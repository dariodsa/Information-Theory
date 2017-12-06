#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
struct Cvor
{
	char znak;
	int pos;
};
struct Trie
{
	int numCvor;
	vector<Cvor>V[9500];
	vector<Cvor>cvorovi;
	Trie()
	{
		numCvor=1;
		Cvor C;
		C.pos=0;
		
	}
	bool find(string S)
	{
		int len=S.length();
		int cvor=0;
		for(int i=0;i<len;++i)
		{
			bool find=false;
			for(int j=0;j<V[cvor].size();++j)
			{
				if(V[cvor][j].znak==S[i])
				{
					find=true;
					cvor=V[cvor][j].pos;
					break;
				}
			}
			if(!find)return false;
		}
		return true;
	}
	void add(string S)
	{
		int len=S.length();
		int cvor=0;
		for(int i=0;i<len;++i)
		{
			bool find=false;
			for(int j=0;j<V[cvor].size();++j)
			{
				if(V[cvor][j].znak==S[i])
				{
					find=true;
					cvor=V[cvor][j].pos;
					break;
				}
			}
			if(!find)
			{
				//pocni dodavati
				for(int k=i;k<len;++k)
				{
					Cvor C;
					C.pos=numCvor++;
					C.znak=S[k];
					V[cvor].push_back(C);
					cvor=C.pos;
				}
				break;
			}
		}
	}
	unsigned short giveMeCode(string S)
	{
		if(find(S))
		{
			int len=S.length();
			int cvor=0;
			for(int i=0;i<len;++i)
			{
				bool find=false;
				for(int j=0;j<V[cvor].size();++j)
				{
					if(V[cvor][j].znak==S[i])
					{
						find=true;
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
};
Trie T;
void solve(FILE *inputFile, FILE *outputFile)
{
	char oktet;
	
	string word="";
	while(fread(&oktet,sizeof(char),1,inputFile)==1)
	{
		char newSimbol=oktet;
		string tempString=word+newSimbol;
		if(T.find(tempString))
			word=word+newSimbol;
		else 
		{
			//ispis koda
			if(word.length()>0)
			{
				if(!T.find(word))T.add(word);
				unsigned short kod=T.giveMeCode(word);
				fwrite(&kod,sizeof(unsigned short),1,outputFile);
				//cout<<kod<<"->>"<<word<<endl;
				T.add(word+newSimbol);
			}
			word=newSimbol;
			//cout<<"Nova radna rijec "<<word<<endl;
		}
	}
	unsigned short kod=T.giveMeCode(word);
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

