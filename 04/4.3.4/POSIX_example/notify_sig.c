#include <pthread.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static mqd_t mqdes;

void mq_notify_proc(int sig_num)
{
    /* mq_notify_proc()是信号处理函数， 当队列从空变成非空时，会给本进程发送信号， 触发本函数执行。 */

    struct mq_attr attr;
    void *buf;
    ssize_t size;
    int prio;
    struct sigevent sev;

    /* 我们约定使用SIGUSR1信号进行处理， 在此判断发来的信号是不是SIGUSR1。 */
    if (sig_num != SIGUSR1) {
        return;
    }

    /* 取出当前队列的消息长度上限作为缓存空间大小。 */
    if (mq_getattr(mqdes, &attr) < 0) {
        perror("mq_getattr()");
        exit(1);
    }

    buf = malloc(attr.mq_msgsize);
    if (buf == NULL) {
        perror("malloc()");
        exit(1);
    }

    /* 从消息队列中接收消息。 */
    size = mq_receive(mqdes, buf, attr.mq_msgsize, &prio);
    if (size == -1) {
        perror("mq_receive()");
        exit(1);
    }

    /* 打印消息和其优先级。 */
    printf("msq: %s, prio: %d\n", buf, prio);

    free(buf);

    /* 重新注册mq_notify，以便下次可以出触发。 */
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGUSR1;
    if (mq_notify(mqdes, &sev) == -1) {
        perror("mq_notify()");
        exit(1);
    }

    return;
}

int main(int argc, char *argv[])
{
    struct sigevent sev;

    if (argc != 2) {
        fprintf(stderr, "Argument error!\n");
        exit(1);
    }

    /* 注册信号处理函数。 */
    if (signal(SIGUSR1, mq_notify_proc) == SIG_ERR) {
        perror("signal()");
        exit(1);
    }

    /* 打开消息队列，注意此队列需要先创建。 */
    printf("argv[1]=%s\n",argv[1]);
    mqdes = mq_open(argv[1], O_RDONLY);
    if (mqdes == -1) {
        perror("mq_open()");
        exit(1);
    }

    /* 注册mq_notify。 */
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGUSR1;
    if (mq_notify(mqdes, &sev) == -1) {
        perror("mq_notify()");
        exit(1);
    }

    /* 主进程每秒打印一行x，等着从消息队列发来异步信号触发收消息。 */
    while (1) {
        printf("x\n");
        sleep(1);
    }
}