#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	int ret;
	
	printf("系统分配的进程号是：%d\n",getpid());
	ret = system("ping www.baidu.com -c 2");
	printf("返回值为：%d\n",ret);
	return 0;
}
/*
system()会调用fork()产生子进程, 由子进程来调用/bin/sh-c string 来执行参数string 字符串所代表的命令,
此命令执行完后随即返回原调用的进程. 在调用system()期间SIGCHLD 信号会被暂时搁置,SIGINT 和SIGQUIT 信号则会被忽略.

返回值
	1、如果 system()在调用/bin/sh 时失败则返回127, 其他失败原因返回-1.。
	2、若参数string 为空指针(NULL), 则返回非零值.
	3、如果system()调用成功则最后会返回执行shell 命令后的返回值, 但是此返回值也有可能为system()调用/bin/sh 失败所返回的127, 因此最好能再检查errno 来确认执行成功.
附加说明
	在编写具有 SUID/SGID 权限的程序时请勿使用system(), system()会继承环境变量, 通过环境变量可能会造成系统安全的问题.
*/