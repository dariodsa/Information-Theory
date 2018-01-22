#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

typedef struct Cvor
{
	char znak;
	int pos;
} Cvor;
int numCvor=1;
Cvor* V[950000];
int sizeOfArray[950000];
int find(char *S)
{
	int len=strlen(S);
	int cvor=0;
	int i,j;
	
	for(i=0;i<len;++i)
	{
		int find=0;
		for(j=0;j<sizeOfArray[cvor];++j)
		{
			if(V[cvor][j].znak==S[i])
			{
				find=1;
				cvor=V[cvor][j].pos;
				break;
			}
		}
		if(!find)return 0;
	}
	return 1;
}
void add(char *S)
{
	int len=strlen(S);
	int cvor=0;
	int i,j,k;
	for(i=0;i<len;++i)
	{
		int find=0;
		for(j=0;j<sizeOfArray[cvor];++j)
		{
			if(V[cvor][j].znak==S[i])
			{
				find=1;
				cvor=V[cvor][j].pos;
				break;
			}
		}
		if(!find)
		{
			//pocni dodavati
			//printf("Pocinjem dodavati...\n");
			for(k=i;k<len;++k)
			{
				Cvor C;
				C.pos=numCvor++;
				C.znak=S[k];
				
				//V[cvor].push_back(C);
				V[cvor] = (Cvor*) realloc(V[cvor],sizeof(Cvor)*(sizeOfArray[cvor]+1));
				++sizeOfArray[cvor];
				//V[cvor][sizeOfArray[cvor]-1] = C;
				V[cvor][sizeOfArray[cvor]-1].pos = C.pos;
				V[cvor][sizeOfArray[cvor]-1].znak = C.znak;
				
				
				cvor=C.pos;
			}
			break;
		}
	}
}
unsigned short giveMeCode(char *S)
{
	if(find(S))
	{
		int len=strlen(S);
		int cvor=0;
		int i,j;
		for(i=0;i<len;++i)
		{
			int find=0;
			for(j=0;j<sizeOfArray[cvor];++j)
			{
				if(V[cvor][j].znak==S[i])
				{
					find=1;
					cvor=V[cvor][j].pos;
					break;
				}
			}
		}
		return cvor;
	}
	else 
	{
		printf("NEEEEEEEEEEEE!!!\n");
	}
}

void solve(FILE *inputFile, FILE *outputFile)
{
	char oktet;
	
	char word[45654];
	word[0] = 0;
	while(fread(&oktet,sizeof(char),1,inputFile)==1)
	{
		
		char newSimbol=oktet;
		char tempString[45654];
		strcpy(tempString,word);
		
		strcat(tempString,&newSimbol);
	
		//string tempString=word+newSimbol;
		
		if(find(tempString))
			//word=word+newSimbol;
			strcat(word,&newSimbol);
		else 
		{
			//ispis koda
			if(strlen(word)>0)
			{
				if(!find(word))add(word);
				unsigned short kod=giveMeCode(word);
				fwrite(&kod,sizeof(unsigned short),1,outputFile);
				//cout<<kod<<"->>"<<word<<endl;
				char ti[4567];
				strcpy(ti,word);
				strcat(ti,&newSimbol);
				//word+newSimbol
				add(ti);
			}
			//word=newSimbol;
			strcpy(word,&newSimbol);
			//cout<<"Nova radna rijec "<<word<<endl;
		}
	}
	unsigned short kod=giveMeCode(word);
	//cout<<kod<<" "<<word<<endl;
	fwrite(&kod,sizeof(unsigned short),1,outputFile);
}
int main(int argc, char *argv[])
{
	FILE *inputFile=fopen(argv[1],"rb");
	FILE *outputFile=fopen(argv[2],"wb");
	
	solve(inputFile,outputFile);
	
	
	fclose(inputFile);
	fclose(outputFile);
	return 0;
}

