#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>


int 
levelstr(const char *s)
{
    int level = 0;
    for(; *s != '\0'; ++s){
        if (*s == '/'){
            ++level;
        }
    }
    return level;
}

void 
deepdir(char *dirPath, char *maxp)
{
    printf("Current path = %s\n", dirPath);
    if (levelstr(dirPath) > levelstr(maxp)){
        strcpy(maxp, dirPath);
    }
    DIR *dir = opendir(dirPath);
    if (!dir)
    {
        return;
    }
   struct dirent *dd;
   char path[PATH_MAX];
   while((dd = readdir(dir)))
   {
        int slen = snprintf(path, sizeof(path), "%s/%s", dirPath, dd->d_name);
        if (slen + 1 > sizeof(path) || dd->d_name[0] == '.')
            continue;
        struct stat stb;
        if (stat(path, &stb) < 0) 
            continue;
        if((S_ISDIR(stb.st_mode)) && (!S_ISLNK(stb.st_mode)))
            deepdir(path, maxp);
   }
   closedir(dir);
}

int
main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Not enough arguments.\n");
        exit(2);
    }
    char maxp[PATH_MAX] = "";
    deepdir(argv[1], maxp);
    printf("%s\n", maxp);
}
