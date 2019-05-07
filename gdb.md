# GNU DEBUGGER NOTES

# GDB Information
GDB is going to be needed in terms of debugging programs which are going through memory leaks and even seg faults. These errors are mainly caused because pointers are referenced in incorrect locations or non-existent areas which is what a NULL Pointer is known as. 

## Correct compilation method
When your code is being compiled in GCC it is vital to add the switch of ``` -ggdb ``` this allows the use of your variable names to be assigned to the values in memory which are known as symbols in gdb. You can then launch gdb successfully with the executable file of your code with all the variables you have in your code file.   

## Safely starting GDB
To make sure you don't get any undefined behaviour when you start your program like nothing happening you should issue the ``` start ``` command. The start command allows a temporary breakpoint added into the start of the program from which you can resume the program further, it has proven to be a more efficient to start a program in GDB.

## If a segmentation fault happens?
If a segmentation fault kicks off (Usually the reason for using GDB) then there's a way of tracing this in gdb. When the seg fault happens you will be informed of the ``` SIGSEGV ``` this means the signal has been given to your program that a segmenation fault has happened. Using the ``` bt ``` command you can issue a backtrace which reverse traces the source of the segmentation fault back to the very line number at which it occured on your file. 

### What is a segmentation fault?
A segmentation fault is when your code tries to access out-of-bounds memory, non-existent memory or memory which is already occupied by a process. The SIGSEGV signal acts as a protection mechanism to prevent your filesystem from getting damaged whilst you develop your code. 

### Where are you in the program logic?
Command where or frame can be used. where command will give more info with the function name

### Reading source code
Reading source code of programs can 

## Command cheat sheet
- gdb (-q -silent -quiet) - Multiple operators we can use to load gdb in a quiet state without displaying disclaimer
- gcc -ggdb (filename) - Compiles the file with the symbols and variables needed to pass it through gdb
- shell command file - Command structure which can be used in the GDB debugger, you don't even need to leave the gdb shell or kill the process
- set logging on|off|redirect - Enables the use of gdb logging into a file for future referencing. 
- gcc display (var) - displays variable as you continiously pass through the program
- clear - Clears all the breakpoints you've set
- breakpoint (number) - Sets up a breakpoint in which the code stops at a certain line when you run it
- checkpoint (number) - recreates the situation in which the code broke
- continue - Good for skipping program logic like loops
- gdb --args <program> <args…> Start GDB and pass arguments
- print &(variable) - Prints the memory address of the variable
- step - Useful to step into function stack spaces
- bt - backtrace of the steps of memory it took for the error to occur (Good to isolate functions and fault points)
- info (Object type) - Lists details about the object listed such as breakpoints, functions, display variables. 
- frame - Points out exactly where your program is currently at in terms of execution stages.
- where - Similar to frame. 
- backtrace - Tracking method which shows the origin of a fault and how it started up to the destination where the program had crashed (Your program) usually a line number will print.

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

``` ulimit -c unlimited ```

# Core files
A core file or core dump is a file that records the memory image of a running process and its process status (register values etc.). Its primary use is post-mortem debugging of a program that crashed while it ran outside a debugger. A program that crashes automatically produces a core file, unless this feature is disabled by the user. See Files, for information on invoking gdb in the post-mortem debugging mode.

Core files should be used in gdb to recieve details of a seg fault

# Tracing mechanisms
Of course you've got a debugger and the whole point is to stop and resume programs any way you wish. To achieve this there are 3 different kinds of points which can support you for this case. 

#### Breakpoints

#### Watchpoints

#### Checkpoints
On certain operating systems, GDB is able to save a snapshot of a program’s state, called a checkpoint, and come back to it later.

Returning to a checkpoint effectively undoes everything that has happened in the program since the checkpoint was saved. This includes changes in memory, registers, and even (within some limits) system state. Effectively, it is like going back in time to the moment when the checkpoint was saved.

