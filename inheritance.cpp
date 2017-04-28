/*************************************************************************
	File Name: inheritance.cpp
	Author: lideliang
 ************************************************************************/
//C++继承和虚函数
//C++继承和虚函数
 
 
//-----------继承--inheritance：------------
//程序1：
#include<iostream>
using namespace std;
class Person{
protected:
  string name;//由于是protected类型，故在子类里面可以访问
private:
  bool gender;
public:
  Person(const char *a,bool g=true):name(a),gender(g){}
  void show()
  {
    cout<<"大家好，我是"<<(gender?"帅哥":"美女")<<name<<endl;
    cout<<",很高兴认识大家!"<<endl;
  }
  void eat(const char *food)
  {
    cout<<"我喜欢吃"<<food<<"."<<endl;
  }
};
 
class Student:public Person{
  int gread;
  string major;
public:
  //公有继承父类的，可以访问它里面的公有成员以及受保护的成员
  //如果在子类构造函数里面要初始化父类里面的成员，就把相应的参数传给
//父类的构造函数
  Student(const char *a,bool g,int G,const char *m)
  :gread(G),major(m),Person(a,g){}//注意这里对父类成员的初始化
  void show()//改写来自父类成员，隐藏父类的同名成员
  {
    cout<<"大家好，我是"<<name<<endl;
    cout<<",很高兴认识大家!"<<endl;
  }
  void details()
  {
    cout<<"我现在是大学"<<gread<<"年级学生,"<<name<<"我的专业是"<<major;
    cout<<",希望一起交流!"<<endl;
  }
};
int main()
{
  Person a("铁蛋",true);
  a.show();
  a.eat("火腿肠");
  Student b("胖妞",false,3,"信息");
  b.show();
  b.eat("火腿");
  b.details();
}
 
 
//----------多重继承、虚继承:------------
 
   
//虚继承：
//1.来自虚基类的成员合并，只保留一份到最下层子类里面
//2.虚基类构造函数的参数，由底层子类直接传递
//3.虚继承，保证虚基类的成员到最底层子类里面只保留一份
#include<iostream>
using namespace std;
class Goods{
  double price;
public:
  Goods(double p=100):price(p){cout<<"Goods()"<<endl;}
  ~Goods(){cout<<"~Goods()"<<endl;}
  //double Price()
  void Price()
  {
    //return price;
    cout<<price<<endl;
  }
};
class Camera:virtual public Goods{
public:
  Camera(double p):Goods(p){cout<<"Camera()"<<endl;}
  ~Camera(){cout<<"~Camera()"<<endl;}
  void take(const char* obj)
  {
    cout<<"给"<<obj<<"照相."<<endl;
  }
};
class MP3:virtual public Goods{
public:
  MP3(double p):Goods(p){cout<<"MP3()"<<endl;}
  ~MP3(){cout<<"~MP3()"<<endl;}
  void play(const char *song)
  {
    cout<<"播放歌曲<<"<<song<<">>"<<endl;
  }
};
class Phone:virtual public Goods{
public:
  Phone(double p):Goods(p){cout<<"Phone()"<<endl;}
  ~Phone(){cout<<"~Phone()"<<endl;}
  void dial(const char *no)
  {
    cout<<"给"<<no<<"拨打电话!"<<endl;
  }
};
//多重继承,构造函数执行的顺序是按照子类继承父类的顺序执行
//同时，子类的构造函数是最后执行(即一个类总是先调用父类的构造函数)
class ModernPhone:public Phone,public Camera,public MP3
{
  string factory;
public:
  ModernPhone(const char *f,double p):factory(f),Phone(p),Camera(p),MP3(p),Goods(p)
  {
    cout<<"ModernPhone()"<<endl;
    cout<<"手机厂商"<<factory<<endl;
  }
  ~ModernPhone(){cout<<"~ModernPhone"<<endl;}
  void visitnet(const char *url)
  {
    cout<<"访问网址"<<url<<endl;
  }
};
int main()
{
  ModernPhone mp("Apple",300);
  mp.dial("18710831610");
  mp.play("最炫民族风");
  mp.Price();
  return 0;
}
 
//--------虚函数、多态---(polymorphism[pɒlɪ'mɔːfɪz(ə)m])：------------
//程序1：
//通过指针调用虚函数的时候才会实现多态
#include<iostream>
using namespace std;
class Person{
protected:
  string name;
private:
  bool gender;
public:
  Person(const char *a,bool g=true):name(a),gender(g){}
  virtual void show()//虚函数
  {
    cout<<"大家好，我是"<<(gender?"帅哥":"美女")<<name<<endl;
    cout<<",很高兴认识大家!"<<endl;
  }
  void eat(const char *food)
  {
    cout<<"我喜欢吃"<<food<<"."<<endl;
  }
};
 
