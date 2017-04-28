/*************************************************************************
	File Name: strlen.c
	Author: lideliang
	Mail: lideliang@didichuxing.com 
	Created Time: 2017年04月28日 星期五 15时39分45秒
 ************************************************************************/

int strlen( const char *str ) //输入参数const　以下是引用片段：
{
　　assert( strt != NULL ); //断言字符串地址非0
　　int len=0; //注，一定要初始化。
　　while( (*str++) != '\0' )
　　{
　　     len++;
　　}
　　return len;
}
