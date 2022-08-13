/*
* pthread.c
* 线程实例
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
static int run = 1;								/*运行状态参数*/
static int retvalue ;							/*线程返回值*/
void *start_routine(void *arg)					/*线程处理函数*/
{
	int *running = arg;						/*获取运行状态指针*/
	printf("子线程初始化完毕，传入参数为:%d\n",*running); /*打印信息*/
	while(*running)							/*当running控制参数有效*/
	{
		printf("子线程正在运行\n");			/*打印运行信息*/
		usleep(1);							/*等待*/
	}
	printf("子线程退出\n");					/*打印退出信息*/
		
	retvalue = 8;							/*设置退出值*/
	//static int retvalue = 8;//也可
	pthread_exit( (void*)&retvalue);		/*线程退出并设置退出值*/
	/*
线程通过调用pthread_exit函数终止执行，就如同进程在结束时调用exit函数一样。
这个函数的作用是，终止调用它的线程并返回一个指向某个对象的指针。
	*/
}
int main(void)
{
	pthread_t pt;
	int ret = -1;
	int times = 3;
	int i = 0; 
	int *ret_join = NULL;
	
	ret = pthread_create(&pt, NULL, (void*)start_routine, &run);/*建立线程*/
	/*
int pthread_create(
	pthread_t *tidp,const pthread_attr_t *attr, void *(*start_rtn)(void*),void *arg
);
若线程创建成功，则返回0。若线程创建失败，则返回出错编号，并且*thread中的内容是未定义的。
返回成功时，由tidp指向的内存单元被设置为新创建线程的线程ID。attr参数用于指定各种不同的线程属性。
新创建的线程从start_rtn函数的地址开始运行，该函数只有一个万能指针参数arg，
如果需要向start_rtn函数传递的参数不止一个，那么需要把这些参数放到一个结构中，
然后把这个结构的地址作为arg的参数传入。
linux下用C语言开发多线程程序，Linux系统下的多线程遵循POSIX线程接口，称为pthread。	
	*/
	if(ret != 0)							/*建立线程失败*/
	{
		printf("建立线程失败\n");				/*打印信息*/
		return 1;							/*返回*/
	}	
	usleep(1);								/*等待*/
//usleep()函数是把调用该函数的线程挂起一段时间 ，单位是微秒（百万分之一秒）

	for(;i<times;i++)						/*进行3次打印*/
	{
		printf("主线程打印\n");				/*打印信息*/
		usleep(100);							/*等待*/
		//usleep(1);
	}
	run = 0;								/*设置线程退出控制值，让线程退出*/
	pthread_join(pt,(void*)&ret_join);		/*等待线程退出*/
	/*
函数定义： int pthread_join(pthread_t thread, void **retval);
描述 ：pthread_join()函数，以阻塞的方式等待thread指定的线程结束。当函数返回时，被等待线程的资源被收回。
如果线程已经结束，那么该函数会立即返回。并且thread指定的线程必须是joinable的。
参数 ：thread: 线程标识符，即线程ID，标识唯一线程。retval: 用户定义的指针，用来存储被等待线程的返回值。
返回值 ： 0代表成功。 失败，返回的则是错误号。	
	*/

	printf("线程返回值为:%d\n",*ret_join);	/*打印线程的退出值*/
	return 0;
}