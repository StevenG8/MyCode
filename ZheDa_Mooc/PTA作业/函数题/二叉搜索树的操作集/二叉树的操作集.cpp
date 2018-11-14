Position FindMin(BinTree BT)
{
  if(!BT) return NULL;
  while(BT->Left){
    BT=BT->Left;
  }
  return BT;
}

Position FindMax(BinTree BT)
{
  if(!BT) return NULL;
  while(BT->Right){
    BT=BT->Right;
  }
  return BT;
}

Position Find(BinTree BST, ElementType X) {

	if (!BST)

		return NULL;

	if (X < BST->Data) {

		return Find(BST->Left, X);

	}

	else if (X > BST->Data) {

		return Find(BST->Right, X);

	}

	else

		return BST;

}

BinTree Insert(BinTree BT,ElementType X)
{
  if(!BT){
    BT=(BinTree)malloc(sizeof(struct TNode));
    BT->Data=X;
    BT->Left=NULL;
    BT->Right=NULL;
  }else{
    if(X>BT->Data)       BT->Right=Insert(BT->Right,X);
    else if(X<BT->Data)  BT->Left=Insert(BT->Left,X);
    //如果已经存在就不做插入
  }
  return BT;
}

/*
指针是存放地址的变量，而且它是有自己的地址的
也就是说，指针里面赋值的是一个地址A，而指针自己本身是地址B
指针与指针的赋值其实跟普通变量的赋值没有很大的区别，区别只在于指针的赋值是地址
任何一个申请的变量的地址我们是无法去改变的，只能改变这个地址上存放的数据

free()释放的是指针指向的内存！注意！释放的是内存，不是指针！
指针并没有被释放，指针仍然指向原来的存储空间。
指针是一个变量，只有程序结束时才被销毁。
释放了内存空间后，原来指向这块空间的指针还是存在！
只不过现在指针指向的内容的垃圾，是未定义的，所以说是垃圾。
因此，释放内存后把指针指向NULL，防止指针在后面不小心又被解引用了。
*/

BinTree Delete(BinTree BT,ElementType X)
{
  Position TmpCell;
  if(BT==NULL){
    printf("Not Found\n");
    return NULL;
  }
  else if(X>BT->Data)
    BT->Right=Delete(BT->Right,X);
  else if(X<BT->Data)
    BT->Left=Delete(BT->Left,X);
  else{
    if(BT->Left&&BT->Right){//有两个结点
      TmpCell=FindMin(BT->Right);//or FindMax(BT->Left)
      BT->Data=TmpCell->Data;
      BT->Right=Delete(BT->Right,TmpCell->Data);
    }else{//有一个结点或者为无子结点
      TmpCell=BT;
      if(BT->Left!=NULL)
        BT=BT->Left;
      else if(BT->Right!=NULL)
        BT=BT->Right;
      free(TmpCell);
    }
  }
  return BT;
}
