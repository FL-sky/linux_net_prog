#ifndef	_4_H
#define	_4_H

#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <errno.h>
#include<string.h>
//
void showErrCode(int line){
	int iarcode[]={E2BIG,EACCES,EAGAIN,EEXIST,EFAULT,EIDRM,EINTR,EINVAL,ENOENT,ENOMEM,ENOMSG,ENOSPC,EPERM};
	int sz=sizeof(iarcode)/sizeof(int);
	char carcode[][20]={"E2BIG","EACCES","EAGAIN","EEXIST","EFAULT","EIDRM","EINTR","EINVAL","ENOENT","ENOMEM","ENOMSG","ENOSPC","EPERM"};
	printf("line=%d\t",line);
	for(int i=0;i<sz;i++){
		if(errno == iarcode[i]){
			printf("errno=%s\t",carcode[i]);
		}
	}
	puts("---err---\n");
}
//
typedef int sem_t;
union semun {							/*信号量操作的联合结构*/
	int 					val;			/*整型变量*/
	struct semid_ds 	*buf;			/*semid_ds结构指针*/
	unsigned short 		*array;			/*数组类型*/
} arg;									/*定义一个全局变量*/
sem_t CreateSem(key_t key, int value)	/*建立信号量，魔数key和信号量的初始值										   value*/
{
	union semun sem;					/*信号量结构变量*/
	sem_t semid;						/*信号量ID*/
	sem.val = value;					/*设置初始值*/
	
	semid = semget(key,1,IPC_CREAT|0666);	/*获得信号量的ID*/
	if (-1 == semid)						/*获得信号量ID失败*/
	{
		showErrCode(__LINE__);
		return -1;							/*返回错误*/
	}
	
	semctl(semid,0,SETVAL,sem);		/*发送命令，建立value个初始值的信号量*/
		
	return semid;						/*返回建立的信号量*/
}
int Sem_P(sem_t semid)							/*增加信号量*/
{
	struct sembuf sops={0,+1,IPC_NOWAIT};		/*建立信号量结构值*/
		
	return (semop(semid,&sops,1));				/*发送命令*/
}
int Sem_V(sem_t semid)							/*减小信号量值*/
{
	struct sembuf sops={0,-1,IPC_NOWAIT};		/*建立信号量结构值*/
	
	return (semop(semid,&sops,1));				/*发送信号量操作方法*/
}
void SetvalueSem(sem_t semid, int value)			/*设置信号量的值*/
{
	union semun sem;								/*信号量操作的结构*/
	sem.val = value;								/*值初始化*/
		
	semctl(semid,0,SETVAL,sem);						/*设置信号量的值*/
}
int GetvalueSem(sem_t semid)						/*获得信号量的值*/
{
	union semun sem;								/*信号量操作的结构*/
	return semctl(semid,0,GETVAL,sem);				/*获得信号量的值*/
}
void DestroySem(sem_t semid)							/*销毁信号量*/
{
	union semun sem;									/*信号量操作的结构*/
	sem.val = 0;										/*信号量值的初始化*/
	
	semctl(semid,0,IPC_RMID,sem);						/*设置信号量*/
}

#endif