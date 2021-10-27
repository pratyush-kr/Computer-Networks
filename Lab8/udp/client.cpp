#include<iostream>
#include<fstream>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>

using namespace std;

int main(int argc, char *argv[])
{
    string str = "";
    ifstream file("text.txt");
    while(!file.eof())
    {
        string s;
        getline(file, s);
        str += s+" ";
    }
    sockaddr_in saddr, caddr;
    saddr.sin_port = htons(stoi(argv[1]));
    return 0;
}