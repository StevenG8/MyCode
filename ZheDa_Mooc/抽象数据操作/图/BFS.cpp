//�������---�ڽӾ���

/*
  IsEdge(Graph,V,W)���<V,W>�Ƿ�ͼGraph�е�һ����,��W�Ƿ�ΪV���ڽӵ�
  �˺�������ͼ�Ĳ�ͬ����Ҫ����ͬ��ʵ��,�ؼ�ȡ���ڶԲ����ڵıߵı�ʾ����
*/

//�������Ȩͼ,��������ڵı߱���ʼ��ΪINFINITY,����ʵ������:
//�����Visited������ȫ�ֱ���

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
  Visited[S]=true;//��־�ѷ���
  AddQ(Q,S);//����

  while(!IsEmpty(Q)){//���в���
    V=DeleteQ(Q);//�����ڽӵ�
    for(W=0;W<Graph->nv;W++){//�������е�
      if(!Visited[W]&&IsEdge(Graph,V,W)){
        //�����û�����ʹ������Ǹõ���ڽӵ�(��)
        Visit(W);
        Visited[W]=true;
        AddQ(Q,W);//�ڽӵ�����
      }
    }
  }

}
