/*
* sem.c
* 线程实例
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
void *producter_f (void *arg);					/*生产者线程函数*/
void *consumer_f (void *arg);					/*消费者线程函数*/
sem_t sem;
int running =1 ;
int main (void)
{
	pthread_t consumer_t;						/*消费者线程参数*/
	pthread_t producter_t;						/*生产者线程参数*/
	
	sem_init (&sem, 0, 3);						/*信号量初始化*/
	/*
int sem_init(sem_t *sem, int pshared, unsigned int value);//初始化一个定位在 sem 的匿名信号量
参数
	sem ：指向信号量对象
	pshared : 指明信号量的类型。不为0时此信号量在进程间共享，
否则只能为当前进程的所有线程共享。并且应该放置在这个进程的所有线程都可见的地址上(如全局变量，或者堆上动态分配的变量)
	value : 指定信号量值的大小
返回值
	sem_init() 成功时返回 0；错误时，返回 -1，并把 errno 设置为合适的值。	


	*/
	
	pthread_create(&producter_t, NULL,(void*)producter_f, NULL ); 														/*建立生产者线程*/
	pthread_create(&consumer_t, NULL, (void *)consumer_f, NULL); 														/*建立消费者线程*/
	sleep(1);									/*等待*/
	running =0;									/*设置线程退出*/
	pthread_join(consumer_t,NULL);				/*等待消费者线程退出*/
	pthread_join(producter_t,NULL);			/*等待生产者线程退出*/
	sem_destroy(&sem);							/*销毁信号量*/
	
	return 0;
}
void *producter_f (void *arg)					/*生产者处理程序代码*/
{
	int semval=0;								/*信号量的初始值为0*/
	while(running)								/*运行状态为可运行*/
	{
		usleep(1);								/*等待*/
		sem_post (&sem);						/*信号量增加*/
		/*
sem_post函数的作用是给信号量的值加上一个“1”，它是一个“原子操作”
返回值
sem_post() 成功时返回 0；错误时，信号量的值没有更改，-1 被返回，并设置 errno 来指明错误。		
		*/
		
		sem_getvalue(&sem,&semval);				/*获得信号量的值*/
		/*
	sem_getvalue() 把 sem 指向的信号量当前值放置在 sval 指向的整数上。 
如果有一个或多个进程或线程当前正在使用 sem_wait(3) 等待信号量，POSIX.1-2001 允许返回两种结果在 sval 里：
要么返回 0；要么返回一个负值，它的绝对等于当前正在 sem_wait(3) 里阻塞的进程和线程数。
Linux 选择了前面的行为(返回零)。
	注意：信号量的值可能在 sem_getvalue() 返回时已经被更改。
返回值
	sem_getvalue() 成功时返回 0；错误时，返回 -1，同时把 errno 设置为合适的值。
错误
	EINVAL
	sem 不是一个有效的信号量。		
		*/
		
		printf("生产,sum=%d\t",semval);		/*打印信息*/
	}
}
void *consumer_f(void *arg)						/*消费者处理程序代码*/
{
	int semval=0;								/*信号量的初始值为0*/
	while(running)								/*运行状态为可运行*/
	{
		usleep(1);								/*等待*/
		sem_wait(&sem);							/*等待信号量*/
		/*
sem_wait是一个函数，也是一个原子操作，它的作用是从信号量的值减去一个“1”，
但它永远会先等待该信号量为一个非零值才开始做减法		
		*/
		////usleep(100);
		sem_getvalue(&sem,&semval);				/*获得信号量的值*/
		printf("消费,sum=%d\t",semval);		/*打印信息*/
	}
}