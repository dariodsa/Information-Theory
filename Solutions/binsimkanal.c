#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char inputPath[500];
char outputPath[500];
double eta;
void sol(FILE *inputFile,FILE *outputFile,double eta)
{
	unsigned char broj;
	while(fread(&broj,sizeof(unsigned  char),1,inputFile)==1)
  	{
		int i;
		for(i=0;i<8;++i)
		{
			int randa=rand()%1000;
			double koef=randa/1000.0;
			if(koef<=eta)
			{
				if(broj&(1<<i))
					broj-=(1<<i);
				else if(!(broj&(1<<i)))
					broj+=(1<<i);
			}
		}
		
		fwrite(&broj,sizeof(unsigned char),1,outputFile);
	}
}
double toDouble(char *q)
{
	double ans=0;
	int beforeDot=1;
	double ten=0.1;
	while(*q)
	{
		if(*q=='.')
		{
			beforeDot=0;
		}
		else
			if(beforeDot)
				ans=ans*10+(*q-'0');
			else
			{
				ans=ans+(*q-'0')*ten;
				ten/=10.0;
			}
		++q;
	}
	return ans;
}
int main(int argc, char *argv[])
{
	
	eta=toDouble(argv[2]);
	
	FILE *inputFile=fopen(argv[1],"rb");
	FILE *outputFile=fopen(argv[3],"wb");
	
	sol(inputFile,outputFile,eta);
	
	fclose(inputFile);
	fclose(outputFile);
	return 0;
}
