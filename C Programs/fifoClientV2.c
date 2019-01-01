#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define clientfile "clientFile"
#define serverfile "serverFile"

void demo()
{
    int clientfd, serverfd, num;
    char filename[100], data[2000];

    printf("Enter Filename: ");
    scanf("%s", filename);

    //writing file name on client file
    clientfd = open(clientfile, O_WRONLY);
    write(clientfd, filename, sizeof(filename));

    //reading data from the server file
    serverfd = open(serverfile, O_RDONLY);
    while(num = read(serverfd, data, sizeof(data)) < 0); //waiting to recieve data.
    printf("\nRecieved Data is: \n\n %s", data);
}

int main()
{
    //creating files for server and client.
    if(mknod(clientfile, S_IFIFO | 0777, 0) == -1)
        perror("mknod of client error: ");
    if(mknod(serverfile, S_IFIFO | 0777, 0) == -1)
        perror("mknod of Server error: ");
    printf("Client Online!!");

    demo();    
    return 0;
}
