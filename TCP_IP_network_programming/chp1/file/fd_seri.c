#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

int main(void)
{
    int fd1, fd2, fd3;
    // 创建 2个套接字 和 1个文件
    fd1=socket(PF_INET, SOCK_STREAM, 0);
    fd2=open("test.dat", O_CREAT|O_WRONLY|O_TRUNC);
    fd3=socket(PF_INET, SOCK_DGRAM, 0);

    // 文件描述符从3开始 递增，（0，1，2分别是标准I/O）
    printf("file descriptor 1: %d\n", fd1); // 3
    printf("file descriptor 2: %d\n", fd2); // 4
    printf("file descriptor 3: %d\n", fd3); // 5

    close(fd1);
    close(fd2);
    close(fd3);
    return 0;

}
