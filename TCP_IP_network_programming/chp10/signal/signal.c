#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// 定义信号处理函数
void timeout(int sig)
{
    if(sig==SIGALRM){
	puts("time out!");
    }
    // 每隔2秒，产生SIGALRM信号
    alarm(2);
}

void keycontrol(int sig)
{
    if(sig==SIGINT){
	puts("CTRL+C pressed");
    }
}

int main(int argc, char *argv[])
{
    int i;
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);
    alarm(2);

    // 理论上，3次循环，将sleep 3*100=300秒时间
    // 但是，发生信号的时候，将会唤醒由于调用sleep函数而进入阻塞状态的进程
    // 进程一旦被唤醒，不会继续进入睡眠状态
    for(i=0;i<3;i++){
	puts("wait ...");
	sleep(100);
    }
    return 0;
}
