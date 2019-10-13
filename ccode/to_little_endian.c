#include <stdio.h>

typedef unsigned char byte;

void show_byte(byte *start, int len)
{
    int i;
    for (i = 0; i < len; ++i)
        printf("%.2x", start[i]);
}

int is_little_endian()
{
    unsigned int a = ~0xff;
    if (((byte *)&a)[0])
        return 0;
    return 1;
}

byte *to_litte_endian(unsigned int *num)
{
    if (!is_little_endian())
        *num = (*num & 0x000000ff) << 24 | (*num & 0x0000ff00) << 8 | (*num & 0x00ff0000) >> 8 | (*num & 0xff000000) >> 24;
    return (byte *)num;
}

int main()
{
    unsigned int a = 0x12345678;
    show_byte(to_litte_endian(&a), 4);
    return 0;
}
