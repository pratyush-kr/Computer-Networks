#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>

typedef struct Student Student;

struct Student
{
    unsigned int roll_number;
    unsigned int age;
    char address[255];
    unsigned int pin_code;
};

int main()
{
    Student *s = (Student*)malloc(sizeof(Student));
    struct sockaddr_in saddr;
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1025);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int buff;
    int len = sizeof(saddr); 
    while(1)
    {
        printf("Client: ");
        scanf(" %d", &buff);
        sendto(fd, &buff, sizeof(buff), 0, (const struct sockaddr*)&saddr, len);
        int n = recvfrom(fd, s, sizeof(Student), 0, (struct sockaddr*)&saddr, &len);
        if(s == NULL) {printf("Student details not found\n"); continue;}
        printf("roll: %d\n", s->roll_number);
        printf("age: %d\n", s->age);
        printf("address: %s\n", s->address);
        printf("pin: %d\n", s->pin_code);
    }
    close(fd);
    return 0;
}