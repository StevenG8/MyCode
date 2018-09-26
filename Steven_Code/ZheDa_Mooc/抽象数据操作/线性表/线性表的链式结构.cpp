#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct LNode* List;
struct LNode{
	ElementType Data;
	List Next;
};

int length(List PtrL)
{
	int j=0;
	while(PtrL){//图像法其实就是数链表中的箭头数 
		j++;
		PtrL=PtrL->Next;
	}
	return j;
}

List FindKth(int position,List PtrL)//找到该序号的元素其指针 
{
	int j=1;//这里应该是从1开头 
	while(PtrL&&j<position){
		PtrL=PtrL->Next;
		j++;
	} 
	if(j==position)
		return PtrL;
	else//列表并没有那么多的元素，查找不到 
		return NULL;
} 

List Find(ElementType X,List PtrL)//找到该值的元素其指针 
{
	while(PtrL){
		if(PtrL->Data==X)
		{
			return PtrL;
			break;
		}
		PtrL=PtrL->Next;
	}	
	return NULL;
}

List Insert(ElementType X,int position,List PtrL)//可以插入任意合法位置 
{
	List S;
	if(position==1){//在表头插入头指针改变 
		S=(List)malloc(sizeof(struct LNode));
		S->Next=PtrL;
		S->Data=X;
		return S;
	}
	List p;
	p=FindKth(position-1,PtrL);
	if(p==NULL){
		printf("位置不合法");
		return NULL;
	}
	else{
		S=(List)malloc(sizeof(struct LNode));
		S->Data=X;
		S->Next=p->Next;
		p->Next=S;
		return PtrL;
	}
}

List Delete(int position,List PtrL)//可以删除任意合法位置
{
	List p,s;
	if(position==1){
		s=PtrL;
		if(PtrL!=NULL)
			PtrL=PtrL->Next;
		else 
			return NULL;
		free(s);
		return PtrL;
	}
	p=FindKth(position-1,PtrL);
	if(p==NULL||p->Next==NULL){//要删除的是position,若前面的元素不存在也无法删除 
		printf("位置不合法");
		return NULL;
	}
	else{
		s=p->Next;
		p->Next=s->Next;
		free(s);
		return PtrL;
	}
}	


int main()
{
	//建立表 
	struct LNode L;
	List PtrL,s,p;
	PtrL=s=&L;//保存头节点，不要改动PtrL的位置！另作一个变量去运作！ 
	
	//赋值表 
	s->Data=3;//初始表头赋值 
	int i; 
	for(i=4;i<=8;i++){
		p=(List)malloc(sizeof(struct LNode)); //申请表空间 
		p->Next=NULL;
		s->Next=p;
		s=s->Next;
		s->Data=i;
	} 
	 
	//表长 
	printf("当前表长%d\n",length(PtrL));

	//输出每一个元素
	p=PtrL;//不要改动头结点PtrL的位置！另作一个变量去运作！
	while(p){
		printf("%d ",p->Data);
		p=p->Next;
	} 
	
	//插入数据 
	PtrL=Insert(1,1,PtrL);	
	PtrL=Insert(2,2,PtrL);
	PtrL=Insert(9,9,PtrL);
	PtrL=Insert(10,10,PtrL);
	
	//新表长 
	printf("\n插入后的当前表长%d\n",length(PtrL));
	
	//输出每一个元素
	p=PtrL; 
	while(p){
		printf("%d ",p->Data);
		p=p->Next;
	} 
	
	//寻找元素返回指针 
	printf("\n当前的链表元素地址：\n");
	p=PtrL;
	while(p){
		printf("%d\n",p->Data); 
		printf("%p\n",p);
		p=p->Next;
	}
	printf("FindKth(3,PtrL)=%p\n",FindKth(3,PtrL));
	printf("Find(2,PtrL)=%p\n",Find(2,PtrL));
	
	//删除指定位置的数据
	printf("\n删除指定位置之后\n");
	PtrL=Delete(10,PtrL);
	PtrL=Delete(8,PtrL);
	
	p=PtrL;
	while(p){
		printf("%p\n",p);
		printf("%d\n",p->Data); 
		p=p->Next;
	}
	return 0; 
}

