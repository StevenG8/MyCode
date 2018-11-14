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
    //����Ѿ����ھͲ�������
  }
  return BT;
}

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
    if(BT->Left&&BT->Right){//���������
      TmpCell=FindMin(BT->Right);//or FindMax(BT->Left)
      BT->Data=TmpCell->Data;
      BT->Right=Delete(BT->Right,TmpCell->Data);
    }else{//��һ��������Ϊ���ӽ��
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
