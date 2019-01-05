/*******邻接表存储 -- 无权图的单源最短路算法 -- 最少结点******/

// dist[]和path[]全部初始化为-1
//dist[]是存放跨越了多少个节点
//path[]是存放该节点A--从哪个B节点过来路径最短

void Route_ShortestNodes(LGraph graph,int dist[],int path[],Vertex S)
{
  Queue Q;
  Vertex V;
  PtrToAdjVNode W;//邻接链表的表中元素 "pointer to adjacent Vertex Node"

  Q=CreateQueue(Graph->Nv);//生成一个可以装图中所有节点的空队列
  dist[S]=0;//初始化源点 "distance"
  InQueue(Q,S);

  while(!IsEmpty(Q)){
    V=DeQueue(Q);
    for(W=Graph->G[V].FirstEdge ; W!=NULL ; W=W->next){//对该节点的所有邻接点扫描
      if(dist[W->AdjV] == -1){//该节点还未被访问过
        dist[W->AdjV]=dist[V]+1;//W->AdjV到S的距离更新
        path[W->AdjV]=V;//到达W->AdjV的最短路径的上一个节点
        InQueue(Q,W->AdjV);
      }
    }
  }
}









/***********邻接矩阵存储 -- 有权图的单源最短路算法*************/
Vertex FindMinDist(MGraph graph,int dist[],int collected[])
{//返回未被收录顶点中dist最小者
  Vertex MinV,V;
  int MinDist = Infinity;

  for(V=0 ; V < graph->Nv ; V++){
    if( !collected[V] && dist[V]<MinDist ){//若V未被收录且dist[V]更小
      MinDist=Dist[V];//更新最短距离
      MinV=V;//更新对应顶点
    }
  }
  if(MinDist<Infinity)
    return MinV;
  else
    return ERROR;
}

/*
  期间利用了一个定理: 1->2=1,1->3=2, 3!->2
  1到2的权值小，1到3的权值大,则 3到2 的权值永远都不可能比 1到2 要小
*/
bool Dijkstra(MGraph graph,int dist[],int path[],Vertex S)
{
  int collected[MaxVerTexNum];
  Vertex V,W;

  //初始化,不存在的边用Infinity表示
  for(V=0 ; V < graph->Nv ; V++){
    collected[V]=false;//全部都还没访问过
    dist[V]=graph->G[S][V];//全部都是到源点的距离
    if(dist[V]<Infinity)
      path[V]=S;//这些点是跟源点是邻接点
    else
      path[V] = -1;//这些点跟源点并不是邻接点,最短路径的前一个节点下标设置为负数
  }

  //先将源点收录
  dist[S]=0;
  collected[S]=true;

  while(1){
    //V =未被收录顶点但能到达中dist最小者
    V=FindMinDist(Graph,dist,collected);
    if(V=ERROR)
      break;//顶点已经收集完毕或者存在某些点是孤立点没有连接

    collected[V]=true;
    for(W=0;W<graph->Nv;W++){//对图中的每一个顶点遍历
      /*如果该点未被访问并且他跟当前节点V是邻接点*/
      if( !collected[W] &&  graph->G[V][W] < Infinity ){ //W点未访问并且可以从V到W
        if(graph->G[V][W] < 0)//若有负边,迪杰斯特拉算法不能用
          return false;
        if(dist[V]+graph->G[V][W] <dist[W] ){//如果收录V能够使得dist[W]变小，建立一条他们之间的路径
          dist[W]=dist[V]+graph->G[V][W];//更新此点到源点的距离
          path[W]=V;//更新S到W的路径
        }
      }
    }
  }
  return true;
}






/*************邻接矩阵存储 -- 多源最短路算法***************/
bool Floyd(MGraph graph,WeightType D[][MaxVerTexNum],Vertex Path[][MaxVerTexNum])
{
  Vertex i,j,k;
  //初始化权值
  for(i=0;i<graph->Nv;i++){
    for(j=0;j<graph->Nv;j++){
      D[i][j]=graph->G[i][j];//两点间的距离初始化
      path[i][j] = -1;//全部不通
    }
  }

  //遍历所有节点之间可能的路径
  for(k=0; k< graph->Nv ; k++){
    for(i=0 ; i< graph->Nv ; i++){
      for(j=0 ; j< graph->Nv ; j++){
        if( D[i][k]+D[k][j] < D[i][j] ){//原点到原点(x+x)<x,永远不满足这个条件，不会更新出错，除非是负值圈但在内部做了if判断处理
          D[i][j] = D[i][k]+D[k][j];//更新权值
          if( i==j && D[i][j]<0 )//发现负值圈，错误
            return false;
          //i-k-j(i)，形成了一个圈，经过一个节点之后权值变小！证明有边是负值
          //只要每条边的权值都为正数就能解决，也就是说这个算法只能针对正权值
          path[i][j]=k;//从源点来到这里的路径 先到节点k
        }
      }
    }
  }

  return true;
}
