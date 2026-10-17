#ifndef COMMAND_H
#define COMMAND_H

typedef void *Command;

#include "Tree.h"
#include "Jobs.h"
#include "Sequence.h"

extern Command newCommand(T_command t);

//Pin and pout are used for pipline input and output
extern int execCommand(Command command, Pipeline pipeline, Jobs jobs,
      int *jobbed, int *eof, int fg, int pin, int pout, int (*fds)[2], int npipes);

extern void freeCommand(Command command);
extern void freestateCommand();

#endif
