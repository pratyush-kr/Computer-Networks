#include<stdio.h>
#include<math.h>
typedef struct pkt pkt;

struct pkt
{
    unsigned char ch1;
    unsigned char ch2[2];
    unsigned char ch3;
};

int main()
{
    unsigned int x = 300, x2;
    unsigned char *ch = (unsigned char*)&x, *ch1 = (unsigned char*)&x2;
    pkt num;
    /*Learnt Way*/
    num.ch1 = *(ch+0);
    num.ch2[0] = *(ch+1);
    num.ch2[1] = *(ch+2);
    num.ch3 = *(ch+3);
    printf("HEX: 0x%x%x%x%x\n", num.ch3, num.ch2[1], num.ch2[0], num.ch1);
    *(ch1+0) = num.ch1;
    *(ch1+1) = num.ch2[0];
    *(ch1+2) = num.ch2[1];
    *(ch1+3) = num.ch3;
    printf("num = %d\n", x2);
    /*My way*/
    x = 0x256;
    num.ch1 = x;
    num.ch2[0] = x>>8;
    num.ch2[1] = x>>16;
    num.ch3 = x>>24;
    printf("HEX: 0x%x%x%x%x\n", num.ch3, num.ch2[1], num.ch2[0], num.ch1);
    x2 = num.ch3 * pow(16 ,4) + num.ch2[1] * pow(16, 3) + num.ch2[0] * pow(16, 2) + num.ch1;
    printf("num = %d\n", x2);
    return 0;
}