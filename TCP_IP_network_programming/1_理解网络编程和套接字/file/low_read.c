#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 100

void error_handling(char* message);

int main(void)
{
    int fd;
    char buf[BUF_SIZE];

    // 打开文件，只读方式
    fd=open("data.txt", O_RDONLY);

    if(fd==-1)
	error_handling("open() error");
    printf("file descriptor: %d \n", fd);

    // 调用read函数，读入文件中的数据到buf数组
    if(read(fd, buf, sizeof(buf))==-1)
	error_handling("read() error!");
    printf("file data: %s", buf);

    close(fd);
    return 0;
}


void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
