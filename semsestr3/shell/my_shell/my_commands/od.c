#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

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

static int od(char **argv)
{
    int c;
    long int number = 0;
    char fl_b = 0;
    if (argv[2] != NULL) {
        if (!strcmp(argv[1], "-b")) {
            fl_b = 1;
        }
    }
    
    FILE *fd = fopen(argv[1 + fl_b], "r");
    
    if (fd == NULL) {
        return -1;
    }
       
    while(((c = fgetc(fd)) != EOF) && (!feof(fd))){
        ++number;
        if (number % 10 == 1){
            printf("%07ld\t", number);
        }
        if (fl_b){
            switch (c) {
                case '\n':
                    printf("%06o\t", '\n');
                    break;
                case '\t':
                    printf("%06o\t", '\t');
                    break;
                case '\r':
                    printf("%06o\t", '\r');
                    break;
                default:
                    printf("%06o\t", c);
            }
        } else {
            switch(c) {
                case '\n':
                    printf("%4s\t", "\\n");
                    break;
                case '\t':
                    printf("%4s\t", "\\t");
                    break;
                case '\r':
                    printf("%4s\t", "\\r");
                    break;
                default:
                    printf("%4c\t", c);
            }
        }
        if (number % 10 == 0){
            printf("\n");
        }
    }
    if((c == EOF) && (ferror(fd))){
        fclose(fd);
        return -2;
    }
    fclose(fd);
    printf("\n");
    return 0;
}

int main(int argc, char *argv[]){
	int r;
	if((argc != 3) && (argc != 2)){
		print_usage(argv[0]);
        return -1;
	}
    else if((r = od(argv)) != 0 ){
        print_error(r);
        return -1;
    }
    return 0;
}
