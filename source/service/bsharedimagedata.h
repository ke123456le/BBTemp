#ifndef BSHAREDIMAGEDATA_H
#define BSHAREDIMAGEDATA_H
#include <QMutex>

#include "../errorcode.h"

struct IdentImageInfo{
    unsigned char *imageData;
    int imageWidth;
    int imageHeight;
    int lenData;
    IdentImageInfo(unsigned char *_data=NULL, int _width=0,
                   int _height=0, int _len=0)
    {
        imageData   = _data;
        imageWidth  = _width;
        imageHeight = _height;
        lenData     = _len;
    }
};


class BSharedImageData
{
public:
    BSharedImageData(int _dataSize);
    ~BSharedImageData();

    BT_RET updateImageData(const unsigned char *_data, int _size,
                            const int _width, const int _height);
    IdentImageInfo * getImageData();

private:
    BT_RET checkBuf(const unsigned char *_data, const int _size);

private:
    IdentImageInfo image;
    IdentImageInfo tmpImage;
    bool isUpdate;
    QMutex _dataLock;
};

#endif // BSHAREDIMAGEDATA_H
