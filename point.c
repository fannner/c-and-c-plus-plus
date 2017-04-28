/*************************************************************************
	File Name: point.c
	Author: lideliang
	Mail: lideliang@didichuxing.com 
	Created Time: 2017年04月28日 星期五 15时38分13秒
 ************************************************************************/
//指针与引用参数传递以及函数指针问题

//例1
#include<iostream>
using namespace std;
void change(int *a,int &b,int c)
{
	c=*a;
	b=3;
	*a=2;
}
int main()
{
	int a=1,b=2,c=3;
	change(&a,b,c);
	cout<<a<<b<<c<<endl;
	return 0;
}
//输出结果是：2 3 3
//a是指针，修改它的内容也就修改了它的值；
//b是引用，不存在副本，故修改它的内容，值也会跟着改变；
//C传的是值，在函数体内被修改，但没有返回值，所以不改变.。


//例2：利用函数指针判断三个数的大小	
#include<stdio.h>
int max(int x,int y)
{
	return (x>y?x:y);
}
int main()
{
	int max(int ,int);
	int (*p)(int,int)=&max;
	int a,b,c,d;
	printf("请输入3个整数:\n");
	scanf("%d %d %d",&a,&b,&c);
	d=(*p)((*p)(a,b),c);
	printf("最大值是:%d\n",d);
	return 0;
}
