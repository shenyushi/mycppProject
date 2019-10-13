#include <stdio.h>

int main()
{
    int a = 0x87654321;
    printf("%x\n", a);
    printf("%x\n", a & 0xff);
    printf("%x\n", a ^ ~0xff);
    printf("%x\n", a | 0xff);
}