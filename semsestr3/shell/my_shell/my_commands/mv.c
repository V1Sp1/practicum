#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

enum { MAX_BUFF = 64};

void print_error(int error){
    if (error == -1){
        fprintf(stderr, "The source file failed to open\n");
    } else if (error == -2){
        fprintf(stderr, "The destination file failed to open or create\n");
    } else if (error == -3){
        fprintf(stderr, "The destination file failed to write\n");
    } else if (error == -3){
        fprintf(stderr, "The source file failed to read\n");
    }
}

void print_usage(char *this){
    fprintf(stderr, "SYNTAX ERROR:\nUsage: %s [old filename] [new filename]\n", this);
    exit(EXIT_FAILURE);
}

static int mv(char **argv)
{
    char buff[MAX_BUFF];
    int fsource = open(argv[1], O_RDONLY);

    if (fsource == -1) {
        return -1;
    }

    int fdst = open(argv[2], O_CREAT | O_WRONLY, 0666);
    if (fdst == -1) {
        close(fsource);
        return -2;
    }
    int r;
    while((r = read(fsource, buff, MAX_BUFF)) > 0){
        if ((r = write(fdst, buff, MAX_BUFF)) < 0){
            close(fsource);
            close(fdst);
            return -3;
        }
    }
    close(fsource);
    close(fdst);
    if ( r < 0){
        return -4;
    }
    return 0;
}

int main(int argc, char *argv[]){
	int r;
	if(argc != 3){
		print_usage(argv[0]);
	}
    else if((r = mv(argv)) != 0 ){
        print_error(r);
        return -1;
    }
    unlink(argv[1]);
    return 0;
}
