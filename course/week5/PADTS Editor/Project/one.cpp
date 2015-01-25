
#ifndef BMP_H
#define BMP_H
#include <stdio.h>
#include <iostream>
#include <math.h>

#define BYTE unsigned char //8 bits
#define WORD unsigned short //16 bits
#define DWORD unsigned int //32 bits

#define CLAMP(x) (((x) > (255)) ? (255) : (((x) < (0)) ? (0) : (x)))
#define RGB2GRAY(r,g,b) (BYTE)( (b)*0.3 + (g)*0.59 + (r)*0.11 )

typedef struct
{
	WORD   identifier;
	DWORD  size;
	DWORD  reserved;
	DWORD  bitoffset;
	DWORD  headerSize;
	DWORD  width;
	DWORD  height;
	WORD   planes;
	WORD   bitsPerPixel;
	DWORD  compression;
	DWORD  imageSize;
	DWORD  hResolution;
	DWORD  vResolution;
	DWORD  numberOfColours;
	DWORD  importantColours;
}BMPHeader;

typedef struct
{
	BYTE b;
	BYTE g;
	BYTE r;
	BYTE a;
}Color;


class BMP
{
private:	
	BMPHeader header;
	Color *pPalette;        // Colour palette
	BYTE *pImageData;       // Pixels
	bool isImageLoaded;     // Flag up if image loaded

public:
	BMP(const char *name);
	void printHeader(void);
	void save(const char *name);
	void brightness(const int u);
	void negative(void);
	void red(void);
	void RGBtoGRAY(void);
	~BMP(void);
};
#endif


//#pragma warning(disable:4996)
BMP::BMP(const char *name)
{
	if (!name) return; //returns if name was not given
	
	// Initialization
	isImageLoaded = false;
	pPalette = NULL;
	pImageData = NULL;
	FILE* pFile = fopen(name,"rb"); //opens file for input operations (r) as binary (b)
	//fopen_s(pFile, name, "rb"); 

	//Read the file headers
	fread(&header.identifier,1,sizeof(WORD),pFile);
	fread(&header.size, 1, sizeof(DWORD), pFile);
	fread(&header.reserved, 1, sizeof(DWORD), pFile);
	fread(&header.bitoffset, 1, sizeof(DWORD), pFile);
	fread(&header.headerSize, 1, sizeof(DWORD), pFile);
	fread(&header.width, 1, sizeof(DWORD), pFile);
	fread(&header.height, 1, sizeof(DWORD), pFile);
	fread(&header.planes, 1, sizeof(WORD), pFile);
	fread(&header.bitsPerPixel, 1, sizeof(WORD), pFile);
	fread(&header.compression, 1, sizeof(DWORD), pFile);
	fread(&header.imageSize, 1, sizeof(DWORD), pFile);
	fread(&header.hResolution, 1, sizeof(DWORD), pFile);
	fread(&header.vResolution, 1, sizeof(DWORD), pFile);
	fread(&header.numberOfColours, 1, sizeof(DWORD), pFile);
	fread(&header.importantColours, 1, sizeof(DWORD), pFile);

	//Verifies if image is 8-bit bitmap
	if (header.bitsPerPixel != 8)
	{
		fclose(pFile); //closes file and clears buffer
		printf("File is not 8-bit BMP\n");
		getchar();
		return;
	}

	//Get number of colours
	if (header.numberOfColours == 0)
		header.numberOfColours = (int)pow(2.0,1.0*header.bitsPerPixel);

	//Colour palette
	pPalette = new Color[header.numberOfColours]; //Assigns necessary memory for colour palette
	fread(pPalette, header.numberOfColours, sizeof(Color), pFile);

	//Array for the pixels
	pImageData = new BYTE[header.width * header.height];

	fseek(pFile, header.bitoffset, SEEK_SET); //sets pointer to beginning of data
	fread(pImageData, 1, header.width * header.height, pFile);  

	isImageLoaded = true;
	fclose(pFile);
}

