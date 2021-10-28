#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    FILE *fp;
    // open函数创建文件，返回文件描述符
    int fd=open("data.dat", O_WRONLY|O_CREAT|O_TRUNC);
    if(fd==-1){
	fputs("file open error", stdout);
	return -1;
    }
    // fdopen函数将文件描述符转换为FILE指针
    fp=fdopen(fd, "w");
    // 利用FILE指针，调用标准输出函数fputs
    fputs("network c programming\n", fp);
    fclose(fp);
    return 0;

}
