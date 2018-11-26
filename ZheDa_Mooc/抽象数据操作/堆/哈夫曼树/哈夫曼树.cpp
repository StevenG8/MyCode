//哈夫曼树又名最优二叉树,带权路径长度之和最小

typedef struct TreeNode *HuffmanTree;
struct TreeNode{
  int Weight;//权值
  HuffmanTree left,right;
};

HuffmanTree Huffman(Minheap H)//函数参数---按权值排序的最小堆
{
  int i;
  HuffmanTree T;
  for(i=1; i<(H->size) ; i++){//两两合并,n个元素最终执行n-1次,所以这里初始化i=1
    T=malloc(sizeof(struct TreeNode));
    //从最小堆中拿出两个最小权值结点,生成合并成新的权值的树
    T->left=DeleteMin(H);
    T->right=DeleteMin(H);
    T->weight = T->left->weight + T->right->weight;//合并权值

    /*
      打开最小堆的程序代码对比着看!!!!
      原本最小堆是插入数据而不是插入一棵有左右子树的树的,但是在这里插入一棵有左右子树的树不会出现任何问题
------优秀的代码有普适性,就像数学里的自变量x,f(x)==(x=sint)==f(sint),f(x)==x=cosu==f(cosu).------------
      因为在最小堆的插入函数中,不管你插入的是什么,都是插到数组的相应位置
      即把树插到数组对应位置,是链式结构和顺序结构的混用
      他都永远认为是size+1,只多了一个元素.它的终止条件会限制
      在最小堆的排序当中它只会认它的根节点而不会在意它的左右子树,可以认为是这个最小堆的自变量变成了一棵二叉树
      这里只需要把最小堆存放数据的数组的大小重新定义一下即可
    */
    Insert(T,H);//重新放到最小堆里,因为权值相加后仍然可能小于或等于最小堆中的最小权值
  }

  //在这个最小堆中,因为两两合并,最终只会剩一个根节点,而这个根节点里包含了所有的树.
  //这个根节点的子树是按权值排好序的
  T=DeleteMin(H);//从最小堆中取出哈夫曼树的根节点

  return T;
}
