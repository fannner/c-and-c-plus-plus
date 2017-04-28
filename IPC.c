/*************************************************************************
	File Name: IPC.c
	Author: lideliang
 ************************************************************************/

//----------------方式：管道、消息队列、共享内存、信号量、套接口----------------

/*
         管道：进程间通信最古老的方式，包括无名管道和有名管道，前者用于父子进程间的通信，后者用于同一台机器上的任意两个进程间通信。
*/

/*1>无名管道：只能在父子进程间通信，fd[0]：只读；fd[1]：只写。
函数原型：int pipe(int pipefd[2]);
例：
//建立两个子进程，一个负责计算1-5000的素数，另外一个负责计算5001-10000，父进程负责存储
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>//要用到文件
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sched.h>
int idx=0;
int fddata;
void handle(int s)
{
  int status;
  if(s==SIGCHLD)
  {
    wait(&status);//回收节点
    idx++;
     if(idx==2)
    {
      close(fddata);
      printf("任务完成\n");
      exit(-1);
    }
  }
}
int isprimer(int data)
{
  int i=2;
  for(;i<data;i++)
  {
    if(data%i==0)
    {
      return 0;
    }
  }
  return 1;
}
main()
{
  int a,b;
  int id=1;
  int fd[2];
  signal(SIGCHLD,handle);
  pipe(fd);
  while(1)
  {
    if(id==1)
      {
	a=2;
	b=5000;
      }
      if(id==2)
      {
	a=5001;
	b=10000;
      }
    if(fork())
    {
      //父进程
      id++;
      if(id>2)
      {
	break;
      }
      continue;
    }
    else
    {
      //子进程
      int i;
      close(fd[0]);
      for(i=a;i<=b;i++)
      {
	if(isprimer(i))
	{
	  write(fd[1],&i,sizeof(int));
	}
	sched_yield();
      }
      printf("%d任务完成!\n",getpid());
      
      exit(0);
    }
  }
  int re;
  char buf[20];
  close(fd[1]);
  fddata=open("result.txt",O_RDWR|O_CREAT,0666);
  while(1)
  {
    int r;
    //打开文件,准备存储
    if(r=read(fd[0],&re,sizeof(int))==0)
    {
    sprintf(buf,"%d\n",re);//转化成文本
    write(fddata,buf,strlen(buf));
    sched_yield();
    }
  }
}
/*2>有名管道：有名管道提供一个路径名，这样在进程中通过这个路径名就可以访问，实现彼此通信；它严格遵循FIFO原则；
函数原型：int mkfifo(const char *pathname, mode_t mode);
例：
*/
//程序A:
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<signal.h>
int fd;
int i=0;
void end(int s)
{
  //关闭管道
  close(fd);
  //删除管道
  unlink("my.pipe");
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
    //每隔一秒钟写一个数据
    sleep(1);
    write(fd,&i,4);
    i++;
  }
  
}
//程序B：
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<signal.h>
int fd;
int i=0;
void end(int s)
{
  //关闭管道
  close(fd);
  //删除管道
  unlink("my.pipe");
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
    //每隔一秒钟读一个数据
    sleep(1);
read(fd,&i,4);
printf(“%d\n”,i);
    i++;
  }
}
/*
         消息队列：消息队列的内核持续性要求每个消息队列在系统范围内对应唯一的键值key。
*/
//数据结构
struct msgbuf
{
  long type;
  char data[32];
};
//例：
//------------程序A：-----------
#include<stdio.h>
#include<unistd.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
struct msgbuf
{
  long type;
  char data[32];
};
main()
{
  key_t key;
  int msgid;
  int i;
  //创建消息队列
  key=ftok(".",255);
  if(key==-1) printf("ftok error:%m\n"),exit(-1);
  msgid=msgget(key,IPC_CREAT|IPC_EXCL|0666);
  if(msgid==-1) printf("get error:%m\n"),exit(-1);
  printf("msggid:%d\n",msgid);
  //构造消息
  struct msgbuf msg;
  //发送消息
  for(i=1;i<=10;i++)
  {
    bzero(msg.data,sizeof(msg.data));
    msg.type=1;
    sprintf(msg.data,"Massage:%d",i);
    
    msgsnd(msgid,&msg,sizeof(msg.data),0);
  }
  //exit(0);
  //删除消息
 // msgctl(msgid,IPC_RMID,0);
}
//---------程序B：----------
#include<stdio.h>
#include<unistd.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
struct msgbuf
{
  long type;
  char data[32];
};
main()
{
  key_t key;
  int msgid;
  int i;
  //得到消息队列
  key=ftok(".",255);
  if(key==-1) printf("ftok error:%m\n"),exit(-1);
  msgid=msgget(key,0);
  printf("msggid:%d\n",msgid);
  if(msgid==-1) printf("get error:%m\n"),exit(-1);
  //构造消息
  struct msgbuf msg;
  //接受消息
  while(1)
  {
    bzero(&msg,sizeof(msg));
    msgrcv(msgid,&msg,sizeof(msg.data),1,0);//第四个参数代表所取消息类型
    printf("%s\n",msg.data);
  }
}