Thus, if you’re stepping thru a program and you think you’re getting close to the point where things go wrong, you can save a checkpoint. Then, if you accidentally go too far and miss the critical statement, instead of having to restart your program from the beginning, you can just go back to the checkpoint and start again from there.

This can be especially useful if it takes a lot of time or steps to reach the point where you think the bug occurs.

To use the checkpoint/restart method of debugging:

checkpoint
Save a snapshot of the debugged program’s current execution state. The checkpoint command takes no arguments, but each checkpoint is assigned a small integer id, similar to a breakpoint id.

info checkpoints
List the checkpoints that have been saved in the current debugging session. For each checkpoint, the following information will be listed:

Checkpoint ID
Process ID
Code Address
Source line, or label
restart checkpoint-id
Restore the program state that was saved as checkpoint number checkpoint-id. All program variables, registers, stack frames etc. will be returned to the values that they had when the checkpoint was saved. In essence, gdb will “wind back the clock” to the point in time when the checkpoint was saved.

Note that breakpoints, GDB variables, command history etc. are not affected by restoring a checkpoint. In general, a checkpoint only restores things that reside in the program being debugged, not in the debugger.

delete checkpoint checkpoint-id
Delete the previously-saved checkpoint identified by checkpoint-id.

Returning to a previously saved checkpoint will restore the user state of the program being debugged, plus a significant subset of the system (OS) state, including file pointers. It won’t “un-write” data from a file, but it will rewind the file pointer to the previous location, so that the previously written data can be overwritten. For files opened in read mode, the pointer will also be restored so that the previously read data can be read again.

Of course, characters that have been sent to a printer (or other external device) cannot be “snatched back”, and characters received from eg. a serial device can be removed from internal program buffers, but they cannot be “pushed back” into the serial pipeline, ready to be received again. Similarly, the actual contents of files that have been changed cannot be restored (at this time).

However, within those constraints, you actually can “rewind” your program to a previously saved point in time, and begin debugging it again — and you can change the course of events so as to debug a different execution path this time.

Finally, there is one bit of internal program state that will be different when you return to a checkpoint — the program’s process id. Each checkpoint will have a unique process id (or pid), and each will be different from the program’s original pid. If your program has saved a local copy of its process id, this could potentially pose a problem.

4.12.1 A Non-obvious Benefit of Using Checkpoints
On some systems such as GNU/Linux, address space randomization is performed on new processes for security reasons. This makes it difficult or impossible to set a breakpoint, or watchpoint, on an absolute address if you have to restart the program, since the absolute location of a symbol will change from one execution to the next.

A checkpoint, however, is an identical copy of a process. Therefore if you create a checkpoint at (eg.) the start of main, and simply return to that checkpoint instead of restarting the process, you can avoid the effects of address randomization and your symbols will all stay in the same place.

Pulled from: https://sourceware.org/gdb/onlinedocs/gdb/Checkpoint_002fRestart.html#A-Non_002dobvious-Benefit-of-Using-Checkpoints
### Additional breakpoint information
5.1.7 Breakpoint Command Lists
You can give any breakpoint (or watchpoint or catchpoint) a series of commands to execute
when your program stops due to that breakpoint. For example, you might want to print
the values of certain expressions, or enable other breakpoints.
commands [bnum]
... command-list ...
end Specify a list of commands for breakpoint number bnum. The commands themselves appear on the following lines. Type a line containing just end to terminate
the commands.
To remove all commands from a breakpoint, type commands and follow it immediately with end; that is, give no commands.
With no bnum argument, commands refers to the last breakpoint, watchpoint,
or catchpoint set (not to the breakpoint most recently encountered).
Pressing RET as a means of repeating the last gdb command is disabled within a
command-list.
You can use breakpoint commands to start your program up again. Simply use the
continue command, or step, or any other command that resumes execution.


### Reverse execution and process recording
In order for a program to be reversed it is important that the process is recorded into a log file. Once this is recorded the values are then used to be adjusted from the log file 

http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.338.3420&rep=rep1&type=pdf
