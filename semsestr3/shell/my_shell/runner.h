#ifndef RUNNER_H
#define RUNNER_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "command.h"

struct Background_pids
{
    pid_t pid;
    struct Background_pids *next;
};

int run_command(Command *c);

#endif