/*
         共享内存：它是运行在同一台机器上的进程间通信最快的方式，因为数据不需要在不同的进程间复制；通常由一个进程创建一块共享内存区，其余进程对这块内存区进行读写。
*/
//例：
//----------程序A：-------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/shm.h>
#include<sys/ipc.h>
key_t key;
int shmid;
int *p;
int i=0;
void deal(int s)
{
  if(s==SIGINT)
  {
   //4.卸载共享内存shmdt
    shmdt(p);
  //5.删除共享内存shctl
    shmctl(shmid,IPC_RMID,0);
    exit(0);
  }
}
main()
{
  signal(SIGINT,deal);
  //1.创建共享内存shmget
  key=ftok(".",255);//'.'代表当前目录
  //if(key=-1) printf("ftok error:%m\n"),exit(-1);
  shmid=shmget(key,4,IPC_CREAT|IPC_EXCL|0666);
  if(shmid==-1) printf("get error:%m\n"),exit(-1);
  //2.挂载共享内存shmat
  p=shmat(shmid,0,0);
  if(p==(int*)-1) printf("at error:%m\n"),exit(-1);
  //3.访问共享内存
  while(1)
  {
    *p=i;
    sleep(3);
    i++;
  }
}

//-------------程序B：-----------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/shm.h>
#include<sys/ipc.h>
key_t key;
int shmid;
int *p;
void deal(int s)
{
  if(s==SIGINT)
  {
   //4.卸载共享内存shmdt
    shmdt(p);
    exit(0);
  }
}
main()
{
  signal(SIGINT,deal);
  //1.创建共享内存shmget
  key=ftok(".",255);
  //if(key=-1) printf("ftok error:%m\n"),exit(-1);
  shmid=shmget(key,4,0);
  if(shmid==-1) printf("get error:%m\n"),exit(-1);
  //2.挂载共享内存shmat
  p=shmat(shmid,0,0);
  if(p==(int*)-1) printf("at error:%m\n"),exit(-1);
  //3.访问共享内存
  while(1)
  {
    sleep(1);
    printf("%d\n",*p);
  } 
}

/*
          信号量：又称信号灯，用来协调不同进程间的数据对象的，是在多线程环境下使用的一种设施，可以用来保证两个或者多个关键代码段不被并发调用。
*/
struct sembuf{
int sem_num；//下标
int sem_op;
int sem_flg;
};
//例：
//---------程序A：-----------
#include<stdio.h>
#include<unistd.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<stdlib.h>
union semun {
       int val;    
       struct semid_ds *buf;    
       unsigned short  *array;  
       struct seminfo  *__buf;  
};
main()
{
  key_t key;
  int semid;
  union semun v;
  int r;
  struct sembuf op[1];
  //1.创建信号量
  key=ftok(".",99);
  if(key==-1) printf("ftok err:%m\n"),exit(-1);
  semid=semget(key,1/*信号量数组个数*/,IPC_CREAT|IPC_EXCL|0666);
  //semid=semget(key,1,0);//得到信号量
  if(semid==-1) printf("get err:%m\n"),exit(-1);
 
  //2.初始化信号量
  v.val=2;//任意值，被下面op[0].sem_op=-1;操作
  semctl(semid,0,SETVAL,v);//设置信号量,其中第二个参数是要执行操作信号量的编号
  if(r==-1) printf("初始化失败!\n"),exit(-1);
  //3.对信号量进行阻塞操作
  //3.1定义操作
  op[0].sem_num=0;//信号量的下标
  op[0].sem_op=-1;//信号量的操作单位和类型
  op[0].sem_flg=0;
  while(1)
  {
    semop(semid,op,1);//第三个参数，即op数组个数
    printf("解除阻塞!\n");
  }
  //4.删除信号量（可以不删除）
 semctl(semid,0,IPC_RMID,0);
  
}
//------------程序B：-----------
#include<stdio.h>
#include<unistd.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<stdlib.h>
union semun {
       int val;    
       struct semid_ds *buf;    
       unsigned short  *array;  
       struct seminfo  *__buf;  
};

