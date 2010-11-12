// HMapReader.cpp

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "HMapReader.hpp"

//#define ind(x, z, sizeofx) ((x) + ((z) * sizeofx)) 

using namespace std;


Hmap::Hmap(const char *Map)
:Data(0)
,height(0)
,width(0)
{
   string FileName(Map);
   if(FileName.find(".bmp", 0)!=string::npos)
   {  
   		cout << "ReadBMP()"<<endl;
        HMap_ReadBMP(Map);
   }
   else if (FileName.find(".raw", 0)!=string::npos)
   {
   		cout << "ReadRaw()"<<endl;
        HMap_ReadRaw(Map, 128 ); // @TODO: calculate the size
   }
    
}

Hmap::~Hmap()
{
    // correct?
    delete[] Data;    
}

Uint8 Hmap::HMap_ReadRaw(const char *FileName, int size=128)
{
   height=size;
   width=size;
   ifstream file;
   unsigned char c;
   Data = new(Uint8[size*size]);
   
   file.open(FileName,ios::binary);
   for (int z=0; z < size; z++) {
      for (int x=0; x < size; x++) {
         char tmp;
         file.get(tmp);
         c = (unsigned char)tmp;
         Data[x+z*size] = (short)c;
      }
   }
   file.close();
   return 1;
}


Uint8  Hmap::HMap_ReadBMP(const char *FileName)
{
    struct BMP_FileHeader FileHeader;
    struct BMP_InfoHeader InfoHeader;
    
    ifstream bmpFile(FileName, ios::binary);      
    ofstream bmplog( "ReadBMP.log", ios::out );
    
    bmplog << "<Reading " << FileName << ">\n";  
    bmplog << "--- Reading Header ---\n";
    //bmpFile.read( (char *) (&FileHeader), sizeof(BMP_FileHeader));
    bmpFile.read( (char *) (&(FileHeader.bfType)), sizeof(Uint16));
    bmpFile.read( (char *) (&(FileHeader.bfSize)), sizeof(Uint32));
    bmpFile.read( (char *) (&(FileHeader.bfReserved1)), sizeof(Uint16));
    bmpFile.read( (char *) (&(FileHeader.bfReserved2)), sizeof(Uint16));
    bmpFile.read( (char *) (&(FileHeader.bfOffBits)), sizeof(Uint32));
  
    bmplog << "bfType = " << FileHeader.bfType << "\n";
    bmplog << "bfSize = " << FileHeader.bfSize << "\n";
    bmplog << "bfReserved1 = " << FileHeader.bfReserved1 << "\n";
    bmplog << "bfReserved2 = " << FileHeader.bfReserved2 << "\n";
    bmplog << "bfOffBits = " << FileHeader.bfOffBits << "\n";

    if(FileHeader.bfType!=19778)
        return 0;
    if(FileHeader.bfReserved1!=0 || FileHeader.bfReserved2!=0)
        return 0;
    
    bmplog << "--- Reading Info ---\n";
    bmpFile.read( (char *) (&InfoHeader), sizeof(BMP_InfoHeader));
    bmplog << "biSize = " << InfoHeader.biSize << "\n";
    bmplog << "biWidth = " << InfoHeader.biWidth << "\n";
    bmplog << "biHeight = " << InfoHeader.biHeight << "\n";
    bmplog << "biPlanes = " << InfoHeader.biPlanes << "\n";
    bmplog << "biBitCount = " << InfoHeader.biBitCount << "\n";
    bmplog << "biCompression = " << InfoHeader.biCompression << "\n";
    bmplog << "biSizeImage = " << InfoHeader.biSizeImage << "\n";
    bmplog << "biXPelsPerMeter = " << InfoHeader.biXPelsPerMeter << "\n";
    bmplog << "biYPelsPerMeter = " << InfoHeader.biYPelsPerMeter << "\n";
    bmplog << "biClrUsed = " << InfoHeader.biClrUsed << "\n";
    bmplog << "biClrImportant = " << InfoHeader.biClrImportant << "\n";
    
    if(InfoHeader.biBitCount!=8)
        return 0;
        
    bmplog << "--- Reading Data ---\n";
    bmpFile.seekg(FileHeader.bfOffBits);
    
    height=InfoHeader.biHeight;
    width=InfoHeader.biWidth;
    
    Data = new(Uint8[width*height]);
    bmpFile.read( (char *) (Data), InfoHeader.biWidth*InfoHeader.biHeight);
    
    for(int num=0; num<height*width; num++)
    {
            int number=Data[num];
            bmplog << "Data["<<num<<"] = " << number << "\n";
    }
    bmplog << "--- Reading Finished! ---\n";  
    bmplog.close();
    bmpFile.close();
    return 1;
}
