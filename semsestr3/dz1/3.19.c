#include <stdio.h>

int main(void)
{
    int n, count = 0;
    for (n = 102; n <= 987; n++){
        if ((n / 100) == ((n / 10) % 10)){
	    n += 9;
	    } else {
            if (((n % 10) != (n / 100)) && ((n % 10) != ((n /10) % 10))){
                count++;
            }
        }
    }
    printf("amount of numbers with all different digit is %d\n", count);
    return 0;
}
