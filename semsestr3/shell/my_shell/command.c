#include <stdlib.h>

#include "command.h"


int
init_empty_command(Command *c)
{
    c = NULL;
    return 0;
}

int
init_sequence_command(Command *c)
{
    c->kind = KIND_SEQ;
    c->seq_size = 0;
    c->seq_commands = NULL;
    c->seq_operations = NULL;
    return 0;
}

int
append_command_to_sequence(Command *c, Command *cmd)
{
    if (c->seq_size == 0){
        c->seq_size++;
        c->seq_commands = (Command *)malloc(sizeof(Command));
        c->seq_operations = (int *)malloc(sizeof(int));
    } else {
        c->seq_size++;
        c->seq_commands = (Command *)realloc(c->seq_commands, (c->seq_size) * sizeof(Command));
        c->seq_operations = (int *)realloc(c->seq_operations, (c->seq_size) * sizeof(int));
    }
    (c->seq_commands)[c->seq_size - 1] = *cmd;
    return 0;
}

int
append_operation_to_sequence(Command *c, int op)
{
    (c->seq_operations)[c->seq_size - 1] = op;
    return 0;
}

int
init_pipeline_command(Command *c)
{
    c->kind = KIND_PIPELINE;
    c->pipeline_size = 0;
    c->pipeline_commands = NULL;
    return 0;
}

int
append_to_pipeline(Command *c, Command *cmd)
{
    if (c->pipeline_size == 0){
        (c->pipeline_size)++;
        c->pipeline_commands = (Command *)malloc(sizeof(Command));
    } else {
        (c->pipeline_size)++;
        c->pipeline_commands = (Command *)realloc(c->pipeline_commands, (c->pipeline_size) * sizeof(Command));
    }
    (c->seq_commands)[c->pipeline_size - 1] = *cmd;
    return 0;
}

int
init_redirect_command(Command *c)
{
    c->kind = KIND_REDIRECT;
    c->rd_path = NULL;
    c->rd_command = NULL;
    return 0;
}

int
set_rd_command(Command *c, Command *cmd)
{
    c->rd_command = (Command *)malloc(sizeof(Command));
    *(c->rd_command) = *cmd;
    return 0;
}

int
init_simple_command(Command *c)
{
   c->kind = KIND_SIMPLE;
   c->argc = 0;
   c->argv = (char **)malloc(sizeof(char *));
   *(c->argv) = NULL;
   return 0;
}

int
append_word_simple_command(Command *c, char *arg)
{    
    (c->argv)[c->argc] = arg;
    c->argc++;
    c->argv = (char **)realloc(c->argv, (c->argc + 1) * sizeof(char *));
    (c->argv)[c->argc] = NULL;
    return 0;
}

void free_command(Command *c)
{
    int i = 0;
    switch (c->kind) {
    case KIND_SIMPLE:
        for (; i < (c->argc); ++i){
            free((c->argv)[i]);
        }
        free(c->argv);
        return;
    case KIND_REDIRECT:
        free_command(c->rd_command);
        free(c->rd_command);
        free(c->rd_path);
        return;
    case KIND_PIPELINE:
        for (; i < (c->pipeline_size); ++i){
            free_command(c->pipeline_commands + i);
        }
        if (c->pipeline_size > 0){
            free(c->pipeline_commands);
        }
        return;
    case KIND_SEQ:
        for (; i < (c->seq_size); ++i){
            if(c->seq_commands != NULL){
                free_command(c->seq_commands + i);
            }
        }
        if (c->seq_size > 0) {
            free(c->seq_commands);
            free(c->seq_operations);
        }
        return;
    default:
        abort();
        break;
    }
    return;
}
