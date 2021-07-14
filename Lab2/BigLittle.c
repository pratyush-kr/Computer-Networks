#include<stdio.h>

int main()
{
    unsigned int x = 1;
    unsigned char *ch;
    ch = (char*)&x;
    printf("%x\n", *ch);
    if(*ch == 1)
        printf("Little Endian\n");
    else
        printf("Big Endian\n");
    return 0;
}