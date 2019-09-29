#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main()
{
    srand(time(NULL));
    for (int i = 0; i < 100; ++i)
    {
        int tmp = rand();
        if (!(tmp & 1))
            ++tmp;
        if (tmp % 2)
            printf("!");
        else
            printf("?");
    }
    return 0;
}