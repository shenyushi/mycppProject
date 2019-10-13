#include <stdio.h>

typedef unsigned char byte;

void show_byte(byte *start, int len)
{
    int i;
    for (i = 0; i < len; ++i)
        printf("%.2x", start[i]);
}

unsigned int val = 0x654321;
byte *valp = (byte *)&val;

int main()
{
    show_byte(valp, 4);
}