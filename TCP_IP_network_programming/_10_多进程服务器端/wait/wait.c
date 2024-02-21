#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status;
    pid_t pid=fork();

    if(pid==0){
	// 第一个子进程通过return 终止
	return 3;
    }
    else{
	printf("child pid: %d\n", pid);
	pid=fork();
	if(pid==0){
	    // 第二个子进程通过 exit函数终止
	    exit(7);
	}
	else{
	    printf("child pid: %d\n", pid);
	    // 调用wait函数，之前终止的子进程信息保存到status变量中
	    wait(&status);
	    // 验证子进程是否正常终止，如果正常退出，输出子进程的返回值
	    if(WIFEXITED(status)){
		printf("child send one: %d\n", WEXITSTATUS(status));
	    }
	    wait(&status);
	    if(WIFEXITED(status)){
		printf("child send two: %d\n", WEXITSTATUS(status));
	    }
	    sleep(30);
	}
    }
    return 0;
}
