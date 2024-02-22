#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int cfd1, cfd2;
    char str1[]="hi, \n";
    char str2[]="It is nice day\n";

    // 调用dup, 复制文件描述符1
    // 调用dup2, 再次复制了文件描述符，指定描述符为7
    cfd1=dup(1);
    cfd2=dup2(cfd1, 7);

    printf("fd1=%d, fd2=%d\n", cfd1, cfd2);
    // 通过复制的文件描述符，进行输出
    write(cfd1, str1, sizeof(str1));
    write(cfd2, str2, sizeof(str2));

    // 终止复制的文件描述符
    close(cfd1);
    close(cfd2);
    // 此时，仍然可以输出
    write(1, str1, sizeof(str1));
    close(1);
    // 此时，无法继续输出，因为所有的文件描述符都终止
    write(1, str2, sizeof(str2));
    return 0;
}
