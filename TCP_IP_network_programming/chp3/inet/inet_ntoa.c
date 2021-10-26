#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in addr1, addr2;
    char *str_ptr;
    char str_arr[20];

    addr1.sin_addr.s_addr=htonl(0x1020304);
    addr2.sin_addr.s_addr=htonl(0x1010101);

    // 向inet_ntoa 函数传递结构体变量addr1中的IP地址信息并调用该函数，返回字符串形式的IP地址
    str_ptr=inet_ntoa(addr1.sin_addr);
    // 复制addr1中的IP地址
    strcpy(str_arr, str_ptr);
    printf("dotted-decimal notation1: %s\n", str_ptr);

    // 再次调用inet_ntoa函数，str_ptr将被覆盖
    inet_ntoa(addr2.sin_addr);
    printf("dotted-decimal notation2: %s\n", str_ptr);
    printf("dotted-decimal notation3: %s\n", str_arr);
    return 0;
}
