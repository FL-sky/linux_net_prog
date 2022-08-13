#include<stdio.h>
#include<stdlib.h>
extern char ** environ;
int main(int argc,char *argv[])          //argv[]相当于上面的argvec[]
{
    int j;
    char **ep;
    for(j = 0;j < argc;j++) {
        printf("argv[%d] = %s\n",j,argv[j]);
    }
    for(ep = environ;*ep != NULL;ep++) {    //environ是上面的envVec[]
        printf("environ:%s\n",*ep);
    }
    exit(EXIT_SUCCESS);
    return 0;
}