#include <stdio.h>
#include <math.h>

#define Maxsize 100
#define radius 7.5
#define SideLength 50

struct Node{
  int x,y;
}XY[Maxsize];

int range,num;
bool flag=0;
bool Visited[Maxsize]={false};

bool FirstJump(int i)
{
  float distance=sqrt(pow(XY[i].x,2)+pow(XY[i].y,2));
  return (distance-radius)<=range;
}

bool getreach(int i,int j)
{
  float distance=sqrt( pow((XY[i].x - XY[j].x) , 2) + pow( (XY[i].y - XY[j].y) , 2) );
  return distance<=range;
}

bool IsSafe(int i)
{
  int absX=abs(XY[i].x);
  int absY=abs(XY[i].y);
  return (absX+range>=SideLength) || (absY+range>=SideLength);
}

void DFS(int i)
{
  if( IsSafe(i) ){
	  flag=1;
    return;
  }

  Visited[i]=true;//�ý���ѷ���

  for(int j=0;j<num;j++){//����������������δ���ʹ����ڽӵ�
  	if(flag==1)
      break;
  	if(!Visited[j] && getreach(i,j))
	    DFS(j);
  }
}

int main()
{
  scanf("%d %d",&num,&range);
  for(int i=0;i<num;i++){
    scanf("%d %d",&XY[i].x,&XY[i].y);
  }
  for(int i=0;i<num;i++){//�������Ե����ڽӵ�ȫ������
    if(flag==1) break;
    if( !Visited[i] && FirstJump(i) ){
//      printf("��һ�������%d����\n",i);
      DFS(i);
    }
  }
  if(flag==1) printf("Yes\n");
  else        printf("No\n");

}
