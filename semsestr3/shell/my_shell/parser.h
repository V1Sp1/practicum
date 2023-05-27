#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>

#include "command.h"
#include "errors.h"
#include "scanner.h"

int init_parser(FILE *input);
void free_parser(void);
int next_command(Command *c);

#endif