main()
{
  key_t key;
  int semid;
  union semun v;
  //int r;
  struct sembuf op[1];
  //1.创建信号量
  key=ftok(".",99);
  if(key==-1) printf("ftok err:%m\n"),exit(-1);
  semid=semget(key,1,0);//得到信号量
  if(semid==-1) printf("get err:%m\n"),exit(-1);
  //2.初始化信号量
  //3.对信号量进行阻塞操作
  //3.1定义操作
  op[0].sem_num=0;//信号量的下标
  op[0].sem_op=1;//信号量的操作单位和类型
  op[0].sem_flg=0;
  while(1)
  {
    semop(semid,op,1);
    sleep(1);
  }
  //4.删除信号量（可以不删除）
}

/*
         套接口socket：网络通信方式
*/
/*阻塞与非阻塞：
1>阻塞：
简单的的说，阻塞就是当你调用accept()，send()或者是recv()等过程后，程序必须要等待一个返回结果程序才会继续执行下去，在这种情况下，如果你是单线程的，那么你的程序就会完全挂起。
2>非阻塞：
非阻塞套接字是指，执行此套接字的网络调动时，不管是否执行成功，都立即返回；
简单的说，同步阻塞常用于连接较少流量较大的地方；非阻塞常用于连接较多，流量较少的地方。
使用selece()函数，函数原型；nt PASCAL FAR select( int nfds, fd_set FAR* readfds,　fd_set FAR* writefds, fd_set FAR* exceptfds,　const struct timeval FAR* timeout);
在讲解select()函数之前我们先讲一下fd_set.
它表示一个集合.具体的讲是一个文件描述符的集合.在此例中都把它理解为套接字描述符.
在Unix中一切都是文件.包括输入设备键盘.硬盘上的文件.还有专门用于网络传输的socket(套接字)等等.所以.在这里都把它当作是socket套接字.
那么文件描述符或者是套接字描述符就好比是WINDOWS下面的句柄.
fd_set的定义如下:
struct fd_set
{
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; u_int&nbsp;&nbsp; fd_count;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; SOCKET&nbsp; fd_array[FD_SETSIZE];&nbsp;&nbsp;
};
对这些集合的操作都是通过一些特定的宏来完成的.
&nbsp;&nbsp;&nbsp; FD_ZERO(fd_set *set)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; //清除一个文件描述符集合
　　&nbsp;&nbsp;&nbsp; FD_SET(int fd, fd_set *set)&nbsp;&nbsp; //把fd添加到集合set中
　　&nbsp;&nbsp;&nbsp; FD_CLR(int fd, fd_set *set)&nbsp;&nbsp; //从集合set中移去fd
　　&nbsp;&nbsp;&nbsp; FD_ISSET(int fd, fd_set *set) //测试fd是否在集合set中
现在再来说说select()函数,以及它的用法.
该函数的功能就是用来等待套接字(这里只讨论套接字)状态的改变.
参数nums代表最大的套接字描述符加1.
参数reads,writes和excepts是套接字描述符集合,用来回传该套接字描述符的读,写或例外的状况.
参数timeout指向一个timeval结构.它用来设定select等待的时间.可以设置到微秒级.1秒等于1000毫秒.1毫秒等于1000微秒.虽然可以精确到1微秒.但这只是理想的.实际上跟系统还有硬件有关.
timeval结构的定义如下:
struct timeval
{
　　 int tv_sec;
　　 int tv_usec;&nbsp;
};
当然你可以将参数timeout设置成NULL,那么它将永远不会超时.
成功返回套接字描述状态改变的个数,如果返回0表示在套接字描述符状态改变前已经超过参数timeout设定的时间.当有错误发生时则返回-1.此时参数reads,writes,execepts和timeout的值变得不可预测.
同时有错误发生时,它会设置全局错误变量.常见错误有下面几种.
EBADF 套接字描述符无效或该套接字已关闭
EINTR 此调用被信号所中断
EINVAL 参数n 为负值
ENOMEM 核心内存不足*/
