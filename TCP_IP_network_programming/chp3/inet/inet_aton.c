#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
    char *addr="127.232.124.79";
    struct sockaddr_in addr_inet;

    // inet_aton函数和inet_addr函数， 在功能上完全相同，也是将字符串形式的IP地址转换为32位的网络字节序整数并返回
    // 该函数利用了in_addr结构体，并且使用频率更高
    if(!inet_aton(addr, &addr_inet.sin_addr))
	error_handling("conversion error");
    else
	printf("network ordered integer addr: %#x \n",
	       addr_inet.sin_addr.s_addr);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
