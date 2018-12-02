#include<fcntl.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/stat.h> 
#include<stdio.h>

#define fifo1 "/root/fifox" 
#define fifo2 "/root/fifoy"

int main() 
{
    char filename[100],c[2000]; 
    int fd1,fd2,fd;
    int num;

    mknod(fifo1,S_IFIFO |0777,0); 
    mknod(fifo2,S_IFIFO |0777,0);

    printf("server online\n"); 
    fd1=open(fifo1,O_RDONLY);

    printf("waiting for request\n");
    while((num=read(fd1,filename,100))<0); 
    filename[num]='\0';
    printf("%s\n",filename); 
    fd=open(filename,O_RDONLY,0);
    read(fd,c,1999); 
    printf("transmitting data\n");
    fd2=open(fifo2,O_WRONLY);
    write(fd2,c,1999);

    return 0; 
}