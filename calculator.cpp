/*************************************************************************
	File Name: calculator.cpp
	Author: lideliang
	Mail: lideliang@didichuxing.com 
	Created Time: 2017年04月28日 星期五 15时32分58秒
 ************************************************************************/
//description:基于Qt的计算器，能实现基本的加减乘除乘方开放等功能
#include"caldlg.h"
#include<math.h>
 
CALDLG::CALDLG(QWidget *parent)
{
  ui=new Ui_calculate;
  ui->setupUi(this);
  first = 0;
  second = 0;
  result = 0;
  flag1 = 0;
  b=1;
}
CALDLG::~CALDLG()
{
  delete ui;
}
/*-------------------处理数字键-------------------*/
void CALDLG::on_pushButton_1_clicked()
{
  str+=ui->pushButton_1->text();
  //转换为double
  temp=str.toDouble();
  //把和转换为文本显示到标签框
  ui->lineEdit->setText(QString::number(temp));
}
void CALDLG::on_pushButton_2_clicked()
{
  str+=ui->pushButton_2->text();
  temp=str.toDouble();
  ui->lineEdit->setText(QString::number(temp));
}
void CALDLG::on_pushButton_3_clicked()
{
  str+=ui->pushButton_3->text();
  temp=str.toDouble();
  ui->lineEdit->setText(QString::number(temp));
}
void CALDLG::on_pushButton_4_clicked()
{
  str+=ui->pushButton_4->text();
  temp=str.toDouble();
  ui->lineEdit->setText(QString::number(temp));
}
void CALDLG::on_pushButton_5_clicked()
{
  str+=ui->pushButton_5->text();
  temp=str.toDouble();
  ui->lineEdit->setText(QString::number(temp));
}
void CALDLG::on_pushButton_6_clicked()
{
  str+=ui->pushButton_6->text();
  temp=str.toDouble();
  ui->lineEdit->setText(QString::number(temp));
}
void CALDLG::on_pushButton_7_clicked()
{
  str+=ui->pushButton_7->text();
  temp=str.toDouble();
  ui->lineEdit->setText(QString::number(temp));
}
void CALDLG::on_pushButton_8_clicked()
{
  str+=ui->pushButton_8->text();
  temp=str.toDouble();
  ui->lineEdit->setText(QString::number(temp));
}
void CALDLG::on_pushButton_9_clicked()
{
  str+=ui->pushButton_9->text();
  temp=str.toDouble();
  ui->lineEdit->setText(QString::number(temp));
}
void CALDLG::on_pushButton_10_clicked()
{
  str+=ui->pushButton_10->text();
  temp=str.toDouble();
  ui->lineEdit->setText(QString::number(temp));
}
void CALDLG::on_pushButton_20_clicked()
{
  str+=ui->pushButton_20->text();
  temp=str.toDouble();
  ui->lineEdit->setText(QString::number(temp));
}
 
/*------------------处理运算符键--------------------*/
void CALDLG::on_pushButton_11_clicked()
{
  flag = '+';
    if(flag1 == 0)
    {
       first = temp;
       temp = 0;
    }
    str = "";
}
void CALDLG::on_pushButton_12_clicked()
{
    flag = '-';
    if(flag1 == 0)
    {
       first = temp;
       temp = 0;
    }
    str = "";
}
void CALDLG::on_pushButton_13_clicked()
{
    flag = '*';
    if(flag1 == 0)
    {
       first = temp;
       temp = 0;
    }
    str = "";
}
void CALDLG::on_pushButton_14_clicked()
{
    flag = '/';
    if(flag1 == 0)
    {
       first = temp;
       temp = 0;
    }
    str = "";
}
void CALDLG::on_pushButton_15_clicked()
{
    flag = 's';
    if(flag1 == 0)
    {
       first = temp;
       temp = 0;
    }
    str = "";
}
void CALDLG::on_pushButton_16_clicked()
{
    flag = 'c';
    if(flag1 == 0)
    {
       first = temp;
       temp = 0;
    }
    str = "";
}
void CALDLG::on_pushButton_17_clicked()
{
    flag = 't';
    if(flag1 == 0)
    {
       first = temp;
       temp = 0;
    }
    str = "";
}
void CALDLG::on_pushButton_18_clicked()
{
    flag = 'o';
    if(flag1 == 0)
    {
       first = temp;
       temp = 0;
    }
    str = "";
}
 
void CALDLG::on_pushButton_21_clicked()
{
    flag = 'l';
    if(flag1 == 0)
    {
       first = temp;
       temp = 0;
    }
    str = "";
}
void CALDLG::on_pushButton_22_clicked()
{
    flag = '#';
    if(flag1 == 0)
    {
       first = temp;
       temp = 0;
    }
    str = "";
}
void CALDLG::on_pushButton_23_clicked()
{
    flag = '^';
    if(flag1 == 0)
    {
       first = temp;
       temp = 0;
    }
    str = "";
}
 
/*-------------------清零操作--------------------*/
void CALDLG::on_pushButton_24_clicked()
{
    first =0;
    second = 0;
    result = 0;
    temp = 0;
    flag1 = 0;
    str = "";
    ui->lineEdit->setText(QString::number(result));
}
 
/*-------------------绛夊彿鎿嶄綔--------------------*/
void CALDLG::on_pushButton_19_clicked()
{
   second=temp;
   switch(flag)
   {
     case '+':result=first+second;break;
     case '-':result=first-second;break;
     case '*':result=first*second;break;
     case '/':result=first/second;break;
     case '#':result = pow(first,(1.0/second));break;
     case '^':
       for(i=0;i<second;i++)
     b*=first;
       result=b;break;
     case 's':result=sin(first*(Pi/180));break;
     case 'c':result=cos(first*(Pi/180));break;
     case 't':result=tan(first*(Pi/180));break;
     case 'o':result=1/(first*(Pi/180));break;
     case 'l':result=log(first);break;
  }
  ui->lineEdit->setText(QString::number(result));
  first=result;
  flag1=1;
  temp=0;
  b=1;
}

