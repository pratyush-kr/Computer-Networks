#include<stdio.h>

int main()
{
    unsigned int x = 0x11223344;
    unsigned char ch[4];
    for(int i=0; i<4; i++)
    {
        ch[i] = (x>>(i*8));
        printf("%02X\n", ch[i]);
    }
    return 0;
}