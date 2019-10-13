#include <stdio.h>
int bis(int x, int m) { return x | m; }
int bic(int x, int m) { return x & ~m; }
int bool_or(int x, int y) { return bis(x, y); }
int bool_xor(int x, int y) { return bis(bic(x, y), bic(y, x)); }

int main()
{
    int x = 0x12, y = 0x34;
    printf("%x,%x\n", bool_or(x, y), bool_xor(x, y));
    printf("%x,%x\n", x | y, x ^ y);
    return 0;
}