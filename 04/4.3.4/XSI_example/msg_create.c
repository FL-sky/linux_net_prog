///http://www.voidcn.com/article/p-grndwcei-yb.html
/*
XSI消息队列
系统提供了四个方法来操作XSI消息队列，它们分别是：

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int msgget(key_t key, int msgflg);
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
*/

/*
我们可以使用msgget去创建或访问一个消息队列，与其他XSI IPC一样，msgget使用一个key作为创建消息队列的标识。
这个key可以通过ftok生成或者指定为IPC_PRIVATE。
指定为IPC_PRIVATE时，此队列会新建出来，而且内核会保证新建的队列key不会与已经存在的队列冲突，
所以此时后面的msgflag应指定为IPC_CREAT。当msgflag指定为IPC_CREAT时，msgget会去试图创建一个新的消息队列，
除非指定key的消息队列已经存在。可以使用IPC_CREAT | IPC_EXCL在指定key已经存在的情况下报错，而不是访问这个消息队列。
我们来看创建一个消息队列的例子：
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>

#define FILEPATH "./psd"
#define PROJID 1234

int main()
{
    int msgid;
    key_t key;
    struct msqid_ds msg_buf;

    key = ftok(FILEPATH, PROJID);
    if (key == -1) {
        perror("ftok()");
        exit(1);
    }

    msgid = msgget(key, IPC_CREAT|IPC_EXCL|0600);
    if (msgid == -1) {
        perror("msgget()");
        exit(1);
    }

    if (msgctl(msgid, IPC_STAT, &msg_buf) == -1) {
        perror("msgctl()");
        exit(1);
    }

    printf("msgid: %d\n", msgid);
    printf("msg_perm.uid: %d\n", msg_buf.msg_perm.uid);
    printf("msg_perm.gid: %d\n", msg_buf.msg_perm.gid);
    printf("msg_stime: %ld\n", msg_buf.msg_stime);
    printf("msg_rtime: %ld\n", msg_buf.msg_rtime);
    printf("msg_qnum: %ld\n", msg_buf.msg_qnum);
    printf("msg_qbytes: %ld\n", msg_buf.msg_qbytes);
    return 0;
}

///https://blog.csdn.net/Cyrus_wen/article/details/79846633 
//删除消息队列

