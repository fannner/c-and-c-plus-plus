/*************************************************************************
	File Name: algorithm.c
	Author: lideliang
 ************************************************************************/
//几种著名算法实现总结
/*
用数组处理Fibonacci问题
*/
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	int i;
	int f[20]={1,1};
	for(i=2;i<20;i++)
		f[i]=f[i-2]+f[i-1];
	for(i=0;i<20;i++)
	{
		if(i%5==0)  cout<<endl;
		  cout<<setw(8)<<f[i];
	}
	cout<<endl;
	return 0;
}

/*
用逻辑表达式求解闰年
*/
#include <iostream>
using namespace std;
int main()
{
	int year;
	bool leap;
	cout<<"please enter year:";
	cin>>year;
	if((year%4==0&&year%100!=0)||year%400==0)
       leap=true;
	else
		leap=false;
	
	if(leap)
		cout<<year<<" is ";
	else
		cout<<year<<" is not ";
	cout<<"a leap year."<<endl;
    return 0;
}

/*
用布尔变量prime求素数
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main()
{
	int m,k,i,n=0;
    bool prime;
	for(m=1;m<=1000;m=m+2)
	{
		prime=true;
		k=int(sqrt(m));
		for(i=2;i<=k;i++)
			if(m%i==0)
			{
				prime=false;
				break;
			}
			if(prime)
			{
				cout<<setw(5)<<m;
				n=n+1;
			}
			if(n%10==0) cout<<endl;
	}
	cout<<endl;
	return 0;
}

/*
用布尔变量leap求解闰年
*/
#include <iostream>
using namespace std;
int main()
{
	int year;
	bool leap;
	cout<<"please enter year:";
	cin>>year;
	if(year%4==0)
	{
		if(year%100==0)
	{
			if(year%400==0)
	               leap=true;
	        else leap=false;}
	    else
		 leap=true;}
	else
		 leap=false;
	if(leap)
		cout<<year<<" is ";
	else
		cout<<year<<" is not ";
	cout<<"a leap year."<<endl;
    return 0;
}

/*
选择法排序一组数
*/
#include <iostream>
using namespace std;
int main()
{
	void select_sort(int array[],int n);
    int a[10],i;
	cout<<"enter the originl aray:"<<endl;
	for(i=0;i<10;i++)
		cin>>a[i];
	cout<<endl;
	select_sort(a,10);
	cout<<"the sorted array:"<<endl;
	for(i=0;i<10;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}


void select_sort(int array[],int n)
{
	int i,j,k,t;
	for(i=0;i<n-i;i++)
	{
		k=i;
		for(j=i+1;j<n;j++)
			if(array[j]<array[k])  k=j;
			t=array[k];array[k]=array[i];array[i]=t;
	}
}

/*
统计一篇文章中各字符个数
*/
#include <iostream>
using namespace std;
int main()
{
	int i,j,upper,lower,digit,space,others;
	char text[3][80];
	upper=lower=digit=space=others=0;
	for(i=0;i<3;i++)
	{
		cout<<"please input line"<<i+1<<endl;
		gets(text[i]);
		for(j=0;j<80&&text[i][j]!='\0';j++)
		{
			if(text[i][j]>='A'&&text[i][j]<='Z')
				upper++;
			else if(text[i][j]>='a'&&text[i][j]<='z')
				lower++;
			else if(text[i][j]>='0'&&text[i][j]<='9')
				digit++;
			else if(text[i][j]==' ')
				space++;
			else
				others++;
		}
	}
	cout<<"upper case:"<<upper<<endl;
	cout<<"lower case:"<<lower<<endl;
	cout<<"digit     :"<<digit<<endl;
	cout<<"space     :"<<space<<endl;
	cout<<"others    :"<<others<<endl;
	return 0;
}

/*
打擂台法求矩阵中最大元素及其行列号
*/
#include <iostream>
using namespace std;
int main()
{
	int i,j,row=0,colum=0,max;
	int a[3][4]={{5,12,23,56},{19,28,37,46},{-12,-34,6,8}};
	max=a[0][0];
	for(i=0;i<=2;i++)
		for(j=0;j<=3;j++)
			if(a[i][j]>max)
			{
				max=a[i][j];
				row=i;
				colum=j;
			}
			cout<<"max="<<max<<",row="<<row<<",colum="<<colum<<endl;
			return 0;
}

/*
用指针类型的数据作函数参数比较大小
*/
#include<iostream>
using namespace std;
int main()
{
	void exchange(int *,int *,int *);
	int a,b,c,*p1,*p2,*p3;
    cin>>a>>b>>c;
    p1=&a;p2=&b;p3=&c;
	exchange(p1,p2,p3);
	cout<<a<<" "<<b<<" "<<c<<endl;
	return 0;
}

void exchange(int *q1,int *q2,int *q3)
	void swap(int *,int *);
{
	if(*q1>*q2) swap(q1,q2);
	if(*q1>*q3) swap(q1,q3);
	if(*q2>*q3) swap(q2,q3);
}

void swap(int *pt1,int *pt2)
{
	int temp;
	temp=*pt1;
	*pt1=*pt2;
	*pt2=temp;
}
