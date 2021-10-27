#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 100
void error_handling(char *buf);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    struct timeval timeout;
    fd_set reads, cpy_reads;

    socklen_t adr_sz;
    int fd_max, str_len, fd_num, i;
    char buf[BUF_SIZE];
    if(argc!=2){
	printf("usage : %s <port>\n", argv[0]);
	exit(1);
    }

    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

    printf("bind start--\n");

    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
	error_handling("bind() error");
    if(listen(serv_sock, 5)==-1)
	error_handling("listen() error");

    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads);
    fd_max=serv_sock;

    /* printf("start--"); */

    while(1){

	cpy_reads=reads;
	timeout.tv_sec=5;
	timeout.tv_usec=5000;

	if((fd_num=select(fd_max+1, &cpy_reads, 0, 0, &timeout))==-1)
	    break;
	if(fd_num==0)
	    /* printf("select result %d", fd_num); */
	    continue;

	for(i=0; i<fd_max+1; i++){
	    /* printf("fd change, num is %d\n", fd_num); */
	    // 查看发生状态变化的文件描述符
	    if(FD_ISSET(i, &cpy_reads)){
		// 如果是服务器端套接字发生变化，即有连接请求
		if(i==serv_sock){
		    printf("is serv sock\n");
		    adr_sz=sizeof(clnt_adr);
		    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
		    if(clnt_sock==-1)
			error_handling("accept() error");
		    // 把客户端套接字放入监视范围
		    FD_SET(clnt_sock, &reads);
		    if(fd_max<clnt_sock)
			fd_max=clnt_sock;
		    printf("connected client: %d\n", clnt_sock);
		}
		// 并非服务端套接字时候，即有要接受的数据时候
		else{
		    str_len=read(i, buf, BUF_SIZE);
		    // 如果发送的是EOF，需要断开连接
		    if(str_len==0){
			FD_CLR(i, &reads);
			close(i);
			printf("close client: %d\n", i);
		    }
		    else{
			write(i, buf, str_len);
		    }
		}

	    }

	}
    }11
    close(serv_sock);
    return 0;
}

void error_handling(char *buf)
{
    fputs(buf, stderr);
    fputc('\n', stderr);
    exit(1);
}
