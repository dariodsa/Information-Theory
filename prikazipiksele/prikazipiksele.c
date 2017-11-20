#include <stdio.h>

#include <cv.h>
#include <highgui.h>

/*
	
*/

int ucitaj(char* polje[], int n, const char* put)
{
	FILE* f;

	f = fopen(put, "rb");

	if(!f)
	{
		return 0;
	}

	if(n == fread(polje, sizeof(char), n, f))
	{
		fclose(f);

		return 1;
	}
	else
	{
		fclose(f);

		return 0;
	}
}

/*
	
*/

int main(int argc, char* argv[])
{
	int visina, sirina;
	IplImage* img;

	if(argc != 4)
	{
		printf("potrebno je predati tri parametra:\n");
		printf("\t- putanja do piksela\n");
		printf("\t- visina slike\n");
		printf("\t- sirina slike\n");
		
		printf("\n");
		printf("primjer: prikazipiksele.exe /putanja/do/piksela 480 640\n");

		return 0;
	}

	sscanf(argv[2], "%d", &visina);
	sscanf(argv[3], "%d", &sirina);

	img = cvCreateImage(cvSize(sirina, visina), IPL_DEPTH_8U, 1);

	img->widthStep = sirina; // hack

	if(!ucitaj(img->imageData, sirina*visina, argv[1]))
	{
		printf("neuspjesno ucitavanje datoteke:\n\t%s", argv[1]);
	}
	else
	{
		cvNamedWindow(argv[1], 1);
		cvShowImage(argv[1], img);
		cvWaitKey(0);
		cvDestroyWindow(argv[1]);
	}

	cvReleaseImage(&img);

	return 0;
}
