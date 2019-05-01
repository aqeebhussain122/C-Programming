# GNU DEBUGGER NOTES

GDB is going to be needed in terms of debugging programs which are going through memory leaks and even seg faults. These errors are mainly caused because pointers are referenced in incorrect locations or non-existent areas which is what a NULL Pointer is known as. 

- gdb (-q -silent -quiet) - Multiple operators we can use to load gdb in a quiet state without displaying disclaimer
- gcc -ggdb (filename) - Compiles the file with the symbols and variables needed to pass it through gdb
- shell command file - Command structure which can be used in the GDB debugger, you don't even need to leave the gdb shell or kill the process
- set logging on|off|redirect - Enables the use of gdb logging into a file for future referencing. 

## ASLR (ADDRESS SPACE LAYER RANDOMINZATION)
Leave the behavior of the started executable unchanged. Some bugs rear their
ugly heads only when the program is loaded at certain addresses. If your bug
disappears when you run the program under gdb, that might be because gdb
by default disables the address randomization on platforms, such as gnu/Linux,
which do that for stand-alone programs. Use set disable-randomization off
to try to reproduce such elusive bugs.
The virtual address space randomization is implemented only on gnu/Linux.
It protects the programs against some kinds of security attacks. In these cases
the attacker needs to know the exact location of a concrete executable code.
Randomizing its location makes it impossible to inject jumps misusing a code
at its expected addresses.
