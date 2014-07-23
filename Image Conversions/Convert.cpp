//	Main .cpp file for this project
//	Conversion functions to be called here

#include "DataStructs.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
using namespace std; 


//typedef	struct	{
//	DWORD		Signature;		// = (int('D')<<24)+(int('R')<<16)+(int('I')<<8)+'.' ;
//	DWORD		Type;		// TYPE_WC_IMAGE_DATA
//	DWORD		Size;
//	DWORD		Images;
//	DWORD		ImagesSize;
//	char		Version[40];
//
//	// added Sept 28, 2002
//
//	DRI_SETTINGS	Settings;
//
//}	WC_IMAGE_DATA_HEADER_2;

int main()
{
	/*
		Create Input stream in binary mode
		Get the number of bytes of the image
	*/	
	ifstream In("C:\\Program Files (x86)\\DataRay\\Test_Perfect_Gaussian_2mm.wcf", ios::binary);
	In.seekg(0, ios::end);
	int i_ImageSize = In.tellg();	
	//	Creates buffer that will hold data
	char *Buffer = new char[i_ImageSize];		
	In.seekg(0, ios::beg);
	In.read(Buffer, i_ImageSize);	
	In.close();
	/*	
		Creates new folder: ConvertedImages
		Then stores the images within the new folder
	*/
	CreateDirectory("C:\\Users\\vramirez\\Documents\\Converted Images", NULL);				
	//	Folder that will hold the .bmp file
	FILE* NewImage = fopen("C:\\Users\\vramirez\\Documents\\Converted Images\\Image.bmp", "w");		
	if (!NewImage)
	{
		cout << "Failed to create the new document!" << endl; 
	}
	/*	
		Create the OutPut stream and open it
		Then write everthing in the Buffer on this file
		As a .bmp image
	*/
	ofstream OutPut;
	//OutPut.open("C:\\Users\\vramirez\\Documents\\Converted Images\\Image.doc");
	//if (!OutPut.is_open())
	//{
	//	cout << "Could not open OutPut file." << endl; 
	//}
	//else if (OutPut.is_open())
	//{
	//	for (size_t i = 0; i < (i_ImageSize + 1); i++)
	//	{
	//		OutPut << Buffer[i];
	//	}
	//}
	OutPut.open("C:\\Users\\vramirez\\Documents\\Converted Images\\Image.bmp");
	if (!OutPut.is_open())
	{
		cout << "Could not open bmp image file!" << endl;
	}
	else if (OutPut.is_open())
	{
		for (size_t v = 0; v < (i_ImageSize + 1); v++)
		{
			OutPut << Buffer[v];
		}
	}
	OutPut.close(); 

	system("pause");
	return(0);
}