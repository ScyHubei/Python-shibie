#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include<time.h>

int i,j;
int k,g;
int l;
int z;//����������
int dis[100][10000];//����
int index[100][10000];//��¼10���㣬����֪��ľ���
int Lei[50][2];//��¼ÿ�������ֵĴ���
int a[10000][3];//����
int b[100][3];//δ֪��
FILE*fp = fopen("D:\\KNN.txt","w");
void LeiShu()
{
	printf("���������δ֪��ĸ�����");
	scanf("%d",&k);
	printf("�����������������");
	scanf("%d",&z);
	printf("��������֪�����ĸ�����");
	scanf("%d",&g);
	printf("������Kֵ��");
	scanf("%d",&l);
}
//������������������������
void Random()
{
	srand((int)time(NULL));
	for (i=0;i<g;i++)
	{
		for (int j = 0; j < 2; j++)
		{
			a[i][j] = rand()%100;
		}
		printf("%d  ",a[i][0]);
		printf("%d  ",a[i][1]);
		a[i][2] = rand()%z;
		printf("%d  %d\n",a[i][2],i);
		printf("-----------\n");
	}
}
//�������δ֪��
void Unkonw_P()
{
	srand((int)time(NULL));
	for (i=0;i<k;i++)
	{
		for (int j = 0; j < 2; j++)
		{
			b[i][j] = rand()%100;
		}
		printf("%d   %d\n",b[i][0],b[i][1]);
	}
}
//������룬��ÿһ����ľ������򣬾�����±���֮�仯��
void Find_K()
{
	for (int j = 0; j < k; j++)
	{
		for (int i = 0; i < g; i++)
		{
			dis[j][i] = (b[j][0]-a[i][0])*(b[j][0]-a[i][0])+(b[j][1]-a[i][1])*(b[j][1]-a[i][1]);
			index[j][i] = i;
		}
	}
	int count = 0;
	int weizhi = 0;
	for (int i = 0; i < k; i++)
	{
		for (int m = 0; m < g; m++)
		{
			for (int n = 0; n < g-1; n++)
			{
				if (dis[i][n]>dis[i][n+1])
				{
					count = dis[i][n];
					dis[i][n] = dis[i][n+1];
					dis[i][n+1] = count;
					weizhi = index[i][n];
					index[i][n] = index[i][n+1];
					index[i][n+1] = weizhi;
				}
			}
		}
	}
}
//�ҵ���δ֪�������K��ֵ������ͨ��index[]������������ֵ��
//��ÿһ��δ֪���K�ڽ���������ִ������м�¼���ҵ�����������𣬼�δ֪������
void K_Point()
{
	int m1 = 0;
	int n1 = 0;
	for (int i = 0; i < k; i++)
	{
		int max = -999;
		for (int m= 0; m < z ; m++)
		{
			Lei[m][0] = m;
			Lei[m][1] = 0;
		}
		for (int j = 0; j < l ; j++)
		{
			m1 = index[i][j];
			n1 = a[m1][2];
			Lei[n1][1] = Lei[n1][1] + 1;
		}
		for (int j = 0; j < z; j++)
		{
			printf("%d   %d\n",Lei[j][0],Lei[j][1]);
			fprintf(fp,"%d   %d\n",Lei[j][0],Lei[j][1]);
			if (Lei[j][1]>max)
			{
				max = Lei[j][1];
				b[i][2] = Lei[j][0];
			}
		}
		printf("��%d���㣺%d��%d�������%d\n",i+1,b[i][0],b[i][1],b[i][2]);
		fprintf(fp,"��%d��������Ϊ%d %d�����Ϊ%d\n",i+1,b[i][0],b[i][1],b[i][2]);
	}
}
int main(void)
{
	FILE*fp = fopen("D:\\KNN.txt","w");
	LeiShu();
	Random();
	Unkonw_P();
	Find_K();
	K_Point();
}



