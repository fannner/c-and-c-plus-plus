/*************************************************************************
	File Name: strcpy.c
	Author: lideliang
	Mail: lideliang@didichuxing.com 
	Created Time: 2017年04月28日 星期五 15时37分44秒
 ************************************************************************/

char *Strcpy(char *strDest,const char *strScr)
{
  assert((strDest!=NULL)&&(strScr!=NULL));
  char *address=strDest;
  while((*strDest++=*strScr++)!='\0')
  {
    *strDest='\0';
  }
  return address;
}
//返回值使用char*原因是：为了实现链式表达式，返回具体值

