/*************************************************************************
	File Name: binary-tree.cpp
	Author: lideliang
 ************************************************************************/
// description:二叉树的插入、删除、清空，更新等操作
#include<iostream>
#include<iomanip>
using namespace std;
typedef int T;
class bst{
    struct Node{
        T data;
        Node * L;
        Node * R;
        Node(const T&d):data(d),L(),R(){}
        Node(const T&d,Node *l,Node *r):data(d),L(l),R(r){}
    };
    Node *rp;
    int n;
public:
    bst():rp(),n(){}
    void insert(Node* &t,Node *p)//插入节点
    {
        if(t==NULL) t=p;
        else if(p->data<t->data) insert(t->L,p);
        else insert(t->R,p);
    }
    void insert(const T&d){insert(rp,new Node(d));}
 
    Node *&find(Node *&t,const T&d)//查找指定元素
    {
        if(t==NULL) return t;
        else if(d==t->data) return t;
        else if(d<t->data) return find(t->L,d);
        else return find(t->R,d);           
    }
    Node *&find(const T&d){return find(rp,d);}
     
    void remove(const T&d)//删除节点
    {
        Node *&t=find(d);
        if(t==NULL) return;
        Node *p=t;
        if(t->L!=NULL) insert(t->R,t->L);
        t=t->R;
        delete p;
    }
     
    void clear(Node *&t)//清空二叉树
    {
        if(t!=NULL)
        {
            clear(t->L);
            clear(t->R);
            delete t;
            t=NULL;//注意这里t要置空，否则输出时会是随机数
        }
    }
    void clear(){clear(rp);}
     
    int high(Node *t)//求树的高度
    {
        if(t==NULL) return 0;
        int lh=high(t->L);
        int rh=high(t->R);
        return 1+(lh>rh?lh:rh); //每次通过这里不断的累加树的高度
    }  
    int high(){high(rp);}
 
    T &root()//查找根节点
    {
        if(rp==NULL) throw "空";
        return rp->data;
    }  
     
    void update(const T&olddata,const T&newdata)//更新一棵树
    {
        remove(olddata);
        insert(newdata);
    }
 
    void travel(Node *t)//遍历整棵树
    {
        if(t!=NULL)
        {
            travel(t->L);
            cout<<t->data<<' ';
            travel(t->R);
        }
    }
    void travel(){travel(rp);cout<<endl;}
 
    void print(Node *t,int space,char sign)//打印一棵树
    {
        if(t==NULL) return;
        cout<<setw(space+1)<<sign<<t->data<<endl;
        print(t->R,space+2,'\\');
        //cout<<setw(space+1)<<sign<<t->data<<endl;
        print(t->L,space,'/');
        //print(t->R,space+3,'\\');
    }
    void print(){print(rp,6,'*');}
};
int main()
{
    bst b;
    b.insert(5);
    b.insert(3);
    b.insert(9);
    b.insert(4);
    b.insert(1);
    b.travel();
    cout<<"树的高度为:"<<b.high()<<endl;
    cout<<"根节点是:"<<b.root()<<endl;
    b.update(1,8);
    b.travel();
    b.print();
    b.remove(4);
    b.travel();
    b.clear();
    b.travel();
    return 0;
}

