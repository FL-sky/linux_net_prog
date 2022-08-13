#include <fcntl.h>
#include <sys/stat.h> /* For mode constants */
#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define MQNAME "/mqtest"


int main()
{

    int ret;

    ret = mq_unlink(MQNAME);
    if (ret == -1) {
        perror("mp_unlink()");
        exit(1);
    }

    exit(0);
}