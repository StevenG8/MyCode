/*******�ڽӱ�洢 -- ��Ȩͼ�ĵ�Դ���·�㷨 -- ���ٽ��******/

// dist[]��path[]ȫ����ʼ��Ϊ-1
//dist[]�Ǵ�ſ�Խ�˶��ٸ��ڵ�
//path[]�Ǵ�Ÿýڵ�A--���ĸ�B�ڵ����·�����

void Route_ShortestNodes(LGraph graph,int dist[],int path[],Vertex S)
{
  Queue Q;
  Vertex V;
  PtrToAdjVNode W;//�ڽ�����ı���Ԫ�� "pointer to adjacent Vertex Node"

  Q=CreateQueue(Graph->Nv);//����һ������װͼ�����нڵ�Ŀն���
  dist[S]=0;//��ʼ��Դ�� "distance"
  InQueue(Q,S);

  while(!IsEmpty(Q)){
    V=DeQueue(Q);
    for(W=Graph->G[V].FirstEdge ; W!=NULL ; W=W->next){//�Ըýڵ�������ڽӵ�ɨ��
      if(dist[W->AdjV] == -1){//�ýڵ㻹δ�����ʹ�
        dist[W->AdjV]=dist[V]+1;//W->AdjV��S�ľ������
        path[W->AdjV]=V;//����W->AdjV�����·������һ���ڵ�
        InQueue(Q,W->AdjV);
      }
    }
  }
}









/***********�ڽӾ���洢 -- ��Ȩͼ�ĵ�Դ���·�㷨*************/
Vertex FindMinDist(MGraph graph,int dist[],int collected[])
{//����δ����¼������dist��С��
  Vertex MinV,V;
  int MinDist = Infinity;

  for(V=0 ; V < graph->Nv ; V++){
    if( !collected[V] && dist[V]<MinDist ){//��Vδ����¼��dist[V]��С
      MinDist=Dist[V];//������̾���
      MinV=V;//���¶�Ӧ����
    }
  }
  if(MinDist<Infinity)
    return MinV;
  else
    return ERROR;
}

/*
  �ڼ�������һ������: 1->2=1,1->3=2, 3!->2
  1��2��ȨֵС��1��3��Ȩֵ��,�� 3��2 ��Ȩֵ��Զ�������ܱ� 1��2 ҪС
*/
bool Dijkstra(MGraph graph,int dist[],int path[],Vertex S)
{
  int collected[MaxVerTexNum];
  Vertex V,W;

  //��ʼ��,�����ڵı���Infinity��ʾ
  for(V=0 ; V < graph->Nv ; V++){
    collected[V]=false;//ȫ������û���ʹ�
    dist[V]=graph->G[S][V];//ȫ�����ǵ�Դ��ľ���
    if(dist[V]<Infinity)
      path[V]=S;//��Щ���Ǹ�Դ�����ڽӵ�
    else
      path[V] = -1;//��Щ���Դ�㲢�����ڽӵ�,���·����ǰһ���ڵ��±�����Ϊ����
  }

  //�Ƚ�Դ����¼
  dist[S]=0;
  collected[S]=true;

  while(1){
    //V =δ����¼���㵫�ܵ�����dist��С��
    V=FindMinDist(Graph,dist,collected);
    if(V=ERROR)
      break;//�����Ѿ��ռ���ϻ��ߴ���ĳЩ���ǹ�����û������

    collected[V]=true;
    for(W=0;W<graph->Nv;W++){//��ͼ�е�ÿһ���������
      /*����õ�δ�����ʲ���������ǰ�ڵ�V���ڽӵ�*/
      if( !collected[W] &&  graph->G[V][W] < Infinity ){ //W��δ���ʲ��ҿ��Դ�V��W
        if(graph->G[V][W] < 0)//���и���,�Ͻ�˹�����㷨������
          return false;
        if(dist[V]+graph->G[V][W] <dist[W] ){//�����¼V�ܹ�ʹ��dist[W]��С������һ������֮���·��
          dist[W]=dist[V]+graph->G[V][W];//���´˵㵽Դ��ľ���
          path[W]=V;//����S��W��·��
        }
      }
    }
  }
  return true;
}






/*************�ڽӾ���洢 -- ��Դ���·�㷨***************/
bool Floyd(MGraph graph,WeightType D[][MaxVerTexNum],Vertex Path[][MaxVerTexNum])
{
  Vertex i,j,k;
  //��ʼ��Ȩֵ
  for(i=0;i<graph->Nv;i++){
    for(j=0;j<graph->Nv;j++){
      D[i][j]=graph->G[i][j];//�����ľ����ʼ��
      path[i][j] = -1;//ȫ����ͨ
    }
  }

  //�������нڵ�֮����ܵ�·��
  for(k=0; k< graph->Nv ; k++){
    for(i=0 ; i< graph->Nv ; i++){
      for(j=0 ; j< graph->Nv ; j++){
        if( D[i][k]+D[k][j] < D[i][j] ){//ԭ�㵽ԭ��(x+x)<x,��Զ���������������������³��������Ǹ�ֵȦ�����ڲ�����if�жϴ���
          D[i][j] = D[i][k]+D[k][j];//����Ȩֵ
          if( i==j && D[i][j]<0 )//���ָ�ֵȦ������
            return false;
          //i-k-j(i)���γ���һ��Ȧ������һ���ڵ�֮��Ȩֵ��С��֤���б��Ǹ�ֵ
          //ֻҪÿ���ߵ�Ȩֵ��Ϊ�������ܽ����Ҳ����˵����㷨ֻ�������Ȩֵ
          path[i][j]=k;//��Դ�����������·�� �ȵ��ڵ�k
        }
      }
    }
  }

  return true;
}
