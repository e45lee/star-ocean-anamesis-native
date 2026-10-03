// Decompile functions at given addresses (creating them if needed).
// Args: <outFile> <hexAddr> [<hexAddr> ...]
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import java.io.*;

public class DecompileAt extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        PrintWriter out = new PrintWriter(new FileWriter(args[0]));
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        for (int i = 1; i < args.length; i++) {
            Address a = toAddr(Long.parseLong(args[i].replace("0x", ""), 16));
            Function f = getFunctionAt(a);
            if (f == null) { disassemble(a); f = createFunction(a, "FUN_" + a); }
            if (f == null) { out.println("// FAILED at " + a); continue; }
            DecompileResults r = di.decompileFunction(f, 120, monitor);
            out.println("// ==== @" + a);
            out.println(r.decompileCompleted() ? r.getDecompiledFunction().getC() : "// failed: " + r.getErrorMessage());
        }
        out.close();
    }
}
