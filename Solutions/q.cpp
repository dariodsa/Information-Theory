#include <stdio.h>
int main(int argc, char *argv[])
{
	FILE *pfile = fopen(argv[1],"r");
	FILE *pfile2 = fopen("out1.txt","w");
	char t;
	while(fscanf(pfile,"%c",&t))
	{
		fprintf(pfile2,"%c,",t);
	}
	
}
