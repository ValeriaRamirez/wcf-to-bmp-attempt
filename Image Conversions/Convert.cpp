#include "DataStructs.h"
#include <iostream>
#include <fstream>
#include <Windows.h> 
#include <istream>
#include <cstdio>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	//	Bitmap headers
	BITMAPFILEHEADER FileBMP;
	BITMAPINFOHEADER InfoBMP;

	//	Header file initializations
	WC_IMAGE_DATA_HEADER_2	FileWCF;
	WC_IMAGE_DATA	DataWCF;

	//	Variables to be used later on
	int i_WCF_Size;
	unsigned short Data;
	unsigned int NewData; 
	int BMPImageSize; 
	int Row;
	int Counter;
	unsigned char Palette[16384][3];
	unsigned char Red = 0;
	unsigned char Green = 0;
	unsigned char Blue = 0;

	std::ifstream  Rgb("C:\\Users\\vramirez\\Documents\\Palette.csv");
	std::string Line;
	Row = 0;
	//	Takes from RGB and stores into Line
	while (std::getline(Rgb, Line))
	{
		Counter = -1;
		std::stringstream  lineStream(Line);
		std::string        cell;		//	RGB
		//	Takes from lineStream and stores in cell until ',' is found
		while (std::getline(lineStream, cell, ','))
		{
				//	atoi() converts cell from cstring to an integer (value)
				unsigned char value = atoi(cell.c_str());
				Counter++;
				if (value)
				{
					value = value;
					// You have a cell!!!!
				}
				if (Counter == 0)
				{
					Palette[Row][0] = value;
				}
				if (Counter == 1)
				{
					Palette[Row][1] = value;
				}
				if (Counter == 2)
				{
					Palette[Row][2] = value;
				}
		}
		Row++;
	}
	Rgb.close(); 

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
		FILE* NewBMPImage = fopen("C:\\Users\\vramirez\\Documents\\ConvertedImage\\Image.BMP", "w");
		if (!NewBMPImage)
		{
			cout << "Failed to create the new BMP file!" << endl;
		}
		//	Create the ofstream
		ofstream OutPut;
		OutPut.open("C:\\Users\\vramirez\\Documents\\ConvertedImage\\Image.BMP");
		//	Find the size of the entire image
		fseek(F_WCF, 0, SEEK_SET);
		fseek(F_WCF, 0, SEEK_END);
		i_WCF_Size = ftell(F_WCF);
		fseek(F_WCF, 0, SEEK_SET);

		//		void* Data = malloc(1048576 * 2);
		//


		//	Read and write the header files
		if (!OutPut.is_open())
		{
			cout << "Failed to open the BMP file. Cannot begin writing." << endl;
		}
		else if (OutPut.is_open())
		{
			fread(&FileWCF, sizeof(FileWCF), 1, F_WCF);
			fread(&DataWCF, sizeof(DataWCF) - 1, 1, F_WCF);

			BMPImageSize = (DataWCF.Height * DataWCF.Width * 3); 

			//	Bitmap File Header
			FileBMP.bfType = 19778;
			FileBMP.bfSize = (sizeof(FileBMP) + sizeof(InfoBMP) + BMPImageSize);
			FileBMP.bfReserved1 = 0;
			FileBMP.bfReserved2 = 0;
			FileBMP.bfOffBits = (sizeof(FileBMP) +sizeof(InfoBMP));

			OutPut.write((char*)&FileBMP, sizeof(FileBMP));

			//	Bitmap Info Header 
			InfoBMP.biSize = sizeof(InfoBMP);
			InfoBMP.biWidth = DataWCF.Width;
			InfoBMP.biHeight = DataWCF.Height;
			InfoBMP.biPlanes = 1;
			InfoBMP.biBitCount = 24;
			InfoBMP.biCompression = BI_RGB;
			InfoBMP.biSizeImage = 0;
			InfoBMP.biXPelsPerMeter = 0;
			InfoBMP.biYPelsPerMeter = 0;
			InfoBMP.biClrUsed = 0;
			InfoBMP.biClrImportant = 0;

			//OutPut.write((char*)&InfoBMP, sizeof(InfoBMP));
			//char Fill = 0;
			//OutPut.write((char*)&Fill, 4);
			////		fread(&Data, 1, 1, F_WCF);
			//unsigned char Pixel[3];
			//for (WORD Y = 0; Y < (DataWCF.Height); Y++)
			//{
			//	for (WORD X = 0; X < (DataWCF.Width); X++)
			//	{
			//		fread(&Data, 2, 1, F_WCF);
			//		if (Data > 16384)
			//		{
			//			Data = 16384;
			//		}
			//		NewData = (Data);
			//		Red = Palette[NewData][0];
			//		Green = Palette[NewData][1];
			//		Blue = Palette[NewData][2];
			//		Pixel[0] = Red;// = 0;
			//		Pixel[1] = Green;// = 255;
			//		Pixel[2] = Blue;// = 0;
			//		OutPut.write((char*)&Pixel, 3);					//	About 2,000 too big
			//		OutPut.write((char*)&Palette, 3);				//	Right Size, but all black	
			//		OutPut.write((char*)&Palette[NewData][Blue], 1);
			//		OutPut.write((char*)&Palette[NewData][Green], 1);	//	About 2,000 too big
			//		OutPut.write((char*)&Palette[NewData][Red], 1);
			//		OutPut.write((char*)&Palette[NewData][0], 3);	//	About 2,000 too big
			//		OutPut.write((char*)&Palette[NewData][2], 3);	//	About 200 bytes too big
			//		OutPut.write((char*)&Palette[NewData], 3);		//	About 2,000 too big
			//		OutPut.write((char*)&Blue, 1);	
			//		OutPut.write((char*)&Red, 1);					//	About 2,000 bytes too big 
			//		OutPut.write((char*)&Green, 1);
			//	}
			//}

			OutPut.write((char*)&InfoBMP, sizeof(InfoBMP));
			
			//	Write junk for 4 bytes 
			char Fill = 00000000; 
			OutPut.write((char*)&Fill, 4);  

			unsigned short *Data = new unsigned short[BMPImageSize];

	//		fread(Data, 10, 1, F_WCF); 
			fread(Data, (BMPImageSize), 1, F_WCF);
			unsigned char Pixel[3];
 			for (WORD Y = 0; Y < (InfoBMP.biHeight); Y++)
			{
				for (WORD X =0; X < (InfoBMP.biWidth); X++)
				{
	
					if (Data[Y * InfoBMP.biWidth + (X)] > 16384)
					{
						Data[Y * InfoBMP.biWidth + (X)] = 16384;
					}

					NewData = ((Data[Y * InfoBMP.biWidth + (X)]) / 2);

					Red = Palette[NewData][0];
					Green = Palette[NewData][1];
					Blue = Palette[NewData][2];

					Pixel[0] = Red;
					Pixel[1] = Green;
					Pixel[2] = Blue;

					OutPut.write((char*)&Pixel, 3);					//	About 2,000 too big
				}
			}
			OutPut.close();
			if (EOF)
			{
				cout << "End of file reached!" << endl; 
			}
			else if (!EOF)
			{
				cout << "Not reading entire file!" << endl; 
			}
		}
		fclose(NewBMPImage);
	}
	fclose(F_WCF); 

	//		free(Data);
	//

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
