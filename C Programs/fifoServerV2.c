#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define clientfile "clientFile"
#define serverfile "serverFile"

void demo()
{
    int clientfd, serverfd, num, fd;
    char filename[100], data[2000];

    //opening and Reading file from client file
    clientfd = open(clientfile, O_RDONLY);
    printf("\nWaiting for Request...");
    while(num = read(clientfd, filename, sizeof(filename)) < 0);

    //opening and reading file contents
    fd = open(filename, O_RDONLY);
    read(fd, data, sizeof(data));
    
    //Writing file contents (data) to server file
    serverfd = open(serverfile, O_WRONLY);
    write(serverfd, data, sizeof(data));
}

int main()
{
    if(mknod(clientfile, S_IFIFO | 0777, 0) == -1)
        perror("mknod error in client:");
    if(mknod(serverfile, S_IFIFO | 0777, 0) == -1)
        perror("mknod error in server: ");
    printf("Server Online!!\n");

    demo();
    return 0;
}

