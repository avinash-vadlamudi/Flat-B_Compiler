# FlatB Compiler

To run the code, use the following commands:

make
./bcc filename 2>temp.ll  ---- This redirects the IR code genrerated into temp.ll file and also runs the interpreter created using AST.

##To run using lli

llvm-as temp.ll -o temp.bc   --- Create a bitcode file from IR using llvm-assembler

lli temp.bc   --- Run the bitcode generated using llvm-interpreter.

##To run using llc:

llc temp.ll -o temp.s  --- This converts the code into host architecture.

gcc temp.s -o temp.out  ---- This creates the executable

./temp.out
