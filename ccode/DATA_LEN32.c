#include <stdio.h>

#define DATA_LEN32(data) (((data & 0x000000ff) << 24) | ((data & 0x0000ff00) << 8) | \
                          ((data & 0x00ff0000) >> 8) | ((data & 0xff000000) >> 24))

int main()
{
    unsigned int a = 1;
    printf("%d", DATA_LEN32(a));
}