/*************************************************************************
	File Name: copy_file.c
	Author: lideliang
 ************************************************************************/
//description:模拟文件拷贝（利用信号屏蔽防止文件拷贝过程中外部信号中断拷贝）
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void handle(int s)
{
  printf("外部用户中断处理...!\n");
  sleep(3);
  printf("外部用户中断处理完毕!\n");
}
main()
{
  int i;
  sigset_t sigs,sigt,sigu;
  sigemptyset(&sigs);
  sigemptyset(&sigt);
  sigemptyset(&sigu);
  sigaddset(&sigs,SIGINT);
  signal(SIGINT,handle);
  sigprocmask(SIG_BLOCK,&sigs,0);
  for(i=0;i<10;i++)
  {
    printf("正在拷贝电影<%d>!\n",i);
    sleep(5);
    printf("电影<%d>拷贝完毕!\n",i);
    sigpending(&sigu);//查询被屏蔽的信号
    if(sigismember(&sigu,SIGINT))
    {
      sigsuspend(&sigt);//挂起处理外部中断
    }
  }
  printf("所有电影拷贝完毕\n");
  sigprocmask(SIG_UNBLOCK,&sigs,0);
  printf("结束\n");
}
