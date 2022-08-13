/*************************************************************************
  > File Name: mutex.c  加锁，数据同步
  > Author: couldtt(fyby)
  > Mail: fuyunbiyi@gmail.com
  > Created Time: 2013年12月15日 星期日 17时52分24秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sharedi = 0;
void *increse_num(void *);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/*
pthread_mutex_t的初始化
第一种 使用宏PTHREAD_MUTEX_INITIALIZER进行初始化，
第二种 使用函数pthread_mutex_init函数。
区别：
第一种方法仅局限于静态初始化的时候使用：将“声明”、“定义”、“初始化”一气呵成，
除此之外的情况都只能使用pthread_mutex_init函数。
*/

int main(){
    int ret;
    pthread_t thrd1, thrd2, thrd3;

    ret = pthread_create(&thrd1, NULL, increse_num, NULL);
    ret = pthread_create(&thrd2, NULL, increse_num, NULL);
    ret = pthread_create(&thrd3, NULL, increse_num, NULL);

    pthread_join(thrd1, NULL);
    pthread_join(thrd2, NULL);
    pthread_join(thrd3, NULL);

    printf("sharedi = %d\n", sharedi);

    return 0;
}

void *increse_num(void *ptr) {
    long i,tmp;
    for(i=0; i<100000; i++) {
        /*加锁*/
        if (pthread_mutex_lock(&mutex) != 0) {
            perror("pthread_mutex_lock");
            exit(EXIT_FAILURE);
        }
        tmp = sharedi;
        tmp = tmp + 1;
        sharedi = tmp;
        /*解锁*/
        if (pthread_mutex_unlock(&mutex) != 0) {
            perror("pthread_mutex_unlock");
            exit(EXIT_FAILURE);
        }
    }
}