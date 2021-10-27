#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid=fork();

    if(pid==0){

	puts("hi, i am a child process");
    }
    else{
	// 父进程，输出子进程的ID，可以通过ps 查看子进程的状态
	// 父进程sleep 30s，如果父进程终止，子进程也将同时销毁
	printf("child process ID: %d\n", pid);
	sleep(30);
    }

    if (pid==0){
	puts("end child process");
    }
    else{
	puts("end parent process");
    }
    return 0;
}
