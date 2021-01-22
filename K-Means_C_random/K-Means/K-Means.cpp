#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include<time.h>

int i ,j;
int a[1000][3];
int k ;
int x[50];
int y[50];
int dis[50];
int CS = 0;
FILE*fp = fopen("D:\\K-Means.txt","w");
void leibie()
{
	printf("输入分类的类别：");
	scanf("%d", &k);
}
//生成未知点的随机坐标，无属性值
void random()
{
	srand((int)time(NULL));
	for (i = 0;i <1000;i++)
	{
		for (j = 0;j<2;j++)
		{
			a[i][j] = rand()%100;
		}
		//printf("随机数坐标%d  %d\n",a[i][0],a[i][1]);
	}
}
//生成中心点坐标
void Get_center()
{
	srand((int)time(NULL));
	for (int i = 0; i < k; i++)
	{
		x[i]= rand()%100;
		y[i]= rand()%100;
		printf("第1次迭代的第%d个中心点:%d,%d\n",i+1,x[i],y[i]);
		fprintf(fp,"第1次迭代的第%d个中心点:%d,%d\n",i+1,x[i],y[i]);
	}
	fprintf(fp,"------------------------\n");
}
void Get_dict()
{
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < k; j++)
		{
			dis[j] = (a[i][0]-x[j])*(a[i][0]-x[j])+(a[i][1]-y[j])*(a[i][1]-y[j]);
		}
		int min = 999999;
		int count;
		for (int j = 0; j < k; j++)
		{
			if (dis[j] < min)
			{
				min = dis[j];
				count = j;
			}
		}
		a[i][2] = count;
	}
}
void Get_Newcent()
{
	int G[50];
	int XSum[50] ,YSum[50];
	for (int i = 0; i < k; i++)
	{
		G[i] = 0;
		XSum[i] = 0;
		YSum[i] = 0;
	}
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (a[i][2] == j)
			{
				XSum[j] = XSum[j] + a[i][0];
				YSum[j] = YSum[j] + a[i][1];
				G[j]=G[j] + 1;
			}
		}
	}
	for (int i = 0; i < k; i++)
	{
		x[i] = int(XSum[i]/G[i]);
		y[i] = int(YSum[i]/G[i]);
		fprintf(fp,"第%d次迭代的第%d个中心：%d %d\n",CS+2,i+1,x[i],y[i]);
		printf("第%d次迭代的第%d个中心：%d %d\n",CS+1,i+1,x[i],y[i]);
	}
	fprintf(fp,"------------------------\n");
}
int main(void)
{
	FILE*fp = fopen("D:\\K-Means.txt","w");
	leibie();
	random();
	Get_center();
	while (CS<6)
	{
		Get_dict();
		printf("第%d次聚类\n",CS+1);
		Get_Newcent();
		CS = CS+1;
	}
	fprintf(fp,"最终结果\n");
	for (int i = 0; i < 1000; i++)
	{
		fprintf(fp,"第%d个点的坐标为%d.%d的点属于第%d类\n",i+1,a[i][0],a[i][1],a[i][2]);
		printf("第%d个点的坐标为%d.%d的点属于第%d类\n",i+1,a[i][0],a[i][1],a[i][2]);
	}
}