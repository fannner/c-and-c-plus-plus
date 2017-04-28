/*************************************************************************
	File Name: c.c
	Author: lideliang
	Mail: lideliang@didichuxing.com 
	Created Time: 2017年04月28日 星期五 15时22分58秒
 ************************************************************************/

//description :fork()父子进程间资源访问
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
void deal(int s)
{
  int status;
  wait(&status);
  printf("回收中....\n");
  sleep(5);
  printf("回收完毕:%d\n",WEXITSTATUS(status));
}
main()
{
  if(fork()==0)
  {
    printf("子进程\n");
    sleep(10);
    printf("退出\n");
    exit(88);
  }
   
  else
  {
    signal(17,deal);
    while(1)
    {
      printf("父进程!\n");
      sleep(1);
    }
     
  }
}

