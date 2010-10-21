// HMapReader.hpp

#ifndef __HMAPREADER_HPP
#define __HMAPREADER_HPP
#include <SDL/SDL.h>

struct BMP_FileHeader {
    Uint16 bfType;
    Uint32 bfSize;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bfOffBits;
};

struct BMP_InfoHeader {
    Uint32 biSize;
    Sint32 biWidth;
    Sint32 biHeight;
    Uint16 biPlanes;
    Uint16 biBitCount;
    Uint32 biCompression;
    Uint32 biSizeImage;
    Sint32 biXPelsPerMeter;
    Sint32 biYPelsPerMeter;
    Uint32 biClrUsed;
    Uint32 biClrImportant;
};

class Hmap
{
public:
    
    Hmap(const char *Map);
    ~Hmap();
    float getY();
    
    Uint8 *Data;
    Uint16 height;
    Uint16 width;
private:
    
    Uint8 HMap_ReadRaw(const char *FileName, int size);
    Uint8 HMap_ReadBMP(const char *FileName);
};










#endif // __HMAPREADER_HPP
