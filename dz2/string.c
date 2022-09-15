/*
                Task:
Read the text up to the occurence of "END".
Analyze occurence of each character in the text
(we analyze and read line by line; "END" not need in analyze)
Output non-zero frequencies of occurrence of characters
*/
#include <stdio.h>
#define MAX_STR 255
#define symbols 128

int main(void)
{
    char sbuffer[MAX_STR], frequency[symbols], c;
    int i, lens = 0, stop = 1;
    for (i = 0; i < symbols; ++i){
        frequency[i] = 0;
    }
    while(stop != 0){
        i = 0;
        do{
            c = getchar();
            sbuffer[i] = c;
            i++;
        } while ((c != '\n') && (i < 255));
        if (i != 255){
            i -= 2;
        }
       lens = i + 1;
        if ((sbuffer[i-2] == 'E') && (sbuffer[i-1] == 'N') && (sbuffer[i] == 'D')){
            lens -= 3;
            stop = 0;
        }
        for(i = 0; i < lens; ++i){
            frequency[(int)sbuffer[i]]++;
        }
 
   }
    for(i = 0; i < symbols; ++i){
        if( frequency[i] != 0){
            printf("%c = %d\n", i, frequency[i]);
        }
    }
    return 0;
}
