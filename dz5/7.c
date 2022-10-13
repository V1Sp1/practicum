#include <stdio.h>

void pack(char *input, char *output)
{
    FILE *ipf = fopen(input, "r");
    FILE *opf = fopen(output, "w");
    char c0, c1;
    char n = -1;
    fread( &c0, 1, 1, ipf);
    while (fread( &c1, 1, 1, ipf) == 1){
        if (c1 == c0){
            --n;
        } else{
//            fprintf(opf, "%d", n);
//            fprintf(opf, "%c", c0);
            fwrite(&n, 1, 1, opf);
            fwrite(&c0, 1, 1, opf);
            n= -1;
            c0 = c1;
        }
    }
    fclose(ipf);
    fclose(opf);
}

void unpack(char *input, char *output)
{
    FILE *ipf = fopen(input, "r");
    FILE *opf = fopen(output, "w");
    char n, c;
    while (fread(&n, 1, 1, ipf) == 1){
        fread(&c, 1, 1, ipf);
        for(; n < 0; ++n){
            fwrite(&c, 1, 1, opf);
        }
    }
    fclose(ipf);
    fclose(opf);
}
int main(void)
{
    pack("input", "output");
    unpack("output", "output1");
    return 0;
}
