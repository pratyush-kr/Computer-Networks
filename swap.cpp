#include<iostream>

int main()
{
    long int a = 5, b = 6;
    int *ptr;
    ptr = (int*)a;
    a = b;
    b = (long int)ptr;
    std::cout<<a<<" "<<b<<'\n';
    return 0;
}