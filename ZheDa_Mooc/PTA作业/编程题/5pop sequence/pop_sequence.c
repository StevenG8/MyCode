#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
struct SNode{
	ElementType* Data;
	int top;
};
typedef struct SNode* Stack;

/*�Զ�ջ�ĳ������*/
Stack CreatEmptyStack(int length)
{
	Stack S=(Stack)malloc(sizeof(struct SNode));
	S->Data=(ElementType*)malloc(length*sizeof(ElementType));
	S->top=-1;
	return S;
}

int Push(Stack S,ElementType X,int MAXSIZE)
{
	if(S->top==MAXSIZE-1){
		/*printf("��ջ����\n");*/
		return 0;
    }
	else{
	    S->Data[++(S->top)]=X;
	    return 1;
    }
}

ElementType Pop(Stack S)
{
	if(S->top==-1){
		/*printf("ջ��\n");*/
		return 0;
	}else{
		return S->Data[(S->top)--];
	}
}


int judge(ElementType* digit,int length,int MAXSIZE)//����һ�н����ж�
{
  int i;
  Stack S=CreatEmptyStack(length);//�����ն�ջ
  for(i=1;i<=length;i++){
    if(Push(S,i,MAXSIZE)){//�����ջ�ɹ�
      while(S->Data[S->top]==(*digit)){//���ջ��Ԫ���Ƿ����
        digit=digit+1;//����������ʽ�ӵ���һ��Ԫ�� 
        Pop(S);
        /*printf("%d\n",Pop(S));*/
      }
    }else{
	  	/*printf("ջ����\n");*/
		break;//�����ջ������ôֱ������
	}
  }

  if(S->top==-1){
  	free(S);
	return 1;//��ջ�ǿյģ�֤�����ʽ�ӿ��Ա���ջ��ʾ 
  }else{
  	free(S);
  	return 0;//��ջ�����ģ�֤�����ʽ���޷�����ջ��ʾ
  }
  
}


int main()
{
  int maxsize,LengthPush,CheckNumber;
  int i,j;
  scanf("%d %d %d",&maxsize,&LengthPush,&CheckNumber);

  ElementType Temp[CheckNumber][LengthPush];
  for(j=0;j<CheckNumber;j++){
    for(i=0;i<LengthPush;i++){
      scanf("%d",&Temp[j][i]);
    }
  }
  
  for(j=0;j<CheckNumber;j++){
    if(judge(&Temp[j][0],LengthPush,maxsize)==1)
      printf("YES\n");
    else
      printf("NO\n");
  }
  
  return 0;
}
