/*************************************************************************
	File Name: overload.cpp
	Author: lideliang
	Mail: lideliang@didichuxing.com 
	Created Time: 2017年04月28日 星期五 15时43分48秒
 ************************************************************************/
//C++构造函数和运算符重载程序例案
/*
C++构造函数和运算符重载程序例案
*/
//程序1：
#include<iostream>
#include<string>
using namespace std;
class Person{
    string name;
    bool gender;
    int age;
    Person *lover;//注意这里是指针
public:
    Person(const char *n,bool g)
                :name(n),gender(g),age(0),lover(NULL){}
    void show();
    void growup(int years);
    void marry(Person &p);
};
void Person::show()
{
    cout<<"大家好，我是"<<(gender?"帅哥":"美女")<<name<<',';
    cout<<"我今年"<<age<<"岁!";
    if(lover==NULL)
        cout<<"目前单身!"<<endl;
    else
        cout<<"爱人是"<<lover->name<<’!’<<endl;
    cout<<endl;
}
void Person::growup(int years)
{
    age+=years;
}
void Person::marry(Person &p)
{
    lover=&p;
    p.lover=this;//this表示当前对象
    cout<<name<<"和"<<p.name<<"结婚"<<endl; 
}
 
int main()
{
    Person a("芙蓉",false);
    Person b("春哥",true);
    a.growup(19);
    a.show();
    Person e();//声明一个函数,所以一般不要在声明一个对象之后加括号(),放置引起歧义
    //e().show();
    b.marry(a);
    a.show();
}
 
Person e()
{
    string name;
    bool gender;
    int age;
    cout<<"请出入姓名、性别和年龄:";
    cin>>name>>gender>>age;
    Person input(name.c_str(),gender);//类似于Person b("春哥",true);
    input.growup(age);
    return input;
}
 
//输出结果：
//大家好，我是美女芙蓉,我今年19岁!目前单身
 
//春哥和芙蓉结婚
//大家好，我是美女芙蓉,我今年19岁!爱人是春哥
 
 
 
---------------------------------------------------------------------------------------------------------------------------------
//程序2：
#include<iostream>
using namespace std;
class fraction{
  int a;
  int b;
public:
  fraction(int m=0,int n=1):a(m),b(n){}
  friend ostream &operator<<(ostream &o,const fraction &f)
  {
    o<<f.a<<'/'<<f.b;
    return o;
  }
  friend fraction operator+(const fraction &A,const fraction& B)
  {//这里返回值不加&，因为返回值需要复制，重新开辟空间保存，因为返回局部变量res，出了作用域就会释放，故需要复制一份
    fraction res(A.a*B.b+B.a*A.b,A.b*B.b);
    return res;
  }
   
  /*
  //这里写成友员
  friend fraction operator*(const fraction &A,const fraction& B)
  {//这里返回值不加&，因为返回值需要复制，重新开辟空间保存
    fraction res(A.a*B.a,A.b*B.b);
    return res;
  }
  */
  //这里写成成员函数,可以使用类里面的成员（作为当前对象）,成员比友员少一个参数
  fraction operator*(const fraction &A)
  {
    return fraction (a*A.a,b*A.b);//匿名对象
  }
};
int main()
{
  fraction x(2,3);
  fraction y(3,4);
  cout<<x+y<<endl;//由于这里是x+y,所加的结果是一个临时值，
  //故对于重载运算符+、<<里面都必须加const 防止临时值消失
  cout<<x*y<<endl;
}
 
 
 
 
---------------------------------------------------------------------------------------------------------------------------------
//3.临时对象
 
