
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

BinTree Insert(BinTree BST, ElementType X)
{
	 if(!BST) {
		 BST = (BinTree)malloc(sizeof(struct TNode));
		 BST->Left = NULL;
		 BST->Right = NULL;
		 BST->Data = X;
	 }
	 else if (X < BST->Data)
		 BST->Left = Insert(BST->Left, X);
	 else if(X > BST->Data)
		 BST->Right = Insert(BST->Right, X);
	 //如果已经存在就不做插入
	 return BST;
}

Position FindMin(BinTree BST)
{
	if (BST) {
		while (BST->Left != NULL)
			BST = BST->Left;
	}
	return BST;
}

Position FindMax(BinTree BST)
{
	if (BST) {
		while (BST->Right != NULL)
			BST = BST->Right;
	}
	return BST;
}

Position Find(BinTree BST, ElementType X)
{
	if (!BST)
		return NULL;
	if (X < BST->Data)
		return Find(BST->Left, X);
	else if (X > BST->Data)
		return Find(BST->Right, X);
	else
		return BST;
}


BinTree Delete(BinTree BST, ElementType X)
{
	BinTree p;
	if (!BST) {
		printf("Not Found\n");
		return BST;
	}
	if (X < BST->Data)
		BST->Left = Delete(BST->Left, X);
	else if (X > BST->Data)
		BST->Right = Delete(BST->Right, X);
	else {
		if (BST->Left && BST->Right) {//有两个结点
			p = FindMax(BST->Left);
			BST->Data = p->Data;
			BST->Left = Delete(BST->Left, BST->Data);
		}else{//有一个结点或者为无子结点
			p = BST;
			if (!BST->Left)
				BST = BST->Right;
			else if (!BST->Right)
				BST = BST->Left;
			free(p);
		}
	}
	return BST;
}
