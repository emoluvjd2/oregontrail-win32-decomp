// Export fresh local analysis; these inventories are not the upstream baseline.
// @category OregonTrail
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.InstructionIterator;
import java.io.File;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;

public class ExportLocalAnalysis extends GhidraScript {
    private String csv(String value) {
        return "\"" + value.replace("\"", "\"\"") + "\"";
    }

    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 1) throw new IllegalArgumentException("Supply output directory");
        File output = new File(args[0], currentProgram.getName());
        Files.createDirectories(output.toPath());
        DecompInterface decompiler = new DecompInterface();
        if (!decompiler.openProgram(currentProgram)) {
            throw new IllegalStateException(decompiler.getLastMessage());
        }
        try (PrintWriter metrics = new PrintWriter(new File(output, "function_metrics.csv"), "UTF-8");
             PrintWriter assembly = new PrintWriter(new File(output, "disassembly.txt"), "UTF-8")) {
            metrics.println("program,original_va,name,instruction_count,body_bytes,decompile_status");
            FunctionIterator functions = currentProgram.getFunctionManager().getFunctions(true);
            int count = 0;
            while (functions.hasNext() && !monitor.isCancelled()) {
                Function function = functions.next();
                if (function.isExternal()) continue;
                String address = "0x" + function.getEntryPoint().toString();
                assembly.println("\n" + address + " " + function.getName());
                int instructions = 0;
                InstructionIterator iterator = currentProgram.getListing().getInstructions(function.getBody(), true);
                while (iterator.hasNext()) {
                    ghidra.program.model.listing.Instruction instruction = iterator.next();
                    assembly.println(instruction.getAddress() + "  " + instruction);
                    instructions++;
                }
                DecompileResults result = decompiler.decompileFunction(function, 30, monitor);
                boolean completed = result.decompileCompleted() && result.getDecompiledFunction() != null;
                String source = completed ? result.getDecompiledFunction().getC() : "/* " + result.getErrorMessage() + " */";
                Files.write(new File(output, address + ".c").toPath(), source.getBytes(StandardCharsets.UTF_8));
                metrics.println(csv(currentProgram.getName()) + "," + address + "," + csv(function.getName()) + "," +
                    instructions + "," + function.getBody().getNumAddresses() + "," + (completed ? "complete" : "failed"));
                count++;
            }
            println("Exported " + count + " functions to " + output);
        } finally {
            decompiler.dispose();
        }
    }
}