void BMP::printHeader(void)
{
	if (isImageLoaded)
	{
		printf("    + Identifier: \t\t| Ox%X\n", header.identifier);		
		printf("    + File size: \t\t| %d bytes\n", header.size);
		printf("    + Data offset: \t\t| %d bytes\n", header.bitoffset);
		printf("    + Header size: \t\t| %d bytes\n", header.headerSize);
		printf("    + Width: \t\t\t| %dpx\n", header.width);
		printf("    + Height: \t\t\t| %dpx\n", header.height);
		printf("    + Planes: \t\t\t| %d\n", header.planes);
		printf("    + Bits per pixel: \t\t| %d-bits\n", header.bitsPerPixel);
		printf("    + Compression: \t\t| %d\n", header.compression);
		printf("    + Image size: \t\t| %d bytes\n", header.imageSize);
		printf("    + Horizontal resolution: \t| %d\n", header.hResolution);
		printf("    + Vertical resolution: \t| %d\n", header.vResolution);
		printf("    + Number of colours: \t| %d\n", header.numberOfColours);
		printf("    + Important colours: \t| %d\n", header.importantColours);
	}
	else
	{
		printf("No image loaded\n");
	}
}

void BMP::save(const char *name)
{
	if (isImageLoaded)
	{
		if (!name) return;

		FILE *pFile = fopen(name, "wb"); //Creates empty file for output operations (w) as binary (b)

		fwrite(&header.identifier, sizeof(header.identifier), 1, pFile);		
		fwrite(&header.size, sizeof(header.size), 1, pFile);
		fwrite(&header.reserved, sizeof(header.reserved), 1, pFile);
		fwrite(&header.bitoffset, sizeof(header.bitoffset), 1, pFile);
		fwrite(&header.headerSize, sizeof(header.headerSize), 1, pFile);
		fwrite(&header.width, sizeof(header.width), 1, pFile);
		fwrite(&header.height, sizeof(header.height), 1, pFile);
		fwrite(&header.planes, sizeof(header.planes), 1, pFile);
		fwrite(&header.bitsPerPixel, sizeof(header.bitsPerPixel), 1, pFile);
		fwrite(&header.compression, sizeof(header.compression), 1, pFile);
		fwrite(&header.imageSize, sizeof(header.imageSize), 1, pFile);
		fwrite(&header.hResolution, sizeof(header.hResolution), 1, pFile);
		fwrite(&header.vResolution, sizeof(header.vResolution), 1, pFile);
		fwrite(&header.numberOfColours, sizeof(header.numberOfColours), 1, pFile);
		fwrite(&header.importantColours, sizeof(header.importantColours), 1, pFile);
		fwrite(pPalette, sizeof(Color), header.numberOfColours, pFile);

		fseek(pFile, header.bitoffset, SEEK_SET);		
		fwrite(pImageData, 1, header.width * header.height, pFile);

		fclose(pFile);
	}
}

void BMP::brightness(const int u){
if(u ==0 && !isImageLoaded) return;
	
	for(int i=0; i<(int)header.numberOfColours; i++){
		pPalette[i].r = CLAMP(pPalette[i].r + u);
		pPalette[i].g = CLAMP(pPalette[i].g + u);
    		pPalette[i].b = CLAMP(pPalette[i].b + u);
	}
}

void BMP::negative(void) {
if (!isImageLoaded) return;

	int n = (int)header.numberOfColours -1;

	for ( int i = 0; i < (int)header.numberOfColours; i++){

		pPalette[i].r = (n - (int)pPalette[i].r);
		pPalette[i].g = (n - (int)pPalette[i].g);
		pPalette[i].b = (n - (int)pPalette[i].b);
	}
}

void BMP::red(void){
if (!isImageLoaded) return;

		for(int i=0; i< (int) header.numberOfColours; i++){
			pPalette[i].g = 0;
			pPalette[i].b = 0;
		}
}



void BMP::RGBtoGRAY(void)
{
	if(!isImageLoaded) return;

	BYTE intensity = 0;
	for(int i = 0; i < (int)header.numberOfColours; i++){
		intensity = RGB2GRAY(pPalette[i].r, pPalette[i].g, pPalette[i].b);
		pPalette[i].r = intensity;
		pPalette[i].g = intensity;
		pPalette[i].b = intensity;
	}
}

BMP::~BMP(void){
	if (pImageData != NULL) delete[] pImageData;
	if (pPalette != NULL) delete[] pPalette;
}



int main(int argc, char** argv)
{
	BMP bmp("lenna.bmp");
	bmp.printHeader();
	//bmp.save("lennaCopy.bmp");
	bmp.brightness(100);
	bmp.save("brighter.bmp");
	bmp.brightness(-100);
	bmp.save("darker.bmp");
	bmp.negative();
	bmp.save("negative.bmp");
	bmp.red();
	bmp.save("redish.bmp");
	bmp.RGBtoGRAY();
	bmp.save("Gray.bmp");	

	getchar();
	return 0;
}