Teacher t1(“A”,102);
Teacher t2=t1;//将会调用拷贝构造函数
Teacher t3=Teacher (“B”,101);
//用临时对象来初始化一个新对象，编译器一般会优化成直接用创建临时对象的参数来创建新对象
//临时对象，当时创建，当时释放，所以建议使用临时对象
 
 
 
 
------------------------------------------------------------------------------------------------------------------------------程序3：
//一般情况下，一个函数可以写成成员函数，也可以写成非成员函数
//当写成成员函数时，可以少一个参数(当前对象this),如下面return !a,其实就是!(this->a)
#include<iostream>
using namespace std;
class fraction{
  int a;
  int b;
public:
  fraction(int m=0,int n=1):a(m),b(n){}
  friend ostream &operator<<(ostream &o,const fraction &f)
  {
    o<<f.a<<'/'<<f.b;
    return o;
  }
  friend fraction operator~(const fraction& f);//友员，不是成员函数，必须有参数(表示哪个对象)
  bool operator!()const//这里写成成员函数，故参数为空，表示当前对象
  {
    return !a;
    //return !(this->a);
  }
};
fraction operator~(const fraction &f)//因为是非成员函数，所以不需要加”类名::”
{
  return fraction (f.b,f.a);
}
int main()
{
  fraction f1(0,3);
  cout<<f1<<endl;
  cout<<!f1<<endl;
  cout<<~f1<<endl;
  cout<<~10<<endl;
  return 0;
}
 
 
 
 
//程序4：
/*什么时候需要重载“=”，以及什么时候要写拷贝构造函数和析构函数：
 当有指针成员指向动态内存时；
 因为动态分配了内存所以要释放(即需要写析构函数)
 */
//注意：因为类里面有指针变量，所以必须要写拷贝构造函数；
//这是因为，如果不写，那么将调用默认拷贝构造函数，默认拷贝构造函
//只是复制，其他什么也不做，这样两个指针指向同一片空间，但是又
//因为构造了两个对象，会调用析构函数，就会使得同一片空间被释放
//两次(double free),产生错误；而自己写的拷贝构造函数，会重新
//开辟空间，这样就不会倒置错误
#include<iostream>
using namespace std;
class Stack{
  int *a;//指针成员，会动态的指向内存 
  int max;
  int len;
public:
  Stack(int n):a(new int[n]),max(n),len(0){}
  Stack(const Stack& s):a(new int [s.max]),max(s.max),len(s.len){}
  ~Stack(){delete []a;}
  Stack& push(const int& m)
  {
    if(len>=max) throw 0/*"栈已满!"*/;
    a[len++]=m;
    return *this;
  }
  void print()const/*加const防止当前对象被修改*/
  {
    for(int i=0;i<len;i++)
      cout<<a[i]<<' ';
    cout<<endl;
  }
  //对“=”进行运算符重载,"="只能写成成员函数
  //其中一个参数默认为当前对象的参数
  //重载“=”表示动态赋值，故要重新匹配空间，保证和原来的空间大小一样
  Stack &operator=(const Stack &/*引用表示不需要在传参数的时候复制*/rs)
  {
    delete []a;
    a=new int [rs.max];
    max=rs.max;
    len=rs.len;
    for(int i=0;i<len;i++) a[i]=rs.a[i];
    //return *this;//可要可不要
  }
  
};
int main()
{
  Stack t1(10);
  //注意：这里对于t2的初始化必须要在t1.push()之前
  //否则如果将Stack t2(t1);放在t1.push()之后，由于已经入栈，故栈的空间已经被占用
  Stack t2(t1);
  t1.push(1).push(2).push(3).push(4);
  t2.push(5).push(6).push(7).push(8);
  t1.print();
  t2.print();
  Stack t3(6);
  t3=t2;
  t3.print();
}
 
 
 
 
//程序5：
//重载前”++”和后”++”：
//规定后”++”参数多一个(int){表示哑元},由此区别前++
#include<iostream>
using namespace std;
class F{
  int a;
  int b;
public:
  F(int m=0,int n=1):a(m),b(n){}
  F &operator++(){a+=b;return *this;}//前++,返回值有引用，新值就作为当前值用，不用copy
  F operator++(int){F old(*this);a+=b;return old;}//后++,没有引用，用旧值计算并保留旧值，故  //需要copy
  //注意：重载“<<”(输出运算符)时，如果写成两个参数，就表示不是成员函数，所以必//须加friend，表示友元，才能访问类里面的私有成员，同时第二个参数对于重载后”++” 和”~”的时候必须要加const
  friend ostream &operator<<(ostream &o,const F &f)
  {
    o<<f.a<<'/'<<f.b;
    return o;
  }
  //重载类型转换运算符，返回值可以不写(和重载运算符一致)
  operator double(){return 1.0*a/b;}
  operator bool(){return a;}
};
int main()
{
  F f(2,3);
  cout<<++f<<endl;
  cout<<(f++)<<endl;//当是后++时，重载“<<”时第二个参数前必须加const
  cout<<f<<endl;
  cout<<double(f)<<endl;
  cout<<bool(f)<<endl;
  return 0;
}

