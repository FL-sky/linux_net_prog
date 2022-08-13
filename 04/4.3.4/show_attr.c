#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <errno.h>///

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
	printf("%s\n",strerror(errno));
}


void msg_show_attr(int msg_id, struct msqid_ds msg_info)																	/*打印消息属性的函数*/
{
	printf("----IN msg_show_attr----\n");
	int ret = -1;
	sleep(1);
	ret = msgctl(msg_id, IPC_STAT, &msg_info);		/*获取消息*/
	if( -1 == ret)
	{
		printf("获得消息信息失败\n");					/*获取消息失败，返回*/
		showErrCode(__LINE__);
		return ;		
	}
	
	printf("\n");									/*以下打印消息的信息*/
	printf("现在队列中的字节数：%ld\n",msg_info.msg_cbytes);																	/*消息队列中的字节数*/
	printf("队列中消息数：%d\n",(int)msg_info.msg_qnum);	/*消息队列中的消息数*/
	printf("队列中最大字节数：%d\n",(int)msg_info.msg_qbytes);																	/*消息队列中的最大字节数*/
	printf("最后发送消息的进程pid：%d\n",msg_info.msg_lspid);																/*最后发送消息的进程*/
	printf("最后接收消息的进程pid：%d\n",msg_info.msg_lrpid);																/*最后接收消息的进程*/
	printf("最后发送消息的时间：%s",ctime(&(msg_info.msg_stime)));														/*最后发送消息的时间*/
	printf("最后接收消息的时间：%s",ctime(&(msg_info.msg_rtime)));														/*最后接收消息的时间*/
	printf("最后变化时间：%s",ctime(&(msg_info.msg_ctime)));																/*消息的最后变化时间*/
	printf("消息UID是：%d\n",msg_info.msg_perm.uid);	/*消息的UID*/
	printf("消息GID是：%d\n",msg_info.msg_perm.gid);	/*消息的GID*/

	printf("----OUT msg_show_attr----\n");
}
const int MSGSZ=128,MSGTP=10;
int main()
{
	int ret = -1;
	int msg_flags, msg_id;
	key_t key;
	struct msgmbuf{								/*消息的缓冲区结构*/
		//int mtype;
		long mtype;
		char mtext[MSGSZ];
		};	
	struct msqid_ds msg_info;
	struct msgmbuf msg_mbuf;
	
	int msg_sflags,msg_rflags;
	char *msgpath = "./ipc/msg/";				/*消息key产生所用的路径*/
	///char *msgpath = "./ipc/msg/";				/*消息key产生所用的路径*/

	///进程间通信(IPC,Inter-Process Communication)指至少两个进程或线程间传送数据或信号的一些技术或方法。
	///ftok    系统IPC键值的格式转换函数
	///系统建立IPC通讯 （消息队列、信号量和共享内存） 时必须指定一个ID值。通常情况下，该id值通过ftok函数得到。
	key = ftok(msgpath,'b');					/*产生key*/
	printf("key=%d\n",key);
	if(key != -1)								/*产生key成功*/
	{
		printf("成功建立KEY\n");		
	}
	else										/*产生key失败*/
	{
		showErrCode(__LINE__);
		return 0;///
	}
	
	msg_flags = IPC_CREAT|IPC_EXCL;			/*消息的类型*/
	///msg_id = msgget(key, msg_flags|0x0666);	/*建立消息*/
	msg_id = msgget(key, msg_flags|0666);	/*建立消息*/
	if( -1 == msg_id)
	{
		///printf("消息建立失败\n");
		//showErrCode(__LINE__);
		msg_id = msgget(key, 0);
		printf("msg_id=%d\n",msg_id);
		//return 0;///
	}	
	
	msg_show_attr(msg_id, msg_info);			/*显示消息的属性*/
	
	msg_sflags = IPC_NOWAIT;///这句话到底有毛用，引起报错
	msg_mbuf.mtype = MSGTP;
	//memcpy(msg_mbuf.mtext,"just a test",sizeof("just a test"));	/*复制字符串*//字符串长度得小于数组容量
	for (int i=8;i<13;i++){
		char ss[128];
		sprintf(ss,"i am %d",i);
		memcpy(msg_mbuf.mtext,ss,strlen(ss)+1);
		msgsnd(msg_id, &msg_mbuf, strlen(ss)+1, msg_sflags);	
	}
	//memcpy(msg_mbuf.mtext,"测试消息",sizeof("测试消息"));
	ret = msgsnd(msg_id, &msg_mbuf, sizeof("just a test"), msg_sflags);	 /*发送消息*/
	if( -1 == ret)
	{
		printf("发送消息失败\n");
		showErrCode(__LINE__);
		return 0;///
	}
	msg_show_attr(msg_id, msg_info);			/*显示消息属性*/
	
	msg_rflags = IPC_NOWAIT|MSG_NOERROR;
	///ret = msgrcv(msg_id, &msg_mbuf, 10,10,msg_rflags);		/*接收消息*/
	for (int i=0;i<5;i++){
		ret = msgrcv(msg_id, &msg_mbuf, MSGSZ,MSGTP,msg_rflags=0);		/*接收消息*/
		if( -1 == ret)
		{
			printf("接收消息失败\n");
			showErrCode(__LINE__);
			return 0;///		
		}
		else
		{
			printf("接收消息成功，长度：%d\t%s\n",ret,msg_mbuf.mtext);		
		}
	}
	msg_show_attr(msg_id, msg_info);			/*显示消息属性*/
	
	msg_info.msg_perm.uid = 8;
	msg_info.msg_perm.gid = 8;
	msg_info.msg_qbytes = 12345;
	ret = msgctl(msg_id, IPC_SET, &msg_info);	/*设置消息属性*/ 
	//IPC_SET 用来设置消息队列中的属性，要设置的属性存在 buf 中
	if( -1 == ret)
	{
		printf("设置消息属性失败\n");
		showErrCode(__LINE__);
		return 0;		
	}
	msg_show_attr(msg_id, msg_info);			/*显示消息属性*/
	
	ret = msgctl(msg_id, IPC_RMID,NULL);		/*删除消息队列*/
	if(-1 == ret)
	{
		printf("删除消息失败\n");
		showErrCode(__LINE__);
		return 0;		
	}
	return 0;
}
