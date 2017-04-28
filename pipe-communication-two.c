/*************************************************************************
	File Name: pipe-communication-two.c
	Author: lideliang
	Mail: lideliang@didichuxing.com 
	Created Time: 2017年04月28日 星期五 15时30分02秒
 ************************************************************************/

//程序二：打开管道并且读取数据
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
int fd;
int i;
void end(int s)
{
//关闭管道
  close(fd);
  exit(-1);
}
main()
{
  //int i; 
  //打开管道   
  signal(SIGINT,end);
  fd=open("my.pipe",O_RDWR);
  while(1)
  {
    read(fd,&i,4);
    printf("%d\n",i);
  }
}

