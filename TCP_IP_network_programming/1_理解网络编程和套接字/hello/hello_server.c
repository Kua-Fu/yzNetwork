#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[]="hello world!";

    if(argc != 2)
    {
	printf("usage :%s <port>\n", argv[0]);
	exit(1);
    }

    // 创建socket, 服务端的套接字（相当于安装电话）
    // 1) 调用socket函数创建套接字
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
	error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    // bind函数，相当于给电话分配了号码
    // 2) 调用bind函数分配IP地址和端口号
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
	error_handling("bind() error");

    // 调用listen函数，相当于连接了电话线
    // 3) 调用listen函数转为可接收请求状态
    if(listen(serv_sock, 5)==-1)
	error_handling("listen() error");

    clnt_addr_size=sizeof(clnt_addr);
    // 调用accept函数, 相当于拿起话筒，进行对话
    // 4) 调用accept函数，受理连接请求
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    if (clnt_sock==-1)
	error_handling("accept() error");

    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
    
}


void error_handling(char *message)
{

    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
