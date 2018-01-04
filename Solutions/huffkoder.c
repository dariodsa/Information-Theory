#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int arr[1024];
int jesam[1024];
char oznake[1024][1024];
typedef struct Cvor
{
	int value;
	int *arr;
	int len;
} Cvor;
Cvor cvor[1024];
void dodaj(int pos,char znak)
{
	int i;
	for(i=0;i<1024;++i)
	{
		if(oznake[pos][i]==0)
		{
			oznake[pos][i] = znak;
			return;
		}
	}
	return;
}
int maxi(int izostavi)
{
	int br = 0x3f3f3f3f;
	int pos = -1;
	int i;
	for(i=0;i<(1<<8);++i)
	{
		if(br>cvor[i].value && i!=izostavi && cvor[i].value!=-2)
		{
			br = cvor[i].value;
			pos = i;
		}
		if(br>=cvor[i].value && cvor[pos].len>cvor[i].len && i!=izostavi && cvor[i].value!=-2)
		{
			br = cvor[i].value;
			pos = i;
		}
	}
	return pos;
}
void solve(FILE *inputFile, FILE *huffTable, FILE *outputFile)
{
	unsigned int oktet;
	int num=0;
	while(fread(&oktet,sizeof(char),1,inputFile)==1)
	{
		arr[(int)oktet]++;
		++num;
	}
	int i;
	for(i=0;i<(1<<8);++i)
	{
		cvor[i].value  = arr[i];
		cvor[i].arr    =(int*) malloc(sizeof(int));
		cvor[i].arr[0] = i;
		cvor[i].len = 1;
	}
	
	int j;
	for(i=0;i<(1<<8)-1;++i)
	{
		int pos = maxi(-1);
		int pos2 = maxi(pos);
		//printf("POS %d %d\n",pos,cvor[pos].value);
		//printf("POS2 %d %d\n",pos2,cvor[pos2].value);
		cvor[pos].value = cvor[pos].value + cvor[pos2].value;
		for(j=0;j<cvor[pos].len;++j)
		{
			dodaj(cvor[pos].arr[j],'0');
		}
		for(j=0;j<cvor[pos2].len;++j)
			dodaj(cvor[pos2].arr[j],'1');
		
		cvor[pos].arr   = (int*)realloc(cvor[pos].arr,sizeof(int)*(cvor[pos].len + cvor[pos2].len));
		for(j=0;j<cvor[pos2].len;++j)
			cvor[pos].arr[cvor[pos].len+j] = cvor[pos2].arr[j];
		cvor[pos].len   = cvor[pos].len + cvor[pos2].len;
		cvor[pos2].value = -2;
	}
	for(i=0;i<(1<<8);++i)
	{
		int val = 0;
		
		for(j=0;j<strlen(oznake[i]);--j)
		{
			val = val*2 + oznake[i][j] - '0';
			//printf
		}
		//printf("%d %s\n",val,oznake[i]);
		fprintf(huffTable,"%s\n",oznake[i]);
	}
	fseek(inputFile, 0, SEEK_SET);
	
	while(fread(&oktet,sizeof(char),1,inputFile)==1)
	{
		arr[(int)oktet]++;
		char val = 0;
		for(j=0;j<strlen(oznake[oktet]);++j)
		{
			val = val*2 + oznake[oktet][j] - '0';
			
		}
		--num;
		
		fwrite(&val,sizeof(char),1,outputFile);
		//fflush(outputFile);
	}
	fclose(huffTable);
	fclose(outputFile);
}
int main(int argc, char *argv[])
{
	FILE *inputFile = fopen(argv[1],"rb");
	FILE *huffTable = fopen(argv[2],"w");
	FILE *outputFile = fopen(argv[3],"wb");
	solve(inputFile, huffTable, outputFile);
	return 0;
}