class Student:public Person{
  int gread;
  string major;
public:
  Student(const char *a,bool g,int G,const char *m)
  :gread(G),major(m),Person(a,g){}
  void show()
  {
    cout<<"大家好，我是"<<name<<endl;
    cout<<",很高兴认识大家!"<<endl;
  }
  void details()
  {
    cout<<"我现在是大学"<<gread<<"年级学生,"<<name<<"我的专业是"<<major;
    cout<<",希望一起交流!"<<endl;
  }
};
int main()
{
  Person a("铁蛋",true);
  Student b("胖妞",false,3,"信息");
  Person *p,*q;   //注意这里，p,q两个指针都是Person类型
  p=&a;
  q=&b;
  //会根据对象的类型来决定调用那个对象里面的成员函数
  a.show();
  b.show();
}
 
//程序2：
//构造函数、析构函数中没有多态
#include<iostream>
using namespace std;
class USB{
public:
  virtual void recognise()
  {
    cout<<"正在识别USB..."<<endl;
  }
  virtual void know()
  {
    cout<<"USB已经接入!"<<endl;
  }
  virtual void display()
  {
    cout<<"USB开始工作."<<endl;
  }
};
//后面的子类里面的成员函数可以不写virtual，默认加virtual
class USBCamera:public USB{
  void recognise()
  {
    cout<<"正在识别相机..."<<endl;
  }
  void know()
  {
    cout<<"相机已经接入!"<<endl;
  }
  void display()
  {
    cout<<"相机开始工作."<<endl;
  }
};
class USBMP3:public USB{
  void recognise()
  {
    cout<<"正在识别MP3..."<<endl;
  }
  void know()
  {
    cout<<"MP3已经接入!"<<endl;
  }
  void display()
  {
    cout<<"MP3开始工作."<<endl;
  }
};
class Computer{
public:
  void use(USB *p)//相当于，用父类申明一个指针,然后用改指针指向相应的成员函数
  {
    p->recognise();
    p->know();
    p->display();
  }
};
int main()
{
//由于父类的成员函数已经申明为虚函数(virtual)，所以在调用函数时，会根据相应的子类对象而调用子类里面的成员函数
  USBCamera ca;
  USBMP3 m;
  Computer c;
  c.use(&ca);
  c.use(&m);
  return 0;
}
 
 
//--------------纯虚函数：-------------
//程序1：
//只有用new创建对象，用delete释放对象，虚析构才起作用
//构造、析构函数没有纯虚函数
//子类一定是父类,所以可以将一个子类赋给父类，但父类不一定能够赋给子类
#include<iostream>
using namespace std;
class Animal{
public:
  Animal(){}
  virtual ~Animal(){}//虚析构
  //~Animal(){shout();}
  void play()
  {
    eat();
    shout();
    sleep();
  }
  //纯虚函数:提供一个接口，子类覆盖它，自己实现函数的不同功能
  //有纯虚函数的类，称为抽象类abstract class
  //补允许创建抽象类的对象
  virtual void eat()=0;
  virtual void shout()=0;
  virtual void sleep()=0;
};
class Horse:public Animal{
public:
  Horse(){cout<<"马"<<endl;}
  ~Horse(){cout<<"死马"<<endl;}
  virtual void eat(){cout<<"马吃草"<<endl;}
  virtual void shout(){cout<<"马叫"<<endl;}
  virtual void sleep(){cout<<"马睡觉"<<endl;}
};
class Tiger:public Animal{
public:
  Tiger(){cout<<"老虎"<<endl;}
  ~Tiger(){cout<<"死老虎"<<endl;}
  virtual void eat(){cout<<"老虎吃肉"<<endl;}
  virtual void shout(){cout<<"老虎叫"<<endl;}
  virtual void sleep(){cout<<"老虎睡觉"<<endl;}
};
int main()
{
  char c;
  Animal *p=NULL;
  cout<<"选择h代表马，t代表老虎:";
  cin>>c;
  if(c=='h')
    p=new Horse;
  else
    p=new Tiger;
  p->play();
  delete p;
  //Animal a;这里编译出现错误，补允许创建抽象类的对象
  return 0;
}
 
 
//程序2：
//虚函数表里存有这个类里面所有虚函数的地址
//每个类只有一个虚函数表，每个对象有一个指针指向这个虚函数表
#include<iostream>
using namespace std;
class A{
  double a;
};
class B{
  double b;
  void fun(){}
};
class C{
  double c;
  virtual void fun(){}
};
class D{
  double d;
  virtual void fun1(){}
  virtual void fun2(){}
  virtual void fun3(){}
};
int main()
{
  cout<<sizeof(A)<<endl;//8
  cout<<sizeof(B)<<endl;
  //sizeof(B)=8,函数在代码区，b在数据区，所以sizeof(b)=8
  cout<<sizeof(C)<<endl;
  //sizeof(C)=12,有虚函数的类，每个对象有一个虚指针，
  //指向一个存有所有虚函数的数组，只占4个字节，与虚函数的个数无关
  cout<<sizeof(D)<<endl;//sizeof(D)=12
  return 0;
}

