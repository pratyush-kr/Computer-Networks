#include<stdio.h>
#include<string.h>

typedef struct Info Info;

struct Info
{
    unsigned int roll_no;
    char name[50];
    float cgpa;
};


void input(Info *ptr, int n)
{
    for(int i=0; i<n; i++)
    {
        printf("roll no: ");
        scanf(" %u", &ptr->roll_no);
        printf("name: ");
        scanf(" %s", ptr->name);
        printf("cgpa: ");
        scanf(" %f", &ptr->cgpa);
    }
}

void output(Info *ptr, int n)
{
    for(int i=0; i<n; i++)
    {
        printf("roll no: %u\n", ptr->roll_no);
        printf("name: %s\n", ptr->name);
        printf("cgpa: %.2f\n", ptr->cgpa);
    }
}

int main()
{
    int n;
    printf("n: ");
    scanf(" %d", &n);
    Info I[n];
    printf("\nINPUT:\n");
    input(I, n);
    printf("\nOUTPUT:\n");
    output(I, n);
    return 0;
}