/*
* mutex.c
* 线程实例
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
void *producter_f (void *arg);					/*生产者*/
void *consumer_f (void *arg);					/*消费者*/
int buffer_has_item=0;							/*缓冲区计数值*/
int empty = 8;
pthread_mutex_t mutex;							/*互斥区*/
int running =1 ;								/*线程运行控制*/

int main (void)
{
	pthread_t consumer_t;						/*消费者线程参数*/
	pthread_t producter_t;						/*生产者线程参数*/
	
	pthread_mutex_init (&mutex,NULL);			/*初始化互斥*/
	/*
pthread_mutex_init()函数是以动态方式创建互斥锁的，参数attr指定了新建互斥锁的属性。
如果参数attr为空，则使用默认的互斥锁属性，默认属性为快速互斥锁 。互斥锁的属性在创建锁的时候指定，
在LinuxThreads实现中仅有一个锁类型属性，不同的锁类型在试图对一个已经被锁定的互斥锁加锁时表现不同。
pthread_mutexattr_init()函数成功完成之后会返回零，其他任何返回值都表示出现了错误。
函数成功执行后，互斥锁被初始化为未锁住态。	
	*/
	pthread_create(&producter_t, NULL,(void*)producter_f, NULL );														/*建立生产者线程*/
	pthread_create(&consumer_t, NULL, (void *)consumer_f, NULL);														/*建立消费者线程*/
	usleep(1000);									/*等待，线程创建完毕*/
	running = 0;									/*设置线程退出值*/
	pthread_join(consumer_t,NULL);				/*等待消费者线程退出*/
	pthread_join(producter_t,NULL);			/*等待生产者线程退出*/
	pthread_mutex_destroy(&mutex);				/*销毁互斥*/
	//互斥锁销毁函数在执行成功后返回 0，否则返回错误码
	
	return 0;
}
void *producter_f (void *arg)					/*生产者线程程序*/
{
	while(running)								/*没有设置退出值*/
	{	
		pthread_mutex_lock (&mutex);			/*进入互斥区*/
		if(empty > 0){
			buffer_has_item++;						/*增加计数值*/
			empty--;
			printf("生产，总数量:%d\n",buffer_has_item); 	/*打印信息*/
		}
		pthread_mutex_unlock(&mutex);			/*离开互斥区*/
	}
}
void *consumer_f(void *arg)						/*消费者线程程序*/
{
	while(running)								/*没有设置退出值*/
	{
		pthread_mutex_lock(&mutex);				/*进入互斥区*/
		if(buffer_has_item > 0){
			buffer_has_item--;						/*减小计数值*/
			empty++;
			printf("消费，总数量:%d\n",buffer_has_item);	/*打印信息*/
		}
		pthread_mutex_unlock(&mutex);			/*离开互斥区*/
	}
}