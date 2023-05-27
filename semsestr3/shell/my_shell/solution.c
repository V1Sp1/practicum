#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "errors.h"
#include "parser.h"
#include "runner.h"

void add_to_path(void)
{
    static char myshell_path[] = "/home/s02210458/course2/shell/my_shell/my_commands";
    char *buff = getenv("PATH");
    int size = sizeof(myshell_path)/sizeof(*myshell_path);
    char *tmp;
    if(buff != NULL){
        tmp = malloc(size + 1 + strlen(buff));
        sprintf(tmp, "%s:%s", myshell_path, buff);
    } else {
        tmp = malloc(size);
        sprintf(tmp, "%s", myshell_path);
    }
    setenv("PATH", tmp, 1);
    free(tmp);
}

int
main(void)
{
    add_to_path();
    int r;
    while (1) {
        printf("$ ");
        fflush(stdout);
        if ((r = init_parser(stdin)) != 0) {
            fprintf(stderr, "%s\n", error_message(r));
            return 0;
        }

        Command c;
        if ((r = next_command(&c)) == EOF && feof(stdin)) {
            free_parser();
            break;
        } else if (r != 0) {
            fprintf(stderr, "%s\n", error_message(r));
            free_parser();
            continue;
        }
        run_command(&c);        
        free_command(&c);
        fflush(stdout);
        free_parser();
    }

    return 0;
}
