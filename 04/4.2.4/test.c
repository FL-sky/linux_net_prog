#include<stdio.h>
#include<unistd.h>
int main(void)
{
	char *args[]={"/bin/ls",NULL};
	printf("系统分配的进程号是：%d\n",getpid());
	if(execve("/bin/ls",args,NULL)<0)//执行成功后，后面的语句都不执行了
		printf("创建进程出错！\n");
	else{
		printf("创建进程成功！\n");
	}
	printf("\n-------主程结束-------\n");
	return 0;
}
/*
execve（执行文件）在父进程中fork一个子进程，在子进程中调用exec函数启动新的程序。exec函数一共有六个，
其中execve为内核级系统调用，其他（execl，execle，execlp，execv，execvp）都是调用execve的库函数。
*/