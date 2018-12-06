#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MinNum -1

/*
	我们采用的是最小堆的元素装指针指向根节点，传入其根节点的地址
	这里也可以将最小堆的元素换成结构体而不是指针，我们把根节点的全部内容拷贝其实也等于根节点
	在DeleteMin新生成结点复制
	在Insert里copy
*/
typedef struct HuffmanTree *HTree;
struct HuffmanTree{
  HTree left;
  HTree right;
  int weight;
};
typedef struct MinHeap *MinH;
struct MinHeap{
  int size;
  HTree *T;//存放关于哈夫曼树的指针的数组
};
typedef struct BinaryTree *Tree;
struct BinaryTree{
  Tree left,right;
};



MinH CreateMinheap(int num);
void MinHFInsert(MinH H,int X);
void MinHTInsert(MinH H,HTree *T);
HTree DeleteMin(MinH H);
HTree BuildHuffmanTree(MinH H);
Tree EmptyTree();
int BuildTree(char s[],int times,Tree T);
int WPL(HTree T,int depth);


//因为最小堆是完全二叉树,是用数组来存放的
//要用最小堆来存放树,只需要把数组存放的数据类型设置为树
//建堆无需考虑左右子树的问题，只需赋权值即可
//左右子树的构建是在后面的哈夫曼建树完成的
MinH CreateMinheap(int num)
{
  MinH H=(MinH)malloc(sizeof(struct MinHeap));//申请堆
  H->size=0;
  H->T=(HTree *)malloc((num+1)*sizeof(HTree));//指针数组申请
  for(int i=0;i<num+1;i++)
  	H->T[i]=(HTree)malloc(sizeof(struct HuffmanTree));//数组元素申请
  H->T[0]->weight=MinNum;//设置哨兵
  for(int i=0;i<num+1;i++)
  	H->T[i]->left = H->T[i]->right = NULL;//左右子树初始化为空
  return H;
}

//插入元素，这里只是赋值无需交换地址
void MinHFInsert(MinH H,int frenquency)
{
  int pos;
  for(pos = ++H->size ; frenquency < H->T[pos/2]->weight ; pos/=2)
    H->T[pos]->weight = H->T[pos/2]->weight;
  H->T[pos]->weight = frenquency;
}



void MinHTInsert(MinH H,HTree *T)
{
  int pos;
  for(pos = ++H->size ; (*T)->weight < H->T[pos/2]->weight ; pos/=2)
    H->T[pos]= H->T[pos/2]; //交换所指向的地址，也就是交换所存放的哈夫曼树。
  H->T[pos] = *T;//使用了指针的指针，目的是为了将根节点的地址写入
  //（插入一个有左右子树的树应该插入的是根节点的地址，否则左右子树将会丢失）
}

HTree DeleteMin(MinH H)
{
  if(H->size==0){
    printf("堆空\n");
    return H->T[0];//返回哨兵
  }

  int child,parent;
  HTree result=H->T[1];//返回堆中权值最小的根节点树

  //这里其实就是头拿出来，其他位置移动，最后再把头插回去
  HTree DeleteNode=H->T[H->size--];
  for(parent=1;parent*2 <= H->size;parent=child){//这里是小于或等于，否则就会出错
	child=parent*2;
    if(child!=H->size && H->T[child+1]->weight < H->T[child]->weight )
      child++;
    if(DeleteNode->weight < H->T[child]->weight)
	    break;
    else
      H->T[parent] = H->T[child];//要让地址交换而不是权值交换
	  //如果是权值交换会导致每次返回的都是H->T[1]元素所指向的地址，也就是老是同一棵树，这样再建立哈夫曼树就乱套了
  }
  H->T[parent]=DeleteNode;

  return result;
}


HTree BuildHuffmanTree(MinH H)
{
  HTree T;
  int times=H->size;//最小堆元素总数

  //这里要用times而不直接用H->size的原因是，H->size会在DeleteMin函数中减小，导致循环的步长变化
  for(int i=1;i<times;i++){//两两拿出建树再插回去，N个元素就要执行N-1次
    T=(HTree)malloc(sizeof(struct HuffmanTree));//malloc应该循环里面,如果在循环外面会把前面写的数据重写
	T->left=DeleteMin(H);
    T->right=DeleteMin(H);
    T->weight = (T->left->weight) + (T->right->weight);
    MinHTInsert(H,&T);//传入根节点的地址就等于传入了整棵树
  }
  T=DeleteMin(H);
  return T;
}

int WPL(HTree T,int depth)
{
  if(T->left==NULL&&T->right==NULL){//如果左右子树都不存在那么即为叶节点，返回其带权路径值
  	return (T->weight)*depth;
  }
  else{  //因为哈夫曼树只有度为0或2的结点，因此要么左右子树都为空，要么左右子树都存在
	return ( WPL(T->left,depth+1) + WPL(T->right,depth+1) );
	//计算出左子树和右子树的带权路径值相加
  }
}



Tree EmptyTree()
{
  Tree T=(Tree)malloc(sizeof(struct BinaryTree));
  T->left=T->right=NULL;
  return T;
}

//哈夫曼树的编码方式可以多样化,但只要满足这两点就可以说是哈夫曼树
//1.带权路径长度之和最小
//2.数据仅存在叶节点上
//如果这颗哈夫曼树有度为1的结点，那么其路径长度就不会是最小
//因为如果是有度为1的结点，为什么不把中间多余的路径砍掉？
int BuildTree(char s[],int times,Tree T)
{
  for(int i=0;i<times;i++){
    if(s[i]=='0'){
      if(T->left==NULL)
        T->left=EmptyTree();
      T=T->left;
    }
    else{
      if(T->right==NULL)
        T->right=EmptyTree();
      T=T->right;
    }
  }
  if(T->right||T->left)//这个结点落在路径上而不是叶子节点
    return 1;

  return 0;
}


int main()
{
  int num,i,j;

  scanf("%d",&num);
  getchar();
  MinH H=CreateMinheap(num);//确定最小堆的大小

  char alphabet;
  int frequency[num];//记录权值
  for(i=0;i<num;i++){
    scanf("%c %d",&alphabet,&frequency[i]);
    getchar();
    MinHFInsert(H,frequency[i]);//生成最小堆
  }

  HTree HuffmanT=BuildHuffmanTree(H);//生成哈夫曼树
  int Value=WPL(HuffmanT,0);

  int checknum,flag;
  scanf("%d",&checknum);
  int length,power=0;
  char s[num][64];
  Tree T;

  for(i=0;i<checknum;i++){
    flag=1;
    power=0;
    T=EmptyTree();
    for(j=0;j<num;j++){
      getchar();
      scanf("%c",&alphabet);
      scanf("%s",s[j]);
      length=strlen(s[j]);//算出路径长
      power=length*frequency[j]+power;//权值累加
      if( flag && BuildTree(s[j],length,T) )
		flag=0;//如果建树过程中出错，标志置0
    }

    if(flag){//建树对应没问题
      if(power==Value)//校验权值是否相同
      	printf("Yes\n");
	  else
	  	printf("No\n");
	}
    else
      printf("No\n");
  }
  return 0;
}
