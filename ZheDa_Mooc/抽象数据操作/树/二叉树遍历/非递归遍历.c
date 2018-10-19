//中序
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

//先序
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

/********************************后序**************************************/
//是层扫描的形式
void PostOrderTraversal(BinTree BT)
{
  if(BT==NULL){
    printf("树为空\n");
    return;
  }

  BinTree CurT,PreT;
  CurT=PreT=NULL;
  Stack S=CreateStack(Maxsize);
  Push(S,BT);
  while(!IsEmpty(S)){
    CurT=NULL;
    StackGetPop(S,CurT);//从堆栈中取出栈顶但不弹出
    if( (cur->left==NULL&&CurT->right==NULL)  ||
        (PreT!=NULL&&(PreT==CurT->left||PreT==CurT->right))
      )//如果这个结点的左右子树都被访问过那么就可以输出
    {
        printf("%d",CurT->data);
        PreT=CurT;
        Pop(S,CurT);
    }else{//左右结点存在且没被访问过
      if(CurT->right!=NULL)
        Push(S,CurT->right);
      if(CurT->left!=NULL)
        Push(S,CurT->left);
    }
  }
  free(S);
}
