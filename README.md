# CS452 Homework 3-2
Class: CS452-002 \
Name: Mackenzie Wright \
Email: mackenziewright@u.boisestate.edu

## Project Description
This project implements a simplified Unix shell that supports sequences, pipelines, and I/O redirection. 

## Building and Running
To build and run this project, you have to make sure you're in the inner directory `CS452-hw3`. Once you're in that directory you can build the project by calling `make` to build the whole project or `make shell` to only build the files neceassary to run the shell. You can then start the shell by running `./shell`. To build the tests simply run `make test`, and to clear your build run `make clean`. To create a valgrind report first build the shell then run `./vg`. This runs the shell under Valgrind with full leak checking. Use the shell normally, then `exit` to see the report.

## My Experience
I had a lot of fun working on this project. It reminded me of the project we completed in programming languages where we created our own parser, and I really enjoyed that project as well. I appreciated the already completed basic shell because it provided me a good place to start and an outline for how to complete the rest of the project. I also enjoyed this method of testing because it was unique and ensured I knew what to expect for each shell commands. The hardest part of completing this project was figuring out how to implement pipelining. It took a lot of trial and error, and I used gdb like the project recommended. On the other hand, implementing I/O redirection was much easier for me to implement because I used dup2 which is a standard Unix operation for redirection. 

## Known Issues
There are no known issues with this project. 

## Valgrind Report
Below is my valgrind report I generated using the vg script and running a couple of basic commands in the shell. 

valgrind --leak-check=full --show-leak-kinds=all --suppressions=rl.supp ./shell \
==25428== Memcheck, a memory error detector \
==25428== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al. \
==25428== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info \
==25428== Command: ./shell \
==25428==  \
$ cd /tmp \
$ echo hello \
hello \
$ echo hello > out.txt \
$ cat out.txt \
hello \
$ exit \
==25428== \ 
==25428== HEAP SUMMARY: \
==25428==     in use at exit: 232,800 bytes in 234 blocks \
==25428==   total heap usage: 721 allocs, 487 frees, 265,415 bytes allocated \
==25428==  \
==25428== 47 bytes in 1 blocks are still reachable in loss record 16 of 74 \
==25428==    at 0x484DB80: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so) \
==25428==    by 0x4AD89DC: _nc_doalloc (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE74C8: _nc_read_termtype (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE85E1: _nc_read_file_entry (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE896C: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE8AD0: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE4155: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE42E5: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE47F6: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4898CE4: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2) \
==25428==    by 0x48845D7: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2) \
==25428==    by 0x4884896: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2) \
==25428==  \
==25428== 156 bytes in 1 blocks are still reachable in loss record 23 of 74 \
==25428==    at 0x484DB80: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so) \
==25428==    by 0x4AD89DC: _nc_doalloc (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE74E6: _nc_read_termtype (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE85E1: _nc_read_file_entry (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE896C: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE8AD0: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE4155: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE42E5: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE47F6: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4898CE4: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2) \
==25428==    by 0x48845D7: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2) \
==25428==    by 0x4884896: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2) \
==25428== \
==25428== 4,000 bytes in 1 blocks are still reachable in loss record 44 of 74 \
==25428==    at 0x484DB80: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so) \
==25428==    by 0x4AD89DC: _nc_doalloc (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE7504: _nc_read_termtype (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE85E1: _nc_read_file_entry (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE896C: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE8AD0: _nc_read_entry2 (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE4155: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE42E5: _nc_setupterm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4AE47F6: tgetent_sp (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4) \
==25428==    by 0x4898CE4: _rl_init_terminal_io (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2) \
==25428==    by 0x48845D7: rl_initialize (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2) \
==25428==    by 0x4884896: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2) \
==25428==  \
==25428== LEAK SUMMARY: \
==25428==    definitely lost: 0 bytes in 0 blocks \
==25428==    indirectly lost: 0 bytes in 0 blocks \
==25428==      possibly lost: 0 bytes in 0 blocks \
==25428==    still reachable: 4,203 bytes in 3 blocks \
==25428==         suppressed: 228,597 bytes in 231 blocks \
==25428== \
==25428== For lists of detected and suppressed errors, rerun with: -s \
==25428== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0) \