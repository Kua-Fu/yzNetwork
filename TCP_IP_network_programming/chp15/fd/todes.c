#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    FILE *fp;
    int fd=open("data.dat", O_WRONLY|O_CREAT|O_TRUNC);
    if(fd==-1){
	fputs("file open error", stdout);
	return -1;
    }

    printf("first file descriptor: %d\n", fd);
    fp=fdopen(fd, "w");
    fputs("TCP/IP socket programming\n", fp);
    // 函数fileno将把FIFE指针转换为文件描述符
    printf("second file descriptor: %d\n", fileno(fp));
    fclose(fp);
    return 0;
}
