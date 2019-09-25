#include <stdio.h>

#define M (x * 3 + 5)

int main()
{
    int s = 0;
    int x = 0;
    printf("input a number:");
    scanf("%d", &x);
    s = 3 * M;
    printf("s=%d\n", s);
}