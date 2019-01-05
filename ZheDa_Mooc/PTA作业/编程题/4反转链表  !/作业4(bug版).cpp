#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100000

/*
�����ҷ���һ����������Ϊ�����ñ����ʽ�ṹʵ��
��ʵ���Ҹ����޷�ָ����Ԫ�صĵ�ַ�Ƕ���
����ò��˵����c���Ե��˾͹涨�˲����������ַ
���ñ��˳��ṹ��ַ�ͱ���������±꣬����ˣ�

���������ڷ����ýṹ������鷴�������


ѧ������֪ʶ
1.printf("%05d",FirstCell);
  printf("%5d",FirstCell);
  ͬ�����Ҷ��룬һ����0����һ���ÿո�
2.�ṹ���а������飬��������[]���룬��Ҫ��ָ������
3.��ʽ�ṹ��˳��ṹ�Ĳ�ͬ����
(1).˳��ṹ����һ���ṹ�壬�ṹ���е��������洢��Ϣ
    �����������־��β���±�
   �������ӵ������и���ı�������־˳��ṹ��λ����Ϣ��)
(2).��ʽ�ṹ����һ���ṹ����ṹ���ָ����ϵ

*/

typedef int ElementType;
typedef struct Node* PtrNode;
struct Node{
	int NextAdr;
	ElementType Digit;
};
struct Node Data[MAXSIZE];

int CreateList(int Size)
{
	ElementType digit;
	int Adr,NextAdr;
	while(Size--){
		scanf("%d %d %d",&Adr,&digit,&NextAdr);
		Data[Adr].Digit=digit;
		Data[Adr].NextAdr=NextAdr;
	}
}

//ǰ�᣺
//�յ���size������ʹ�øú�����Ҳ����˵�ܹ�ִ�д���=����/�ָ���
//�������������ϵķ�ת��ʹ�øú�����Ҳ����˵size>=2
//��������Ǵ���������Щ��size��Ԫ�ģ���������������ݵġ�
//���������ĵ�ԪҪ������Ĵ���Ҳ��˵��Щ��Ԫ֮�����ϵ����������ֵ��Ҫע��

int Inverse(int size,int FirstAdr,int* Connect)
{
	int TempAdr1,TempAdr2;
	if(size>2){//�ָ�����������������
		size=size-1;//n������ֻ��Ҫ����n-1��
		TempAdr1=Data[FirstAdr].NextAdr;
		TempAdr2=TempAdr1;//Ϊ����Ӧ�ƹ�ͳһ
		while(size--){
			TempAdr1=TempAdr2;
			TempAdr2=Data[TempAdr1].NextAdr;
			Data[TempAdr1].NextAdr=FirstAdr;
			// printf("Data[%d].NextAdr=%d",TempAdr1,FirstAdr);
			FirstAdr=TempAdr1;
			// printf("TempAdr1=%d,TempAdr2=%d\n",TempAdr1,TempAdr2);
		}
		*Connect=TempAdr2;
		return FirstAdr;//���ط�ת���ͷ��Ϊ��ʵ�ֵ�Ԫ֮�������
	}else{//�ָ����Ϊ���������
		TempAdr1=FirstAdr;
		TempAdr1=Data[FirstAdr].NextAdr;
		*Connect=Data[TempAdr1].NextAdr;
		Data[TempAdr1].NextAdr=FirstAdr;
		return TempAdr1;//���ط�ת���ͷ
	}
}

int main()
{
	int FirstAdr,size,part;
	scanf("%d %d %d",&FirstAdr,&size,&part);
	CreateList(size);

	int times,head,rear;
	int HeadTemp,RearTemp;
	if(part>1){//����һ����Ҫ��ת
		int Connect;
		times=size/part;

		//����ͷ������һ�η�ת��������
		//�ָԪ�У�ԭ�ȵ�ͷ�ڵ������ɷ�ת���β�ڵ�
		rear=FirstAdr;//�õ���һ�η�ת���β�ڵ�
		head=Inverse(part,FirstAdr,&Connect);//�õ���һ�η�ת���ͷ�ڵ�
		//�����Connect�õ��ָԪ֮��ĵ�һ��Ԫ�ص�ַ
		// printf("head=%d,Connect=%d\n",head,Connect);

		if(size%part==0&&times==1){//������ת��ֻ��һ�η�ת
			Data[rear].NextAdr=-1;
		}else{//������һ����ת��Ԫ����������ת
			times--;//��ȥ���������ĵ�һ��
			while(times--){//�ж����ת��Ԫ�������м��ƹ㴦��
				RearTemp=Connect;//�õ��ڶ����ָԪ��β�ڵ�
				HeadTemp=Inverse(part,Connect,&Connect);//�õ��ڶ����ָԪ��ͷ�ڵ�
				Data[rear].NextAdr=HeadTemp;//����ͷ��Ԫ��������ĵ�Ԫ������
				rear=RearTemp;
			}
			//����β�ʹ�����ʱҪô���ָ�Ҫô�ָ��ʣ�¼����ղ��ɵ�Ԫ������
			if(Connect==-1){//���ָ�
				Data[rear].NextAdr=-1;
			}else{//�ָ�����
				Data[rear].NextAdr=Connect;
			}
		}
	}else
		head=FirstAdr;

	while(Data[head].NextAdr!=-1){
		printf("%05d %d %05d\n",head,Data[head].Digit,Data[head].NextAdr);
		head=Data[head].NextAdr;
	}
	printf("%05d %d %d\n",head,Data[head].Digit,-1);

	return 0;
}
