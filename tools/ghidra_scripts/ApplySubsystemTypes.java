// Applies a subsystem's recovered types and names to the program (tools/ghidra_apply_types.sh).
// Args: <types.json> [<symbols.tsv>]
//   types.json (tools/subsystem.py export-types): structs -> data types in /soa/<subsystem>, replacing
//     an earlier version of the same name; pointers to structs of the same file are typed.
//   symbols.tsv: a function still named FUN_... gets the row's symbol; every row gets a bookmark
//     "soa/<subsystem>" with its status and topic.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import com.google.gson.*;
import java.nio.file.*;
import java.util.*;

public class ApplySubsystemTypes extends GhidraScript {
    DataTypeManager dtm;
    Map<String, DataType> made = new HashMap<>();

    DataType typeOf(JsonObject t, int size) {
        String k = t.get("kind").getAsString();
        switch (k) {
        case "int": {
            int n = t.get("size").getAsInt();
            boolean signed = t.has("signed") && t.get("signed").getAsBoolean();
            return signed ? AbstractIntegerDataType.getSignedDataType(n, dtm) : AbstractIntegerDataType.getUnsignedDataType(n, dtm);
        }
        case "float":
            return t.get("size").getAsInt() == 8 ? DoubleDataType.dataType : FloatDataType.dataType;
        case "ptr": {
            DataType to = t.has("to") && !t.get("to").isJsonNull() ? made.get(t.get("to").getAsString()) : null;
            return new PointerDataType(to != null ? to : VoidDataType.dataType, 8, dtm);
        }
        case "struct": {
            DataType d = made.get(t.get("name").getAsString());
            if (d != null) return d;
            break;
        }
        case "array": {
            JsonObject of = t.getAsJsonObject("of");
            int count = t.get("count").getAsInt();
            DataType e = typeOf(of, count > 0 ? size / count : 0);
            if (e != null && count > 0 && e.getLength() > 0) return new ArrayDataType(e, count, e.getLength(), dtm);
            break;
        }
        }
        return null;  // bytes, bitfield, unknown: undefined bytes
    }

    DataType bytes(int n) { return new ArrayDataType(Undefined1DataType.dataType, n, 1, dtm); }

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        JsonObject doc = JsonParser.parseString(Files.readString(Path.of(args[0]))).getAsJsonObject();
        String sub = doc.get("subsystem").getAsString();
        dtm = currentProgram.getDataTypeManager();
        CategoryPath cat = new CategoryPath("/soa/" + sub);
        JsonArray structs = doc.getAsJsonArray("structs");
        // Pass 1: every struct as an empty shell of its size, so pointers and members resolve in any order.
        for (JsonElement e : structs) {
            JsonObject s = e.getAsJsonObject();
            String name = s.get("name").getAsString();
            boolean union = s.has("union") && s.get("union").getAsBoolean();
            DataType shell = union ? new UnionDataType(cat, name, dtm) : new StructureDataType(cat, name, s.get("size").getAsInt(), dtm);
            made.put(name, dtm.addDataType(shell, DataTypeConflictHandler.REPLACE_HANDLER));
        }
        // Pass 2: the members.
        int nfields = 0;
        for (JsonElement e : structs) {
            JsonObject s = e.getAsJsonObject();
            String name = s.get("name").getAsString();
            int size = s.get("size").getAsInt();
            boolean union = s.has("union") && s.get("union").getAsBoolean();
            Composite c = union ? new UnionDataType(cat, name, dtm) : new StructureDataType(cat, name, size, dtm);
            for (JsonElement fe : s.getAsJsonArray("fields")) {
                JsonObject f = fe.getAsJsonObject();
                int off = f.get("offset").getAsInt();
                int fsize = f.get("size").getAsInt();
                String fname = f.get("name").getAsString();
                String comment = f.has("comment") ? f.get("comment").getAsString() : null;
                if (fsize <= 0) continue;
                DataType dt = typeOf(f.getAsJsonObject("type"), fsize);
                if (dt == null || dt.getLength() > fsize) {
                    if (dt != null) comment = (comment == null ? "" : comment + "; ") + dt.getName() + " (overlapped by the next field)";
                    dt = bytes(fsize);
                }
                if (union) ((Union) c).add(dt, fname, comment);
                else ((Structure) c).replaceAtOffset(off, dt, dt.getLength(), fname, comment);
                nfields++;
            }
            made.put(name, dtm.addDataType(c, DataTypeConflictHandler.REPLACE_HANDLER));
        }
        println("soa/" + sub + ": " + structs.size() + " struct(s), " + nfields + " field(s)");

        if (args.length < 2 || !Files.exists(Path.of(args[1]))) return;
        int renamed = 0, marked = 0;
        List<String> lines = Files.readAllLines(Path.of(args[1]));
        for (int i = 1; i < lines.size(); i++) {
            String[] c = lines.get(i).split("\t", -1);
            if (c.length < 7 || c[1].isEmpty()) continue;
            Address a = toAddr(Long.parseLong(c[1].replaceFirst("^0x", ""), 16));
            Function fn = getFunctionAt(a);
            if (fn != null && fn.getName().startsWith("FUN_") && !c[3].startsWith("FUN_") && !c[3].isEmpty()) {
                fn.setName(c[3], SourceType.IMPORTED);
                renamed++;
            }
            BookmarkManager bm = currentProgram.getBookmarkManager();
            bm.setBookmark(a, BookmarkType.NOTE, "soa/" + sub, c[6] + " (" + c[5] + ")" + (c.length > 7 && !c[7].isEmpty() ? ": " + c[7] : ""));
            marked++;
        }
        println("soa/" + sub + ": " + marked + " function(s) bookmarked, " + renamed + " renamed");
    }
}
