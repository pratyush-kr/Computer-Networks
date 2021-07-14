#include<stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a = 5, b = 6;
    printf("Before swap\n");
    printf("a: %d ", a);
    printf("b: %d\n", b);
    swap(&a, &b);
    printf("After swap\n");
    printf("a: %d ", a);
    printf("b: %d\n", b);
    return 0;
}