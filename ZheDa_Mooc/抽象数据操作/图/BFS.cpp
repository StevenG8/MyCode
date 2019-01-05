//广度搜索---邻接矩阵

/*
  IsEdge(Graph,V,W)检查<V,W>是否图Graph中的一条边,即W是否为V的邻接点
  此函数根据图的不同类型要做不同的实现,关键取决于对不存在的边的表示方法
*/

//例如对有权图,如果不存在的边被初始化为INFINITY,则函数实现如下:
//这里的Visited数组是全局变量

#define INFINITY 65536
bool IsEdge(MGraph Graph,Vertex V,Vertex W)
{
  return Graph->G[V][W]<INFINITY? true:false;
}
void BFS(MGraph Graph,Vertex S,void(*Visit)(Vertex))
{
  Queue Q;
  Vertex V,W;

  Q=CreateQueue(Maxsize);
  Visit(S);
  Visited[S]=true;//标志已访问
  AddQ(Q,S);//入列

  while(!IsEmpty(Q)){//队列不空
    V=DeleteQ(Q);//弹出邻接点
    for(W=0;W<Graph->nv;W++){//遍历所有点
      if(!Visited[W]&&IsEdge(Graph,V,W)){
        //如果还没被访问过并且是该点的邻接点(边)
        Visit(W);
        Visited[W]=true;
        AddQ(Q,W);//邻接点入列
      }
    }
  }

}
