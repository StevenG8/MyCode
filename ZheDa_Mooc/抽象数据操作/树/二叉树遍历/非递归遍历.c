//����
void InOrderTraversal(BinTree BT)
{
  BinTree T=BT;
  Stack S=CreateStack(Maxsize);
  while( T || !IsEmpty(S) ){
    while(T){
      Push(S,T);
      T=T->left;
    }
    if(!IsEmpty(S)){
      T=Pop(S);
      printf("%d",T->data);
      T=T->right;
    }
  }
}

//����
void PreOrderTraversal(BinTree BT)
{
  BinTree T=BT;
  Stack S=CreateStack(Maxsize);
  while( T || !IsEmpty(S) ){
    while(T){
      printf("%d",T->data);
      Push(S,T);
      T=T->left;
    }
    if(!IsEmpty(S)){
      T=Pop(S);
      T=T->right;
    }
  }
}

/********************************����**************************************/
//�ǲ�ɨ�����ʽ
void PostOrderTraversal(BinTree BT)
{
  if(BT==NULL){
    printf("��Ϊ��\n");
    return;
  }

  BinTree CurT,PreT;
  CurT=PreT=NULL;
  Stack S=CreateStack(Maxsize);
  Push(S,BT);
  while(!IsEmpty(S)){
    CurT=NULL;
    StackGetPop(S,CurT);//�Ӷ�ջ��ȡ��ջ����������
    if( (cur->left==NULL&&CurT->right==NULL)  ||
        (PreT!=NULL&&(PreT==CurT->left||PreT==CurT->right))
      )//�������������������������ʹ���ô�Ϳ������
    {
        printf("%d",CurT->data);
        PreT=CurT;
        Pop(S,CurT);
    }else{//���ҽ�������û�����ʹ�
      if(CurT->right!=NULL)
        Push(S,CurT->right);
      if(CurT->left!=NULL)
        Push(S,CurT->left);
    }
  }
  free(S);
}
