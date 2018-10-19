void levelorderTraversal(BinTree BT)
{
  Queue Q;
  BinTree T;
  if (!BT)//¿ÕÊ÷·µ»ØÍË³ö
    return;
  Q=CreatQueue();
  AddQ(Q,BT);
  while(!IsEmpty(Q)){
    T=DeleteQ(Q);
    printf("%d",T->data);
    if(T->left)   AddQ(Q,T->left);
    if(T->right)  AddQ(Q,T->right);
  }
}
