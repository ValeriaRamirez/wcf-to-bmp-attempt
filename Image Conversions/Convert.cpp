#include "DataStructs.h"
#include <iostream>
#include <fstream>
#include <Windows.h> 
#include <istream>
#include <cstdio>
#include <stdio.h>
using namespace std;

int main()
{
	//	Header file initializations
	WC_IMAGE_DATA_HEADER_2	FileWCF;
	WC_IMAGE_DATA	DataWCF;

	//	Variables to be used later on
	int i_WCF_Size;
	int i_Headers;
	int i_RestOfFile;
	int i_WidthBytes;

	//	Open .wcf image
	FILE* F_WCF = fopen("C:\\Program Files (x86)\\DataRay\\Test_Perfect_Gaussian_2mm.wcf", "r+b");
	if (!F_WCF)
	{
		cout << "Failed to open the WCF image!" << endl;
	}
	else if (F_WCF)
	{
		//	Folder that will be created in Documents
		CreateDirectory("C:\\Users\\vramirez\\Documents\\ConvertedImage", NULL);
		//	File created within the new folder
		FILE* NewBMPImage = fopen("C:\\Users\\vramirez\\Documents\\ConvertedImage\\Image.CSV", "w");
		if (!NewBMPImage)
		{
			cout << "Failed to create the new BMP file!" << endl;
		}
		//	Create the ofstream
		ofstream OutPut;
		OutPut.open("C:\\Users\\vramirez\\Documents\\ConvertedImage\\Image.CSV");
		//	Find the size of the entire image
		fseek(F_WCF, 0, SEEK_SET);
		fseek(F_WCF, 0, SEEK_END);
		i_WCF_Size = ftell(F_WCF);
		fseek(F_WCF, 0, SEEK_SET);

//		void* Data = malloc(1048576 * 2);

		i_RestOfFile = (i_WCF_Size - sizeof(WC_IMAGE_DATA_HEADER_2));
		int ConvertBytes = (i_RestOfFile * 2); 

		//	Read and write the header files
		if (!OutPut.is_open())
		{
			cout << "Failed to open the CSV file. Cannot begin writing." << endl;
		}
		else if (OutPut.is_open())
		{
			fread(&FileWCF, sizeof(FileWCF), 1, F_WCF);
	//		OutPut.write((char*)&FileWCF, sizeof(FileWCF));

			fread(&DataWCF, sizeof(DataWCF), 1, F_WCF);
	//		OutPut.write((char*)&DataWCF, sizeof(DataWCF));

//			fread((WORD*)Data, 1048576 * 2, 1, F_WCF);
//			OutPut.write((char*)Data, 1048576 * 2);
//			WORD ImageData;
			 
			WORD Data;

			//int read_size=fread(ImageDataBuffer, i_WCF_Size, 1, F_WCF);

			for (WORD Y = 1; Y < (DataWCF.Height + 1); Y++)
			{
				for (WORD X = 1; X < (DataWCF.Width + 1); X++)
				{
						//				fread(&ImageData, 2, 1, F_WCF);
						//				OutPut.write((char*)&ImageData, 2);
						//				OutPut << ",";
					fread(&Data, 2, 1, F_WCF);
					OutPut << (WORD)Data << "," ;

				}
				OutPut << endl; 
			}
		}
		OutPut.close();

//		free(Data);
//
	}

	/*
	 //	Total size of both headers put together
		i_Headers = (sizeof(WC_IMAGE_DATA_HEADER_2) + sizeof(WC_IMAGE_DATA));
		//	Size of entire file without headers
		i_RestOfFile = (i_WCF_Size - i_Headers);
		//	One byte for every pixel value 
		i_WidthBytes = (DataWCF.Width * 3);

		//	Buffer that will hold the rest of the file
		BYTE *WCFBuffer = new BYTE[(i_RestOfFile * 2)];
		//	Read the rest of the file all at once
		fread(WCFBuffer, (i_RestOfFile + 1), 1, F_WCF);

		//	Write the rest of the file into the new BMP file
		if (!OutPut.is_open())
		{
			cout << "Failed to open the new BMP file in order to write rest of file!" << endl;
		}
		else if (OutPut.is_open())
		{
			//	Array of the three values that make up each pixel (each value is one byte)
			unsigned char c_Pixel[3];
			//	Height component
			for (int H = 1; H < (DataWCF.Height + 1); H++)
			{
				//	Width component
				for (int W = 0; W < (i_WidthBytes + 1); W++)
				{
					//	Writing in groups of three instead of one by one
					if (((W + 1) % 3) == 0)
					{
						unsigned char Blue = (WCFBuffer[H*i_WidthBytes + (W)]);
						unsigned char Green = (WCFBuffer[H*i_WidthBytes + (W - 1)]);
						unsigned char Red = (WCFBuffer[H*i_WidthBytes + (W - 2)]);

						c_Pixel[0] = Red;
						c_Pixel[1] = Green;
						c_Pixel[2] = Blue;
						OutPut.write((char*)&c_Pixel, 3);
					}
				}
			}
		}
		OutPut.close();
	}*/

	system("pause");
	return(0);
}