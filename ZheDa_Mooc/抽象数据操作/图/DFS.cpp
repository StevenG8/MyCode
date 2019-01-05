//深度搜索---邻接表
//这里的Visited数组是全局变量

void Visit(Vertex V)
{
  printf("正在访问顶点%d\n",V);
}


//因为设置了Visited数组，导致了不可回访，也就是说
//1->2->3的路径，如果从1出发，在2可以出去，1->2->出口就是一条方案
//但是1->2->3 -/> 2，从1出发，到2再到3，就不可以再回到2
//如此一来，DFS只能适用于某个单点的路径搜索。不可以求出整张图中的所有出口路线
//注意并不是最短路径，比如1-2->3->出口，1->3->出口。如果先2再3找到出口，就不会找到1->3->出口
void DFS( LGraph Graph,Vertex V,void(*Visit)(Vertex) )//调用函数Visit
{
  PtrToAdjVNode W;
  Visit(V);
  Visited[V]=true;//标记已访问
  for(W=Graph->G[V].FirstEdge; W!=NULL; W=W->next){
    //确保当前结点的每一条边都进行过广度遍历
    if(!Visited[W->AdjV])//如果这条边还没遍历过
      DFS(Graph,W->AdjV,Visit);//对这条边上的新结点进行广度遍历
  }
}
