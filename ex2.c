#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <memory.h>
#include <sys/mman.h>

int main(){  
	int fd,page_size;
   	pid_t pid; 
   	//⑴显示当前系统的页面大小;
	page_size = getpagesize();//获取页面大小并显示
	printf("页面大小为： %d \n", page_size);	

   	fd=open("./f1",O_RDWR);//打开f1文件，权限为允许读写
   	char * src = (char *) mmap(NULL,page_size,PROT_WRITE,MAP_SHARED,fd,0);//将f1文件的内容只写映射到内存共享区
   	if(src == MAP_FAILED){  
		printf("error\n");
     		exit(1);
    	}
  	//⑵显示src的内容;
	printf("src的内容为： %s \n", src); 
  
   	//⑶使用malloc()函数申请一个页面大小的内存空间，地址返回到dst;
	char *dst = (char *)malloc(page_size);//申请一个当前页面大小的内存空间，返回一个指针，地址存储在dst中

   	//⑷使用memmove()函数将共享存储区的内容复制到dst;
	memmove(dst, src, page_size);//memmove函数内存拷贝，把共享存储区内容拷贝到dst中

   	//⑸显示dst的内容;
	printf("dst的内容为： %s \n", dst);

   	pid=fork();//创建子进程
   	if(pid==0){ /*  子进程空间  */
   	//⑹使用memchr()将dst中“W”之后内容的地址返回到temp;
	char *temp = (char *)memchr(dst, 'W', page_size);//从头开始搜寻dst所指的内存内容,发现“W”后，返回从“W”开始之后内容的指针

   	//⑺显示temp的内容及其内存起始地址;
	printf("temp的内容为： %s \n", temp);
	printf("temp的内存起始地址为： %p \n", temp);

   	//⑻将temp中前前4个字符用你的学号后四位替换替换,显示替换后的dst内容;
	memset(temp, '9', 4);//将temp所指向的内存中的前第4个字节的内容设置为"9"指定的ASCII值
	memset(temp, '1', 3);//将temp所指向的内存中的前第3个字节的内容设置为"1"指定的ASCII值
	memset(temp, '3', 2);//将temp所指向的内存中的前第2个字节的内容设置为"3"指定的ASCII值
	memset(temp, '1', 1);//将temp所指向的内存中的前第1个字节的内容设置为"1"指定的ASCII值
	printf("temp的内容为： %s \n", temp);
	printf("dst的内容为： %s \n", dst);

   	//⑼使用memmove()将修改后的dst的内容复制回src;
	memmove(src, dst, strlen(dst));//字节数通过strlen函数获取dst字节数，把dst修改后内容拷贝回src中

   	//⑽显示src的内容(包含PID及PPID)；
	printf("src的内容为： %s \n", src);
	printf("PID is: %d,  PPID is: %d,  The src value of end is: %s\n", getpid(), 
getppid(), src);    /*显示src指向的共享存储区内容*/
   	//⑾关闭之前打开的文件f1，释放dst;
	close(fd);//关闭文件f1
	free(dst);//释放共享存储区
   	}
   	else if(pid>0){  /* 父进程空间  */
   	wait(NULL);  
  	//⑿使用memset()将共享存储区src中前2个字符用“QQ”替换，并显示替换后的内容(包含PID及PPID);
	memset(src, 'Q', 2);//将src所指向的内存中的前第2个字节的内容设置为"Q"指定的ASCII值
	memset(src, 'Q', 1);//将src所指向的内存中的前第1个字节的内容设置为"Q"指定的ASCII值
	printf("src的内容为： %s \n", src);
	printf("PID is: %d,  PPID is: %d,  The src value of end is: %s\n", getpid(), 
getppid(), src);    /*显示src指向的共享存储区内容*/

   	//⒀显示文件f1的最终内容;
	printf("文件f1的最终内容为：\n");
	system("od -c f1");
   	}   
   	printf("PID is: %d,  PPID is: %d,  The src value of end is: %s\n", getpid(), 
getppid(), src);    /*显示src指向的共享存储区内容*/
   	if(munmap(src,page_size)==0)     /*释放共享存储区*/
    	{ printf("PID is: %d,  PPID is: %d,munmap success\n\n",getpid(), getppid());}
   	else
    	{ printf("PID is: %d,  PPID is: %d,  munmap failed\n\n",getpid(), getppid());}
}

