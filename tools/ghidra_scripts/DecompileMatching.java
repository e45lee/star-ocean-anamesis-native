// Decompile every function whose demangled or raw symbol name matches a regex.
// Args: <outFile> <regex> [<regex> ...]
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.app.util.demangler.*;
import java.io.*;
import java.util.*;
import java.util.regex.*;

public class DecompileMatching extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        PrintWriter out = new PrintWriter(new FileWriter(args[0]));
        List<Pattern> pats = new ArrayList<>();
        for (int i = 1; i < args.length; i++) pats.add(Pattern.compile(args[i]));

        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        Set<Address> done = new HashSet<>();
        SymbolIterator it = currentProgram.getSymbolTable().getAllSymbols(true);
        while (it.hasNext() && !monitor.isCancelled()) {
            Symbol s = it.next();
            if (s.getSymbolType() != SymbolType.FUNCTION && s.getSymbolType() != SymbolType.LABEL) continue;
            if (!s.getAddress().isMemoryAddress() || s.isExternal()) continue;
            String raw = s.getName(true);
            String dem = raw;
            try {
                List<DemangledObject> ds = DemanglerUtil.demangle(currentProgram, s.getName(), s.getAddress());
                if (ds != null && !ds.isEmpty()) dem = ds.get(0).getSignature(false);
            } catch (Exception e) {}
            boolean hit = false;
            for (Pattern p : pats) if (p.matcher(raw).find() || p.matcher(dem).find()) { hit = true; break; }
            if (!hit || done.contains(s.getAddress())) continue;
            done.add(s.getAddress());
            Function f = getFunctionAt(s.getAddress());
            if (f == null) {
                disassemble(s.getAddress());
                f = createFunction(s.getAddress(), null);
            }
            if (f == null) { out.println("// FAILED to create function at " + s.getAddress() + " " + dem); continue; }
            DecompileResults r = di.decompileFunction(f, 120, monitor);
            out.println("// ==== " + dem);
            out.println("// " + raw + " @ " + f.getEntryPoint());
            out.println(r.decompileCompleted() ? r.getDecompiledFunction().getC() : "// decompile failed: " + r.getErrorMessage());
            out.flush();
        }
        out.close();
    }
}
