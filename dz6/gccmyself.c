#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    char *name = (char*)malloc(sizeof(char) * (strlen(argv[0]) + 2));
    strcpy(name, argv[0]);
    name[strlen(argv[0])] = '.';
    name[strlen(argv[0])+1] = 'c';
    pid = fork();
    if (pid == -1){
        perror("fork:");
        exit(1);
    }
    if (pid == 0){
        execlp("gcc", "gcc", "-Wall", name, "-o", argv[0], NULL);
        perror("gcc:");
        exit(1);
    }
    wait(NULL);
    printf("%s\n", name);
    free(name);
    return 0;
}

