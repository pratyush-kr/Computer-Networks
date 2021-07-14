#include<stdio.h>

typedef struct pkt pkt;

struct pkt
{
    unsigned char ch1;
    unsigned char ch2[2];
    unsigned char ch3;
};

int main()
{
    unsigned int x = 0x11223344;
    pkt num;
    num.ch1 = x;
    num.ch2[0] = x>>8;
    num.ch2[1] = x>>16;
    num.ch3 = x>>24;
    printf("0x%02X%02X%02X%02X\n", num.ch3, num.ch2[1], num.ch2[0], num.ch1);
    return 0;
}