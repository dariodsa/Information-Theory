#include <stdio.h>
#include <stdlib.h>
//Govorimo o LBK 16,8,5  ==> n k d(k)
int polje[8];
int rez[16];
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
void mul()
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
void solve(FILE *inputFile, FILE *outputFile)
{
	unsigned char oktet;
	while(fread(&oktet,sizeof(unsigned char),1,inputFile)==1)
	{
		//printf("nest\n");
		polje[0]=(oktet & 128)!=0;
		polje[1]=(oktet & 64)!=0;
		polje[2]=(oktet & 32)!=0;
		polje[3]=(oktet & 16)!=0;
		polje[4]=(oktet & 8)!=0;
		polje[5]=(oktet & 4)!=0;
		polje[6]=(oktet & 2)!=0;
		polje[7]=(oktet & 1)!=0;
		//printf("OKTET %uc",oktet);
		mul();
		
		unsigned char broj1=rez[7] + 2*rez[6] + 4*rez[5] + 8*rez[4] + 16*rez[3] + 32*rez[2] + 64*rez[1] + 128*rez[0];
		unsigned char broj2=rez[15] + 2*rez[14] + 4*rez[13] + 8*rez[12] + 16*rez[11] + 32*rez[10] + 64*rez[9] + 128*rez[8];
		if(oktet!=0)printf("%d %d %d\n",oktet, broj2,broj1);
		//printf("%c %c\n",broj1,broj2);
		fwrite(&broj1,sizeof(unsigned char),1,outputFile);
		fwrite(&broj2,sizeof(unsigned char),1,outputFile);
	}
}

int main(int argc, char *argv[])
{
	FILE *inputFile  = fopen(argv[1],"rb");
	FILE *outputFile = fopen(argv[2],"wb");;
	solve(inputFile,outputFile);
	fclose(inputFile);
	fclose(outputFile);
	return 0;
}
