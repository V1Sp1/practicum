#ifndef COMMAND_H
#define COMMAND_H

#include <stdlib.h>

#include "errors.h"

typedef enum Kinds
{
    KIND_SIMPLE,
    KIND_REDIRECT,
    KIND_PIPELINE,
    KIND_SEQ
}Kinds;

typedef enum Seq_ops
{
    OP_SEQ,
    OP_CONJUNCT,
    OP_DISJUNCT,
    OP_BACKGROUND
}Seq_ops;

typedef enum Rd_modes
{
    RD_INPUT,
    RD_OUTPUT,
    RD_APPEND
}Rd_modes;

typedef struct Command
{
    Kinds kind;
    union{
        struct{
            int argc;
            char **argv;
        };
        struct{
            Rd_modes rd_mode;
            char *rd_path;
            struct Command *rd_command;
        };
        struct{
            int pipeline_size;
            struct Command *pipeline_commands;
        };
        struct{
            int seq_size;
            struct Command *seq_commands;
            int *seq_operations;
        };
    };
}Command;

int init_empty_command(Command *c);

int init_sequence_command(Command *c);
int append_command_to_sequence(Command *c, Command *cmd);
int append_operation_to_sequence(Command *c, int op);

int init_pipeline_command(Command *c);
int append_to_pipeline(Command *c, Command *cmd);

int init_redirect_command(Command *c);
int set_rd_command(Command *c, Command *cmd);

int init_simple_command(Command *c);
int append_word_simple_command(Command *c, char *argv);

void free_command(Command *c);

#endif
