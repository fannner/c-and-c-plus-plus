/*************************************************************************
	File Name: sort.cpp
	Author: lideliang
 ************************************************************************/

/*
1、直接插入排序：
介绍：每次排序都是向前面已经排好序的序列中插入关键字。完整的排序，是从第二个关键字开始。
优缺点：直接插入排序是稳定的排序方法，因为在直接插入排序中，由于待插入元素的比较是从后往前进行的，循环for(j=i;j>0&&t<a[j-1];j--)保证了后面出现的关键字不可能插入到前面相同关键字之前。适合待排序记录数目较少且基本有序，时间复杂度O（），空间复杂度O（1）。
*/
void sort(int* a,int n)
{
  for(int i=1;i<n;i++){
    int t=a[i],j;
    for(j=i;j>0&&t<a[j-1];j--){
    a[j]=a[j-1];
    }
    a[j]=t;//这里必须使用a[j]，而非a[j-1]，因为循环回去已经j--，判断不符合条件才执行此处的
}
/*
2、希尔(Shell)排序：
介绍：希尔排序又称为缩小增量排序法，是一种基于插入思想的排序算法，它利用了直接插入排序的最佳性质，首先将待排序的关键字序列分成若干个较小的子序列，对子序列进行直接插入排序，是整个待排序序列排好序。
优缺点：当delta=1时，就是一趟直接插入排序法，但此时序列的逆转数很小，所以移动的次数相对于简单的直接插入排序而言也会减少。故，希尔排序是一个较好的插入排序方法，时间复杂度O（），空间复杂度O（1），比直接插入要好。适合中等规模(n<=1000)排序，但不稳定。
*/
void shell(int a[],int n)
{
  int delta,i,j,temp;
  for(delta=n/2;delta>=1;delta/=2)//delta代表每次的增量
  {
    for(i=delta;i<n;i++)
    {
      temp=a[i];
      //当delta=1的时候，就是直接插入排序法
      for(j=i-delta;j>=0&&a[j]>temp;j=j-delta)
      {
    a[j+delta]=a[j];
      }
      //注意这里一定是a[j+delta],因为在for循环中j=j-delta,不满足
      //条件才退出，所以线面必须要是j+delta才对
      a[j+delta]=temp;
    }
  }
}
/*
3、冒泡排序：
介绍：每一趟排序都会让最大的数上升到最顶端（移到最后），从而第n次排序时，每趟排序需要进行n-i次，从前往后比较的次数都会减少个元素i；
优缺点：是一种稳定的排序方法，时间复杂度O（），空间复杂度O（1）.
*/
void bubble(int a[],int n)
{
    int temp;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i;j++)
        {
            if(a[j]<a[j-1])
            {
                temp=a[j];
                a[j]=a[j-1];
                a[j-1]=temp;
            }
        }
    }
}
/*
4、快速排序：
介绍：从待排序的序列中选择一个记录（开始可选择首元素）K为中枢，将比它小的元素移到它的左边，比它大的移到它的右边，结果是以此K为界，左边的都不大于它，右边的都不小于它；然后递归再对左右分别进行以上操作。
优缺点：快速排序递归算法的执行过程对应一颗二叉树，理想情况下是一颗完全二叉树，递归工作站的大小与上述递归调用二叉树的深度对应，时间复杂度为O（），平均情况下辅助空间复杂度为O（）。
*/
void sort(int* a,int n)//递归实现
{
  if(n<1) return;
  int l=0;
  int r=n-1;
  int mid=a[l];//此时a[l],为空
  while(l<r){
    while(l<r&&mid<=a[r]) r--;
    a[l]=a[r];
    while(l<r&&a[l]<=mid) l++;
    a[r]=a[l];
  }
  a[l]=mid;
  sort(a,l);
  sort(a+l+1,n-l-1);
}
/*
5、选择排序：
介绍：选择排序的基本思想是，一趟排序中选择关键字最小的下表，然后作为关键字与开始记录交换。
优缺点：不稳定排序。时间复杂度O()，空间复杂度O（1）。
*/
void sort(int* a,int n)
{
  for(int i=0;i<n-1;i++){
    int min=i;
    for(int j=i+1;j<n;j++){
      if(a[j]<a[min]) min=j;
    }
    int t;
    t=a[i];
    a[i]=a[min];
    a[min]=t;
  }
}
/*
介绍：
什么是堆：n个关键字序列K1，K2，…，Kn称为（Heap），当且仅当该序列满足如下性质（简称为堆性质）：ki<=k(2i）且ki<=k(2i+1)(1≤i≤ n），当然，这是小根堆，大根堆则换成>=号。//k(i）相当于二叉树的非叶结点，K(2i）则是左孩子，k(2i+1）是右孩子。即从根节点开始，每个根节点都大于（小于）它的左右子节点，称为大根堆（小根堆）。优缺点：时间复杂度O（），空间复杂度是O（1）
*/
//筛选元素调整堆：
void sift(int d[], int low, int len)
{
    //置i为要筛选的节点
    int i = low;
    //j中保存i节点的左孩子
    int j = i * 2 + 1; //+1的目的就是为了解决节点从0开始二它的左孩子一直为0的情况，                因为数组下标从0开始
    while(j < len)//未筛选到叶子节点
    {
        //如果要筛选的节点既有左孩子又有右孩子并且左孩子的值小于右孩子，从二者中           选出较大的记录
        if(j + 1 < len && d[j] < d[j + 1])
            j++;
        //如果要筛选的节点中的值大于左右孩子的较大者则退出
        if(d[i] > d[j]) break;
        else
        {
            //交换，将a[j]调整到双亲节点上
            int t = d[j];
            d[j] = d[i];
            d[i] = t;
            //重置要筛选的节点和要筛选的左孩子
            i = j;//修改i和j的位置，以便向下筛选
            j = 2 * i + 1;
        }
    }
    return;
}
void heap_sort(int d[], int n)
{
    /* 
        初始化建堆，i从最后一个非叶节点开始
        因为是数组，下表从0开始
        而树从1开始计数，所以要减1，比如第5个元素，下标是4
    */
    for(int i = n/2-1; i >= 0; i--)
        sift(d, i, n);
    for(int j = 0; j < n; j++)
    {
        //交换
        int t = d[0];
        d[0] = d[n - j - 1];
        d[n - j - 1] = t;
        //筛选编号为0
        sift(d, 0, n - j - 1);
    }
}
/*
7、归并排序：
介绍：归并排序 (merge sort) 是一类与插入排序、交换排序、选择排序不同的另一种排序方法。归并的含义是将两个或两个以上的有序表合并成一个新的有序表。
时间复杂度：；
空间复杂度：；
是一种稳定的排序。
*/
#include<iostream>
using namespace std;
//将有二个有序数列a[first...mid]和a[mid...last]合并。 
void mergearray(int a[], int first, int mid, int last, int temp[]) 
{ 
    int i = first, j = mid + 1; 
    int m = mid,   n = last; 
    int k = 0; 
       
    while (i <= m && j <= n) 
    { 
        if (a[i] <= a[j]) 
            temp[k++] = a[i++]; 
        else 
            temp[k++] = a[j++]; 
    } 
       
    while (i <= m) 
        temp[k++] = a[i++]; 
       
    while (j <= n) 
        temp[k++] = a[j++]; 
      /*
        a[first...mid]和a[mid...last]合并到临时数组后，所以下面a[first + i] = temp[i]，            从临时数组拷贝回来要从first开始
     */
    for (i = 0; i < k; i++) 
        a[first + i] = temp[i];
} 
//递归将n个元素的数组不断分成左右“两个”子序列，最后在2路归并排序
void mergesort(int a[], int first, int last, int temp[]) 
{ 
    if (first < last) 
    { 
        int mid = (first + last) / 2; 
        mergesort(a, first, mid, temp);    //左边有序 
        mergesort(a, mid + 1, last, temp); //右边有序 
        mergearray(a, first, mid, last, temp); //再将二个有序数列合并 
    } 
} 
   
bool MergeSort(int a[], int n) 
{ 
    int *p = new int[n]; 
    if (p == NULL) 
        return false; 
    mergesort(a, 0, n - 1, p); 
    delete[] p; 
    return true; 
}

