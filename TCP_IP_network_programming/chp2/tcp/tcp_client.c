#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);


int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len=0;
    int idx=0, read_len=0;

    if(argc !=3)
    {
	printf("Usage: %s <IP> <port> \n", argv[0]);
	exit(1);
    }

    // socket 函数，创建客户端套接字
    // 1) 调用socket函数，创建套接字```
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
	error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

    // connect函数，将会向目标服务器发送连接请求
    // 2)调用connect函数，发送连接请求
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
	error_handling("connect() error");

    // read 循环反复调用, 每次读取1个字节
    // read 返回0，则循环条件为false, 跳出while循环
    // str_len中保存了读取的总字节数
    while(read_len=read(sock, &message[idx++], 1))
    {
	if(read_len==-1)
	    error_handling("read() error!");
	str_len+=read_len;
    }

    printf("message from server: %s\n", message);
    printf("function read call count: %d\n", str_len);

    /* str_len=read(sock, message, sizeof(message)-1); */
    /* if(str_len==-1) */
    /* 	error_handling("read() error"); */

    /* printf("message from server: %s\n", message); */
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);    exit(1);
}
