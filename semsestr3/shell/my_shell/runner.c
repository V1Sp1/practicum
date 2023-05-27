#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "command.h"
#include "runner.h"

static int
run_simple(Command *c)
{ 
    int r, pid;
    if((pid = fork()) == 0){
        if ((r = execvp((c->argv)[0], c->argv)) != 0){
            return r;
        }
    }
    return pid;
}

static int
run_redirect(Command *c)
{
    int fd, stdfd, pid;
    switch (c->rd_mode){
        case RD_INPUT:
            fd = open(c->rd_path, O_RDONLY);
            stdfd = dup(0);
            dup2(fd, 0);
            close(fd);
            break;
        case RD_OUTPUT:
            fd = open(c->rd_path, O_WRONLY | O_CREAT, 0777);
            stdfd = dup(1);
            dup2(fd, 1);
            close(fd);
            break;
        case RD_APPEND:
            fd = open(c->rd_path, O_APPEND | O_CREAT | O_EXCL, 0777);
            stdfd = dup(1);
            dup2(fd, 1);
            close(fd);
            break;
        default:
            return 0;
    }
    pid = run_command(c->rd_command);
    if (c->rd_mode == RD_INPUT){
        dup2(stdfd, 0);
    } else{
        dup2(stdfd, 1);
    }
    return pid;
}

static int
run_pipeline(Command *c)
{

    int i, fd[2], stdfd[2], pid = 0;
    stdfd[0] = dup(0);
    stdfd[1] = dup(1);
    for (i = 0; i < c->pipeline_size; ++i) {
        if (i > 0){
            dup2(fd[0], 0);
            close(fd[0]);
        }
        if (pipe(fd) != 0){
            return -1;
        }
        if (i == c->pipeline_size - 1){
            dup2(stdfd[1], 1);
            close(fd[1]);
        } else {
            dup2(fd[1], 1);
            close(fd[1]);
        }
        if (c->pipeline_size == 1) {
            pid = run_command(c->pipeline_commands);
            close(fd[0]);
        }
        else if ((pid = fork()) == 0) {
            pid = run_command(c->pipeline_commands + i);
            close(fd[0]);
            close(stdfd[0]);
            close(stdfd[1]);
            exit(0);
        }
    }
    close(fd[0]);
    dup2(stdfd[0], 0);
    close(stdfd[0]);
    close(stdfd[1]);
    for(i = 0; i < c->pipeline_size; ++i){
        wait(NULL);
    }
    return pid;
}

static int
run_seq(Command *c)
{
   int pid = 0, status = 0, no_exec = 0;
    for (int i = 0; i < c->seq_size; ++i) {
        switch (c->seq_operations[i]) {
            case OP_SEQ:
                if (no_exec == 0) {
                    pid = run_command(c->seq_commands + i);
                    waitpid(pid, NULL, 0);
                }
                else {
                    no_exec = 0;
                }
                break;
            case OP_CONJUNCT:
                if (no_exec == 0) {
                    pid = run_command(c->seq_commands + i);
                    waitpid(pid, &status, 0);
                }
                no_exec = (!(WIFEXITED(status) && (WEXITSTATUS(status) == 0)));
                break;
            case OP_DISJUNCT:
                if (no_exec == 0) {
                    pid = run_command(c->seq_commands + i);
                    waitpid(pid, &status, 0);
                }
                no_exec = (WIFEXITED(status) && (WEXITSTATUS(status) == 0));
                break;
            case OP_BACKGROUND:
                if (no_exec == 0) {
                    run_command(c->seq_commands + i);
                }
                else {
                    no_exec = 0;
                }
                break;
            default:
                return -1;
                break;
        }
    }
    return pid;
}

int run_command(Command *c)
{
    int pid = 0;
    switch (c->kind) {
        case KIND_SEQ:
            pid = run_seq(c);
            return pid;   
        case KIND_SIMPLE: 
            pid = run_simple(c);
            return pid;
        case KIND_REDIRECT:
            pid = run_redirect(c);
            return pid;
        case KIND_PIPELINE:
            pid = run_pipeline(c);
            return pid;
        default:
            return pid;
    }
    return pid;
}
