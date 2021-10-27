#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    int fds[2];
    char str[]="who are you?";
    char buf[BUF_SIZE];
    pid_t pid;

    // pipe函数用于创建管道，fds数组中保存用于I/O的文件描述符
    pipe(fds);
    pid=fork();
    if(pid==0){
	// 子进程执行
	// 子进程拥有管道的I/O两个文件描述符
	// 父子进程同时拥有I/O文件描述符
	write(fds[1], str, sizeof(str));
    }
    else{
	// 父进程执行
	// 父进程读取子进程写入的字符串
	read(fds[0], buf, BUF_SIZE);
	puts(buf);
    }
    return 0;
}
