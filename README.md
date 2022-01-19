# OperatingSystem-EX2

                                       操作系统实验二  内存管理
                                               
一、 实验目的 

本实验需要完成两个并发进程通过共享存储器机制对文件的修改。通过本次实验，能够使学生进一步熟练使用Linux进程通信及内存管理相关函数和系统调用进行编程，进而掌握通过共享存储器方式实现进程间通信的基本原理及内存管理的基本功能。 
  
二、 实验环境 

操作系统：任何 Unix/Linux 或 MAC 

编译器： gcc

三、 实验内容

1．	打开当前目录下的文件f1，使用系统调用mmap()创建共享存储区，大小为一个页面，将文件f1映射进内存，地址返回到src。

2．	使用malloc()函数申请一个内存块，地址返回到dst。申请成功后，使用memmove()函数将共享存储区的内容复制到dst。

3．	使用fork()调用创建一个新进程，父进程先阻塞自己。

4．	子进程使用memchr()搜索dst中字符“W”出现的位置，返回到temp，利用temp将“W”后4个字符用你的学号后四位替换。修改后的dst的内容使用memmove()复制回src，关闭文件f1，释放dst。 

5．	父进程使用memset()将共享存储区src中前2个字符用QQ替换。最后显示文件f1的内容（经过两次修改）。

6．	解除文件与内存的映射，关闭文件f1，释放dst。

四、 实验框架

int main()

{  int fd,page_size;

   pid_t pid; 
   
   ⑴显示当前系统的页面大小;
   
   fd=open("./f1",O_RDWR);
   
   char * src = (char *) mmap(NULL,page_size,PROT_WRITE,MAP_SHARED,fd,0);
   
   if(src= =MAP_FAILED)
   
   {  printf("error\n");
   
     exit(1);
     
    }
    
   ⑵显示src的内容;   
   
   ⑶使用malloc()函数申请一个页面大小的内存空间，地址返回到dst;
   
   ⑷使用memmove()函数将共享存储区的内容复制到dst;
   
   ⑸显示dst的内容;
   
   pid=fork();
   
   if(pid==0){ /*  子进程空间  */
   
   ⑹使用memchr()将dst中“W”之后内容的地址返回到temp;
   
   ⑺显示temp的内容及其内存起始地址;
   
   ⑻将temp中前前4个字符用你的学号后四位替换替换,显示替换后的dst内容;
   
   ⑼使用memmove()将修改后的dst的内容复制回src;
   
   ⑽显示src的内容(包含PID及PPID)；
   
   ⑾关闭之前打开的文件f1，释放dst;
   
   }
   else if(pid>0){  /* 父进程空间  */
   
   wait(NULL);  
   
   ⑿使用memset()将共享存储区src中前2个字符用“QQ”替换，并显示替换后的内容(包含PID及PPID);
   
   ⒀显示文件f1的最终内容;
   
   }   
   
   printf("PID is: %d,  PPID is: %d,  The src value of end is: %s\n", getpid(), 
   
getppid(), src);    /*显示src指向的共享存储区内容*/

   if(munmap(src,page_size)==0)     /*释放共享存储区*/
   
    { printf("PID is: %d,  PPID is: %d,munmap success\n\n",getpid(), getppid());}
    
   else
   
    { printf("PID is: %d,  PPID is: %d,  munmap failed\n\n",getpid(), getppid());}
    
}


                                               
