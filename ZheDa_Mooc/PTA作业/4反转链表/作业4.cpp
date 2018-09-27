#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100000

/*
该题我犯了一个错误，我以为可以用表的链式结构实现
事实上我根本无法指定该元素的地址是多少
网上貌似说开发c语言的人就规定了不允许操作地址
改用表的顺序结构地址就变成了数组下标，解决了！

而后我终于发现用结构体的数组反而更简便


学到的新知识
1.printf("%05d",FirstCell);
  printf("%5d",FirstCell);
  同样是右对齐，一个用0补，一个用空格补
2.结构体中包含数组，不可以用[]申请，而要用指针申请
3.链式结构和顺序结构的不同在于
(1).顺序结构是做一个结构体，结构体中的数组来存储信息
    另设变量来标志结尾的下标
   （更复杂的类型有更多的变量来标志顺序结构的位置信息等)
(2).链式结构是做一个结构体与结构体的指针联系

*/

typedef int ElementType;
typedef struct Node* PtrNode;
struct Node{
	int NextAdr;
	ElementType Digit;
};
struct Node Data[MAXSIZE];

int CreateList(int Size)
{
	ElementType digit;
	int Adr,NextAdr;
	while(Size--){
		scanf("%d %d %d",&Adr,&digit,&NextAdr);
		Data[Adr].Digit=digit;
		Data[Adr].NextAdr=NextAdr;
	}
}

//前提：
//凑得齐size个数才使用该函数，也就是说总共执行次数=总量/分割数
//两个或两个以上的反转才使用该函数，也就是说size>=2
//这个函数是处理单独的这些个size单元的，不是针对整个数据的。
//遇到结束的单元要做特殊的处理，也就说这些单元之间的联系，函数返回值需要注意

int Inverse(int size,int FirstAdr,int* Connect)
{
	int TempAdr1,TempAdr2;
	if(size>2){//分割个数大于两个的情况
		size=size-1;//n个数据只需要处理n-1次
		TempAdr1=Data[FirstAdr].NextAdr;
		TempAdr2=TempAdr1;//为了适应推广统一
		while(size--){
			TempAdr1=TempAdr2;
			TempAdr2=Data[TempAdr1].NextAdr;
			Data[TempAdr1].NextAdr=FirstAdr;
			// printf("Data[%d].NextAdr=%d",TempAdr1,FirstAdr);
			FirstAdr=TempAdr1;
			// printf("TempAdr1=%d,TempAdr2=%d\n",TempAdr1,TempAdr2);
		}
		*Connect=TempAdr2;
		return FirstAdr;//返回反转后的头，为了实现单元之间的连接
	}else{//分割个数为两个的情况
		TempAdr1=FirstAdr;
		TempAdr1=Data[FirstAdr].NextAdr;
		*Connect=Data[TempAdr1].NextAdr;
		Data[TempAdr1].NextAdr=FirstAdr;
		return TempAdr1;//返回反转后的头
	}
}

int main()
{
	int FirstAdr,size,part;
	scanf("%d %d %d",&FirstAdr,&size,&part);
	CreateList(size);

	int times,head,rear;
	int HeadTemp,RearTemp;
	if(part>1){//大于一才需要反转
		int Connect;
		times=size/part;

		//进行头处理，第一次反转单独处理
		//分割单元中，原先的头节点最后会变成反转后的尾节点
		rear=FirstAdr;//得到第一次反转后的尾节点
		head=Inverse(part,FirstAdr,&Connect);//得到第一次反转后的头节点
		//这里的Connect得到分割单元之后的第一个元素地址
		// printf("head=%d,Connect=%d\n",head,Connect);

		if(size%part==0&&times==1){//整个反转，只需一次反转
			Data[rear].NextAdr=-1;
		}else{//至少有一个反转单元但不整个反转
			times--;//减去单独操作的第一次
			while(times--){//有多个反转单元，进行中间推广处理
				RearTemp=Connect;//得到第二个分割单元的尾节点
				HeadTemp=Inverse(part,Connect,&Connect);//得到第二个分割单元的头节点
				Data[rear].NextAdr=HeadTemp;//建立头单元与接下来的单元的连接
				rear=RearTemp;
			}
			//进行尾巴处理，此时要么整分割要么分割后还剩下几个凑不成单元的数据
			if(Connect==-1){//整分割
				Data[rear].NextAdr=-1;
			}else{//分割有余
				Data[rear].NextAdr=Connect;
			}
		}
	}else
		head=FirstAdr;

	while(Data[head].NextAdr!=-1){
		printf("%05d %d %05d\n",head,Data[head].Digit,Data[head].NextAdr);
		head=Data[head].NextAdr;
	}
	printf("%05d %d %d\n",head,Data[head].Digit,-1);

	return 0;
}
