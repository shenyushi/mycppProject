#include <stdio.h>

int is_little_endian()
{
    unsigned int a = ~0xff;
    if (((unsigned char *)&a)[0])
        return 0;
    return 1;
}

int main()
{
    if (is_little_endian())
        printf("It is a little endian mechain!");
    else
        printf("It is a big endian mechain");
}