#include <stdio.h>
#include <stdlib.h>
//Govorimo o LBK 16,8,5  ==> n k d(k)
int polje[16];
int rez[8];
int G[8][16]={
	{1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	1,	1,	0,	1},
	{0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	1,	1	},
	{0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	1,	1,	0	},
	{0,	0,	0,	1,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	1,	1},
	{0,	0,	0,	0,	1,	0,	0,	0,	1,	1,	1,	0,	0,	0,	0,	1	},
	{0,	0,	0,	0,	0,	1,	0,	0,	1,	1,	0,	1,	0,	1,	0,	0	},
	{0,	0,	0,	0,	0,	0,	1,	0,	0,	1,	1,	1,	0,	0,	1,	0	},
	{0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	1,	1,	1,	0,	0,	0	}
};
int H[8][16]={
	{0,	0,	0,	1,	1,	1,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0	},
	{1,	0,	0,	0,	1,	1,	1,	0,	0,	1,	0,	0,	0,	0,	0,	0	},
	{0,	0,	1,	0,	1,	0,	1,	1,	0,	0,	1,	0,	0,	0,	0,	0	},
	{0,	1,	0,	0,	0,	1,	1,	1,	0,	0,	0,	1,	0,	0,	0,	0	},
	{1,	0,	1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	1,	0,	0,	0	},
	{1,	1,	1,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0	},
	{0,	1,	1,	1,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0},
	{1,	1,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1	}
};
int H_T[16][8];
void transpone()
{
	int i;
	int j;
	for(i=0;i<8;++i)
	{
		for(j=0;j<16;++j)
			H_T[j][i]=H[i][j];
	}
}
void mul()
{
	int i;
	for(i=0;i<8;++i)
	{
		int j;
		rez[i]=0;
		for(j=0;j<16;++j)
		{
			rez[i]+=polje[j]*H_T[j][i];
		}
		rez[i]=rez[i]%2;
	}
}
void mul2()
{
	int j,k;
	for(j=0;j<16;++j)
	{
		
		rez[j]=0;
		for(k=0;k<8;++k)
		{
			rez[j]+=polje[k]*G[k][j];
		}
		rez[j]=rez[j]%2;
	}
}
int arr[4545];
int br = 0;
void addInputs()
{
	int i,j;
	for(i=0;i<(1<<8);++i)
	{
		for(j=7;j>=0;--j)
		{
			polje[7-j]= (i & (1<<j))!=0;
		}
		/*for(j=0;j<8;++j)
			printf("%d ",polje[j]);*/
		//printf("\n");
		mul2();
		int broj=0;
		for(j=0;j<16;++j)
		{
			arr[br] += rez[j] * (1<<(15-j));
		}
		printf("%d.%d  %d\n",br,i,arr[br]);
		++br;
	}
}
int nadi(unsigned short oktet)
{
	int i;
	for(i=0;i<br;++i)
	{
		if(arr[i]==oktet)
			return i;
	}
	return -1;
}
int correction()
{
	int i,j;
	for(i=0;i<16;++i)
	{
		int ca=1;
		for(j=0;j<8;++j)
		{
			if(rez[j]!=H[j][i])
				ca=0;
		}
		if(ca==1)
		{
			polje[i]=!polje[i];
			return i;
		}
	}
	int k;
	int ko1 = rand()%14 +1;
	int ko2 = rand()%14 +1;
	for(i=ko1;i!=ko1-1;i=(i+1)%16)
	{
		for(j=ko2;j!=ko2-1;j=(j+1)%16)
		{
			//printf("%d %d %d %d\n",i,j,ko1,ko2);
			int ca=1;
			if(i!=j)
			for(k=0;k<8;++k)
			{
				if(!(rez[k]!=H[k][i] && rez[k]==H[k][j]))
					ca=0;
				if(!(rez[k]==H[k][i] && rez[k]!=H[k][j]))
					ca=0;
			}
			if(ca==1)
			{
				polje[i]=!polje[i];
				polje[j]=!polje[j];
				return -2;
			}
		}
	}
	return -1;
}
void solve(FILE *inputFile, FILE *outputFile)
{
	transpone();
	addInputs();
	int prvi=0;
	//printf("%d\n",fread(&oktet,sizeof(unsigned short),1,inputFile));
	//printf("%d\n",oktet);
	int dobri =0;
	int losi=0;
	while(fread(&prvi,sizeof(unsigned char),1,inputFile)==1)
	{
		int drugi ;
		fread(&drugi,sizeof(unsigned char),1,inputFile);
		unsigned int oktet=0;
		int find = -1;
		int i;
		int c=0;
		//printf("%d %d\n",prvi,drugi);
		/*if(oktet!=0)
			printf("%d\n",oktet);*/
		
		
		polje[15]=(drugi & 1)!=0;
		polje[14]=(drugi & 2)!=0;
		polje[13]=(drugi & 4)!=0;
		polje[12]=(drugi & 8)!=0;
		polje[11]=(drugi & 16)!=0;
		polje[10]=(drugi & 32)!=0;
		polje[9]=(drugi & 64)!=0;
		polje[8]=(drugi & 128)!=0;
		polje[0]=(prvi & 128)!=0;
		polje[1]=(prvi & 64)!=0;
		polje[2]=(prvi & 32)!=0;
		polje[3]=(prvi & 16)!=0;
		polje[4]=(prvi & 8)!=0;
		polje[5]=(prvi & 4)!=0;
		polje[6]=(prvi & 2)!=0;
		polje[7]=(prvi & 1)!=0;
		//printf("%d %d\n",prvi,drugi);
		/*for(i=0;i<16;++i)
			printf("%d ",polje[i]);
		printf("\n");*/
		//if(oktet!=0)printf("%d\n",oktet);
		//int oktet=0;
		
		mul();
		
		for(i=0;i<8;++i)
			if(rez[i]>0)c=1;
		/*if(c)
		{for(i=0;i<8;++i)
			printf("%d ",rez[i]);
		printf("\n");}*/
		int corr=correction();
		printf("%d ",corr);
		/*if(corr==7) polje[7] = !polje[7];
		if(corr==6) polje[6] = !polje[6];
		if(corr==5) polje[5] = !polje[5];
		if(corr==4) polje[4] = !polje[4];
		if(corr==3) polje[3] = !polje[3];
		if(corr==2) polje[2] = !polje[2];
		if(corr==1) polje[1] = !polje[1];
		if(corr==0) polje[0] = !polje[0];*/
		
		unsigned int broj1 =0 ;
		find = nadi(prvi);
		if(c!=0)
		{	//printf("NIJE DOBRO %d\n",oktet);
			++losi;
			//broj1=polje[15] + 2*polje[14] + 4*polje[13] + 8*polje[12] + 16*polje[11] + 32*polje[10] + 64*polje[9] + 128*polje[8];
		}
		else
		{
			++dobri;
			broj1=find;
		}
		//printf("%d\n",broj1);
		broj1=polje[7] + 2*polje[6] + 4*polje[5] + 8*polje[4] + 16*polje[3] + 32*polje[2] + 64*polje[1] + 128*polje[0];
		//broj1=polje[15] + 2*polje[14] + 4*polje[13] + 8*polje[12] + 16*polje[11] + 32*polje[10] + 64*polje[9] + 128*polje[8];
		//if(broj1!=0)printf("%d\n",broj1);
		//unsigned int broj2=rez[15] + 2*rez[14] + 4*rez[13] + 8*rez[12] + 16*rez[11] + 32*rez[10] + 64*rez[9] + 128*rez[8];
		//if(broj1!=0)printf("%d %d\n",broj1,find);
		int br = fwrite(&broj1,sizeof(unsigned char),1,outputFile);
		if(br!=1)printf("KOKOK\n");
		//fwrite(&broj2,sizeof(unsigned short),1,outputFile);
	}
	printf("%d %d\n",dobri,losi);
}

int main(int argc, char *argv[])
{
	FILE *inputFile  = fopen(argv[1],"rb");
	FILE *outputFile = fopen(argv[2],"wb");
	solve(inputFile,outputFile);
	fclose(inputFile);
	fclose(outputFile);
	return 0;
}
