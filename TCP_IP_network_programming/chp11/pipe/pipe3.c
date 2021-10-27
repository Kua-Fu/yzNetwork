#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    int fds1[2], fds2[2];
    char str1[]="who are you";
    char str2[]="thank you";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fds1);
    pipe(fds2);
    pid=fork();
    if(pid==0){
	write(fds1[1], str1, sizeof(str1));
	read(fds2[0], buf, BUF_SIZE);
	printf("child proc output: %s\n", buf);
    }
    else{
	read(fds1[0], buf, BUF_SIZE);
	printf("parent proc output: %s\n", buf);
	write(fds2[1], str2, sizeof(str2));
	sleep(3);
    }
    return 0;
}
