#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int a,b,c,d;
int arr[150][150];
int arr2[150];
void sum(int pos,int* polje)
{
	for(int i=0;i<b;++i)
	{
		polje[i]+=arr[pos][i];
		polje[i]%=2;
	}
}
bool ok(int br)
{
	for(int i=0;i<8;++i)
	{
		if(br==i && arr2[i]==0)
			return false;
		if(br!=i && arr2[i]==1)
			return false;
	}
	return true;
}
bool ka[10];
int main()
{
	scanf("%d%d",&a,&b);
	for(int i=0;i<a;++i)
	{
		for(int j=0;j<b;++j)
		{
			scanf("%d",&arr[i][j]);
		}
	}
	for(int z=7;z>=0;--z)
	{
		for(int i=0;i<(1<<8);++i)
		{
			for(int j=0;j<8;++j)
			{
				if(true)
				{
					if((i&(1<<j))!=0)
					{
						sum(j,arr2);
					}
				}
			}
			/*for(int j=0;j<a;++j)
				printf("%d ",arr2[j]);
			printf("\n");*/
			bool oka =false;
			for(int k=0;k<8;++k)
			{
				if(ka[k]==false && ok(k))
				{
					printf("OK %d\n",k);
					ka[k]=true;
					oka = true;
					for(int j=0;j<b;++j)
						arr[z][j]=arr2[j];
					break;
				}
			}
			for(int j=0;j<b;++j)
				arr2[j] = 0;
			if(oka)break;
		}
	}
	for(int i=0;i<a;++i)
	{
		for(int j=0;j<b;++j)
			printf("%d ",arr[i][j]);
		printf("\n");
	}
	return 0;
}
