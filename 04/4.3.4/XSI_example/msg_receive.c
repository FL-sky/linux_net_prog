#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILEPATH "./psd"
#define PROJID 1234

struct msgbuf {
    long mtype;
    char mtext[BUFSIZ];
};


int main()
{
    int msgid;
    key_t key;
    struct msgbuf buf;

    key = ftok(FILEPATH, PROJID);
    if (key == -1) {
        perror("ftok()");
        exit(1);
    }

    msgid = msgget(key, 0);
    if (msgid == -1) {
        perror("msgget()");
        exit(1);
    }

    if (msgrcv(msgid, &buf, BUFSIZ, 1, 0) == -1) {
        perror("msgrcv()");
        exit(1);
    }

    printf("mtype: %d\n", buf.mtype);
    printf("mtype: %s\n", buf.mtext);

    if (msgctl(msgid, IPC_RMID, NULL) == -1) {/// IPC_RMID 从系统内核中移走消息队列。
        perror("msgctl()");
        exit(1);
    }

    exit(0);
}