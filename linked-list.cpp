/*************************************************************************
	File Name: list.cpp
	Author: lideliang
 ************************************************************************/
//C++链表的相关操作（建立、插入、删除、查找、逆置）
#include<iostream>
using namespace std;
typedef int T;
class List{
    struct Node{
        T data;
        Node *next;
        Node(const T&d):data(d),next(NULL){}
        //Node(){}
    };
    Node *head;
    int len;
public:
    List():len(0),head(NULL){}
     
    void push_front(const T&d)//头插法
    {
        Node *p=new Node(d);
        if(head==NULL) head=p;
        else
        {
            p->next=head;//使p和head指向相同
            head=p;
        }
    }
     
    void push_back(const T&d)//尾插法
    {
        static Node *r;//防止r在出了这个作用域之后就释放
        Node *p=new Node(d);
        if(head==NULL) {head=p;r=p;}
        else
        {
            r->next=p;
            r=p;
            r->next=NULL;
        }
    }
 
    Node *&getptr(int pos)//得到指定链表中的位置
    {
        if(pos<0) pos=0;
        if(pos==0) return head;
        Node *p=head;
        for(int i=0;i<pos-1;i++)
            p=p->next;
        return p->next;
    }
     
    void insert(const T&d,int pos)//在任意位置插入
    {
        Node *&pn=getptr(pos);
        Node *p=new Node(d);
        p->next=pn->next;
        pn->next=p;
    }
     
    int Num()//统计结点个数
    {
        Node *p=head;
        int cnt=0;
        while(p)
        {
            cnt++;
            p=p->next;
        }
        return cnt;
    }
 
    void clear()//清空链表
    {
        while(head)
        {
            Node *p=head->next;
            delete head;
            head=p;
        }
    }
 
    void erase(int pos)//删除指定位置的元素
    {
        if(pos<0) return;
        Node *&p=getptr(pos);//引用保证是原始指针
        Node *pn=p;
        p=p->next;
        delete pn;
    }
     
    void remove(const T&d)//删除指定元素
    {
        int pos=0;
        Node *p=head;
        while(p)
        {
            if(p->data==d)
            {
                erase(pos);
                return;
            }
            p=p->next;
            pos++;
        }
    }
     
    void set(int pos,const T& d)//修改指定位置处的元素
    {
        if(pos<0) return;
        getptr(pos)->data=d;
    }
     
    void revise()//单链表的逆置
    {
        Node  *p,*q;
        p=head->next;
        head->next=NULL;
        while(p!=NULL)
        {
            q=p->next;
            p->next=head;
            head=p;
            p=q;
        }
    }  
 
    void print()//输出
    {
        Node *p=head;
        while(p)
        {
            cout<<p->data<<' ';
            p=p->next;
        }
        cout<<endl;
    }
};
 
int main()
{
    List l;
    /*
    l.push_front(1);
    l.push_front(2);
    l.push_front(3);
    l.push_front(4);
    l.print();
    */
    l.push_back(5);
    l.push_back(6);
    l.push_back(7);
    l.push_back(8);
    l.insert(9,1);
    l.insert(10,2);
    l.print();//5 6 9 10 7 8
    cout<<"Num="<<l.Num()<<endl;
    l.erase(1);
    l.print();//5 9 10 7 8
    l.remove(9);
    l.print();//5 10 7 8
    l.set(1,3);
    l.print();//5 3 7 8
    l.revise();
    l.print();//8 7 3 5
    l.clear();
    cout<<"Num="<<l.Num()<<endl;
    return 0;
}

