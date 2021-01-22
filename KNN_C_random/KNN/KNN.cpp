#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include<time.h>

int i,j;
int k,g;
int l;
int z;//分类的类别数
int dis[100][10000];//距离
int index[100][10000];//记录10个点，到已知点的距离
int Lei[50][2];//记录每个类别出现的次数
int a[10000][3];//样本
int b[100][3];//未知点
FILE*fp = fopen("D:\\KNN.txt","w");
void LeiShu()
{
	printf("请输入随机未知点的个数：");
	scanf("%d",&k);
	printf("请输入分类的类别数：");
	scanf("%d",&z);
	printf("请输入已知样本的个数：");
	scanf("%d",&g);
	printf("请输入K值：");
	scanf("%d",&l);
}
//生成随机数样本，并随机分类
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
//生成随机未知点
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
//计算距离，对每一个点的距离排序，距离的下标随之变化。
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
//找到距未知点最近的K个值，并且通过index[]索引获得其分类值，
//对每一个未知点的K邻近点的类别出现次数进行记录，找到出现最多的类别，即未知点的类别。
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
		printf("第%d个点：%d、%d的类别是%d\n",i+1,b[i][0],b[i][1],b[i][2]);
		fprintf(fp,"第%d个点坐标为%d %d的类别为%d\n",i+1,b[i][0],b[i][1],b[i][2]);
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



