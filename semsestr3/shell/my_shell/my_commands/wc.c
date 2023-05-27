#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>

enum { MAX_BUFF = 64};

void print_error(int error){
    if (error == -1){
        fprintf(stderr, "The file failed to open\n");
    } else if (error == -2){
        fprintf(stderr, "The file failed to read\n");
    }
}

void print_usage(char *name){
    fprintf(stderr, "SYNTAX ERROR:\nUsage: %s [filename]\n", name);
}

static int wc(char **argv)
{
    char buff[MAX_BUFF];
    int symbols = 0, words = 0, lines = 0;
    int fd = open(argv[1], O_RDONLY);
    
    if (fd == -1) {
        return -1;
    }
    
    int r;
    
    while((r = read(fd, buff, MAX_BUFF)) > 0){
        symbols += r;
        int i;
        for(i = 0; i < MAX_BUFF; ++i){
            if (isspace(buff[i])){
                ++words;
                if (buff[i] == '\n'){
                    ++lines;
                }
            }
        }
    
    }
    close(fd);
    if ( r < 0){
        return -2;
    }
    printf("%12d%12d%12d\t%s\n", lines, words, symbols, argv[1]);
    return 0;
}

int main(int argc, char *argv[]){
	int r;
	if(argc != 2){
		print_usage(argv[0]);
        return -1;
	}
    else if((r = wc(argv)) != 0 ){
        print_error(r);
        return -1;
    }
    return 0;
}
