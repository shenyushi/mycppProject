#include <stdio.h>

int int_size_is_32()
{
    int set_msb = 1 << 31;
    return set_msb > 0 ? 0 : 1;
}

int int_size_is_32_16bits()
{
    int i = 16;
    for (int set_msb = 1 << 15; set_msb > 0; set_msb <<= 1)
        ++i;
    return i == 32 ? 1 : 0;
}

int main()
{
    if (int_size_is_32_16bits())
        printf("int size is 32");
    else
        printf("int size is not 32");
}