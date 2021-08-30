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
    Student students[5];
    int rolls[5] = {1, 2, 3, 4, 5};
    int ages[5] = {21, 21, 22, 21, 20};
    char addresses[5][255] = {"Ranchi", "Hazaribagh", "Dhanbad", "Bokaro", "Jamshedpur"};
    int pins[5] = {12345, 12346, 12347, 12348, 12349};
    for(int i=0; i<5; i++)
    {
        students[i].roll_number = rolls[i];
        students[i].age = ages[i];
        strcpy(students[i].address, addresses[i]);
        students[i].pin_code = pins[i];
    }
    struct sockaddr_in saddr, caddr;
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1025);
    saddr.sin_addr.s_addr = INADDR_ANY;
    printf("Waiting:\n");
    if(bind(fd, (const struct sockaddr*)&saddr, sizeof(saddr)) < 0)
    {
        printf("bind failed\n");
    }
    int buffer;
    while(1)
    {
        int sent = 0;
        int len = sizeof(caddr);
        int n = recvfrom(fd, &buffer, sizeof(buffer), 0, (struct sockaddr*)&caddr, &len);
        printf("%d\n", buffer);
        for(int i=0; i<5; i++)
        {
            if(buffer == students[i].roll_number)
            {
                sendto(fd, &students[i], sizeof(Student), 0, (struct sockaddr*)&caddr, len);
                sent = 1;
            }
        }
        if(!sent)
            sendto(fd, &students[0], sizeof(Student), 0, (struct sockaddr*)&caddr, len);
    }
    close(fd);
    return 0;
}