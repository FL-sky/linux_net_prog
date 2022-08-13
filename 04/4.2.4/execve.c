// https://blog.csdn.net/yangbodong22011/article/details/50197785

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

int main(int argc,char *argv[])
{
    ///char *argVec[10];                               //参数数组
    char *argVec[10]; 
    char *envVec[] = {"环境参数1","环境参数2",NULL};  //环境变量数组
    argVec[0] = argv[1];
    //argVec[0] = "envargs";
    argVec[1] = "hello world";
    argVec[2] = "goodbye";
    argVec[3] = argVec[4] = argVec[5] = "";
    argVec[6] = argVec[7] =  "hellC";
    printf("argv[1]=%s\n",argv[1]);
    execve(argv[1],argVec,envVec);        //分别传入三个参数
    return 0;
}

/*
shell脚本支持的参数为$1...$9，一共9个参数。
一般来说一个脚本最多9个参数，这个数量足够用了
*/