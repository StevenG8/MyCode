
/*
ָ���Ǵ�ŵ�ַ�ı����������������Լ��ĵ�ַ��
Ҳ����˵��ָ�����渳ֵ����һ����ַA����ָ���Լ������ǵ�ַB
ָ����ָ��ĸ�ֵ��ʵ����ͨ�����ĸ�ֵû�кܴ����������ֻ����ָ��ĸ�ֵ�ǵ�ַ
�κ�һ������ı����ĵ�ַ�������޷�ȥ�ı�ģ�ֻ�ܸı������ַ�ϴ�ŵ�����

free()�ͷŵ���ָ��ָ����ڴ棡ע�⣡�ͷŵ����ڴ棬����ָ�룡
ָ�벢û�б��ͷţ�ָ����Ȼָ��ԭ���Ĵ洢�ռ䡣
ָ����һ��������ֻ�г������ʱ�ű����١�
�ͷ����ڴ�ռ��ԭ��ָ�����ռ��ָ�뻹�Ǵ��ڣ�
ֻ��������ָ��ָ������ݵ���������δ����ģ�����˵��������
��ˣ��ͷ��ڴ���ָ��ָ��NULL����ָֹ���ں��治С���ֱ��������ˡ�
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
	 //����Ѿ����ھͲ�������
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
		if (BST->Left && BST->Right) {//���������
			p = FindMax(BST->Left);
			BST->Data = p->Data;
			BST->Left = Delete(BST->Left, BST->Data);
		}else{//��һ��������Ϊ���ӽ��
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
