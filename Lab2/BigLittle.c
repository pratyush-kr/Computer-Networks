#include<stdio.h>
#include<math.h>

int main()
{
    char bigendian[8];
    unsigned int x, num = 0;
    int n = sizeof(x);
    unsigned char *hex[n], *ptr = (unsigned char*)&x;
    printf("Enter a Hex(B): ");
    scanf(" %s", bigendian);
    //converting the string to hex
    sscanf(bigendian, "%x", &x);
    for(int i=0; i<n; i++)
        hex[i] = (ptr+i);
    int p = n;
    //now convert the hex back to int considiring it is big endian system
    for(int i=0; i<n-1; i++)
        num += *hex[i] * pow(16, p--);
    num += *hex[n-1];
    //so if x and num are equal that means our hypothesis was correct
    //else it is Little Endian
    if(x != num)
        printf("Little Endian\n");
    else
        printf("Big Endian\n");
    return 0;
}