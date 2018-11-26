
#define Maxsize 1000
#define Error -1

typedef int ElementType;
typedef struct{
  ElementType Data;
  int parent;//其集合所属
}SetType;//这里既完成了宏的定义,也完成了结构体的声明.
//申请声明结构体不需要写struct SetType X,直接写SetType X即可

//集合的树采用的是双亲表示法,平时的树的根节点指向它的子树,但这里是子树指向根节点.
//多个子树指向同一个根节点,这个根节点就作为这个集合的标志
//集合的头的parent的值是负数,绝对值大小就是其集合大小


void CombineRoots(SetType A[],ElementType a,ElementType b);
int Find(SetType A[],ElementType X);

int Find(SetType A[],ElementType X)
{
  //这样的写法更加简洁,在一个有限次数的循环当中找一个元素
  for(int i=0 ; i<Maxsize&&A[i].Data!=X ; i++);//找出元素在数组的下标

  if(i>=Maxsize){
    printf("找不到\n");
    return Error;
  }

  //寻集合的头
  int head=A[i].parent;
  while(A[head].parent>=0){//跳过中间的小集合
    head=A[head].parent;
  }
  return A[parent].parent;
}

//这个函数是找出两个元素分别属于在哪个集合,如果集合不同,则将其二者的头集合合并
//-------------这个合并跟传统意义上的两个元素合并为一个集合不一样-------------
void CombineRoots(SetType A[],ElementType a,ElementType b)
{
  int root1,root2;
  //找到这两个元素的集合头
  root1=Find(A,a);
  root2=Find(A,b);

  if(root!=root2){//两个集合不同
    if( (A[root1].parent)< (A[root2].parent))//若集合root2的大小是小于集合root1
      A[root2].parent=root1;//将集合root2挂到集合root1上
    else
      A[root1].parent=root2;
  }
}
