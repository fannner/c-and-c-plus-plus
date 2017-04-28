/*************************************************************************
	File Name: mul-thread.c
	Author: lideliang
	Mail: lideliang@didichuxing.com 
	Created Time: 2017年04月28日 星期五 15时39分08秒
 ************************************************************************/
//多线程的使用
#include<pthread.h>
#include<curses.h>
#include<math.h>
struct Achar{
  int x;
  int y;
  int speed;
  char a;
};

int stop=1;
pthread_t t[26];
pthread_t tid;
pthread_mutex_t m;//互斥量
struct Achar a[26];

void *run(void *d)
{
  int id;
  static idx=-1;
  idx++;
  id=idx;
  while(stop)
  {
    pthread_mutex_lock(&m);
    a[id].y+=a[id].speed;
    if(a[id].y>=LINES)
    {
      a[id].y=rand()%(LINES/4);
    }
    pthread_mutex_unlock(&m);
    sched_yield();
    usleep(100000);
  }
}

void *update(void *d)
{
  int i;
  while(1)
  {
    erase();
    for(i=0;i<26;i++)
    {
      mvaddch(a[i].y,a[i].x,a[i].a);
    }
    refresh();
    usleep(10000);
  }
}

main()
{
  int i;
  initscr();
  curs_set(0);
  noecho();
  keypad(stdscr,TRUE);
  for(i=0;i<26;i++)
  {
    a[i].x=rand()%COLS;
    a[i].y=rand()%LINES;
    //a[i].speed=1+rand()%10;
    a[i].speed=1;
    a[i].a='*';
  }
  pthread_mutex_init(&m,0);
  pthread_create(&tid,0,update,0);
  for(i=0;i<26;i++)
  {
    pthread_create(&t[i],0,run,0);
  }
  getch();
  stop=0;
  for(i=0;i<26;i++)
  {
    pthread_join(t[i],(void **)0);
  }
  pthread_join(tid,(void **)0);
  pthread_mutex_destroy(&m);
  endwin();
}
