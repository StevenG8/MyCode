#include <stdlib.h>

#define Maxsize 1000
#define MinNum -1
typedef int ElementType;

typedef struct HeapStruct *Heap;
typedef struct HeapStruct *PriorityQueue;
struct HeapStruct{
  ElementType* Data;
  int size;//当前的大小
  int capacity;//最大容量
}

//函数声明
PriorityQueue Initialise(int MaxElements);
void Destory(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void MinInsert(ElementType X,PriorityQueue H);//最小堆的插入
ElementType DeleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
void MaxInsert(ElementType X,PriorityQueue H);
ElementType DeleteMax(PriorityQueue H);
ElementType FindMax(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);

/*
  堆有两个特性：一是完全二叉树，用数组存储。二是子节点大于/小于根节点（左右子树之间没有大小关系）。
  数组的第0个元素是哨兵，不存放数据。从第一个元素开始才存放数据。
  假设该结点的下标为i，那么其左儿子是2i，右儿子是2i+1，父亲是i/2。
*/
PriorityQueue Initialise(int MaxElements)
{
    PriorityQueue H=(PriorityQueue)malloc(sizeof(struct HeapStruct));
    if(H=NULL)
      printf("error,out of space\n");

    //这里“Maxsize+1”是因为数组的第0位是作为哨兵，不作数据存储
    H->Data=(ElementType *)malloc((Maxsize+1)*sizeof(ElementType));
    H->Data[0]=MinNum;
    H->size=0;
    H->capacity=Maxsize;
}

void MinInsert(ElementType X,PriorityQueue H)//最小堆的插入
{
  int position;
  if(IsFull(H)){
    printf("Full\n");
    return;
  }
  //position=++H->size，完全二叉树插入一个结点，首先大小要变化，其次生成一个新的结点的位置是固定的
  //X < H->Data[position/2]，如果要插入的结点A小于该节点B，则结点B要跟它的儿子换一下位置，既下滤
  //position/=2，交换完后基准结点改变
  for(position=++H->size; X < H->Data[position/2] ; position/=2){
      H->Data[position]=H->Data[position/2];
  }
  H->Data[position]=X;//插入导致的顺序错乱已经交换解决，将要插入的位置插到它应有的位置
}

ElementType DeleteMin(PriorityQueue H)
{
  if(IsEmpty(H)){
    printf("Empty\n");
    return H->Data[0];
  }

  ElementType result=H->Data[1];//存放要返回的结果
  ElementType DeleteNode=H->Data[size--];//因为删除了根节点，大小-1。又完全二叉树的形状固定，最底层最右的结点是要被删除的
  int parent;//根节点
  int child;//根节点的左子树

  /*
    从第一个根节点开始，下滤。
    比较根节点的左右子树，找出最小的，再跟被删除的结点作比较，看谁去顶替根节点
    如果是左右子树去顶替根节点，那个去顶替结点则继续重复第二行的动作，直到没有左右子树
    如果是删除的结点去顶替根节点，那么就不用继续执行了

    parent结点不到最后执行完毕永远是空的，等待最小的结点插入
    整个过程就像是把头给拿出来丢掉，把最后一个位置的结点拿出来，然后其他的部分按顺序顶替上去，最后把拿出来的结点再插回去
  */
  for(parent=1 ; parent*2 < H->size ; parent=child){//parent*2 < H->size,一直执行到这颗完全二叉树的最底层

    /*--------------找出根节点中，左右子树哪个最小--------------*/
    //考虑完全二叉树的形状，如果一棵树只有单个结点，那么这单个结点就是最后的结点
    //判断这个结点是否有两个儿子，只需判断这个结点的左子树是不是这个完全二叉树的最后一个结点即可
    child=parent*2;//根节点的左子树
    if( child!=H->size && H->Data[child+1] < H->Data[child] )//如果有两个儿子，且根节点的右子树小于左子树
      child++;//右子树最小

    /*-------------比较这个最小子树跟被删除的最底层最右的结点------*/
    if(DeleteNode < H->Data[child])//如果是最底层最右的结点最小，那么直接将该结点插入即可
      break;//此时的parent结点还没更新所以break跳出来插入是正确的
    else
      H->Data[parent]=H->Data[child];//如果是子树较小，那么最小子树A插入到其父亲上，随后以A为父亲结点继续执行
      //parent结点更新完后执行“parent*2 < H->size”判断，若没有左右子树，则跳出循环，此时parent结点是最底层的结点（空数值）
  }
  H->Data[parent]=DeleteNode;//下滤结束，被删除的结点插入到相应的位置上

  return result;
}


ElementType DeleteMax(PriorityQueue H)
{
  if(IsEmpty(H)){
    printf("Empty\n");
    return H->Data[0];
  }

  ElementType DeleteNum=H->Data[size--];
  ElementType result=H->Data[1];

  int parent;
  int child;
  for(parent=1; 2*parent< H->size ;parent=child){
    child=parent*2;
    if( child!=H->size && H->Data[child+1]>H->Data[child] )
      child++;
    if(DeleteNum>H->Data[child])
      break;
    else
      H->Data[parent]=H->Data[child];
  }
  H->Data[parent]=DeleteNum;

  return result;
}
