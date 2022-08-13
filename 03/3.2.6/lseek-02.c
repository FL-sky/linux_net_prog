/*文件lseek-02.c,使用lseek()函数构建空洞文件*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include<string.h>
void printFile(char *filename){
	static int cnt=0;
	printf("---%d---\n",++cnt);
	FILE *fp = fopen(filename,"r");
	char ch;
	int i=0;
	while ((ch = fgetc(fp))!=EOF)
	{
		if(ch==0){
			putchar('.');
		}
		else{
			printf("%c",ch);
		}
		if(++i==16){
			puts("");
			i=0;
		}
	}
	fclose(fp);
	puts("\n---\n");
}
int main(void)
{
	int fd = -1;
	ssize_t size = -1;
	off_t offset = -1;
	char buf1[32]="01234567";							/*存放数据的缓冲区*/
	char buf2[32]="ABCDEFGH";
	char buf3[32]="!@#$^^";
	char buf4[32]="Qscesz";
	char filename[] = "hole.txt";  					/*文件名*/
	int len = 8; 
	
	fd = open(filename,O_RDWR|O_CREAT,S_IRWXU); 	/*创建文件hole.txt*/
	if(-1 == fd){ 									/*创建文件失败*/		
	  return -1;
	}
	len=strlen(buf1);
	size = write(fd, buf1,len); 	/*将buf1中的数据写入到文件Hole.txt中*/
	if(size != len){ 								/*写入数据失败*/	
		return -1;	
	}

	printFile(filename);

	offset = lseek(fd, 32, SEEK_SET); 	/*设置文件偏移量为绝对值的32*/
	if(-1 == offset){ 				/*设置失败*/		
		return -1;
	}

	len=strlen(buf2);
	size = write(fd, buf2,len); 	/*将buf2中的数据写入到文件hole.txt中*/
	if(size != len){ 				/*写入数据失败*/	
		return -1;	
	}

	printFile(filename);
	
	//-----
	offset = lseek(fd, 0, SEEK_CUR);
	if(-1 == offset){ 				/*设置失败*/		
		return -1;
	}
	len=strlen(buf3);
	size = write(fd, buf3,len); 	/*将buf2中的数据写入到文件hole.txt中*/
	if(size != len){ 				/*写入数据失败*/	
		return -1;	
	}

	printFile(filename);
	
	//-----
	offset = lseek(fd, 3, SEEK_END);
	if(-1 == offset){ 				/*设置失败*/		
		return -1;
	}
	len=strlen(buf4);
	size = write(fd, buf4,len); 	/*将buf2中的数据写入到文件hole.txt中*/
	if(size != len){ 				/*写入数据失败*/	
		return -1;	
	}

	printFile(filename);
	
	//-----
	offset = lseek(fd, 20, SEEK_SET);
	if(-1 == offset){ 				/*设置失败*/		
		return -1;
	}
	len=strlen(buf4);
	size = write(fd, buf4,len); 	/*将buf2中的数据写入到文件hole.txt中*/
	if(size != len){ 				/*写入数据失败*/	
		return -1;	
	}

	printFile(filename);
	
	//
	close(fd); 						/*关闭文件*/

	return 0;
}
