/*************************************************************************
	File Name: pip-comm.c
	Author: lideliang
 ************************************************************************/

//利用管道实现两个进程之间的通信 
//程序一：建立管道并且写数据
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
int fd;
int i=0;
void  end(int s)
{
//关闭管道 
  close(fd);           
//删除管道
  unlink("my.pipe");   
  exit(-1);
}
main()
{
  signal(SIGINT,end);      
//建立管道
  mkfifo("my.pipe",0666);  
//打开管道
  fd=open("my.pipe",O_RDWR);       
    while(1)   
  {    
//每隔1秒写数据      
    sleep(1);  
    write(fd,&i,4);
    i++;
  }
}

