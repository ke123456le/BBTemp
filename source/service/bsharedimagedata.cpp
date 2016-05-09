#include <QString>
#include "bsharedimagedata.h"
#include <QThread>

#include <QDebug>

BSharedImageData::BSharedImageData(int _dataSize) : image(NULL,0,0,0), tmpImage(NULL,0,0,0),
    isUpdate(false)
{
    if (!image.imageData){
        image.imageData = new unsigned char[_dataSize];
        if (image.imageData)
            image.lenData = _dataSize;
    }

    if (!tmpImage.imageData){
        tmpImage.imageData = new unsigned char[_dataSize];
    }
}

BSharedImageData::~BSharedImageData()
{
    if (image.imageData){
        delete[] image.imageData;
        image.imageData = NULL;
    }

    if (tmpImage.imageData){
        delete[] tmpImage.imageData;
        tmpImage.imageData = NULL;
    }
}


BT_RET BSharedImageData::checkBuf(const unsigned char *_data, int _size)
{
    if (!_data || _size<=0)
        return __BT_DATA_INVILD;

    if (!image.imageData){
        isUpdate = false;
        image.imageData = new unsigned char[_size];
        if (image.imageData){
            image.lenData = _size;
        }else
            return __BT_ALLOC_BUF_FAIL;
    }

    if (image.lenData < _size){
        isUpdate = false;
        if (image.imageData){
            delete[] image.imageData;
            image.imageData = NULL;
        }

        if (tmpImage.imageData){
            delete[] tmpImage.imageData;
            tmpImage.imageData = NULL;
        }
        image.imageData = new unsigned char[_size];
        tmpImage.imageData = new unsigned char[_size];
        if (image.imageData && tmpImage.imageData)
            image.lenData = _size;
        else
            return __BT_ALLOC_BUF_FAIL;
    }

    return __BT_SUCC;
}

BT_RET BSharedImageData::updateImageData(const unsigned char *_data, const int _size,
                                          const int _width, const int _height)
{
    if (!_data || _size<=0 || _width<=0 || _height<=0)
        return __BT_DATA_INVILD;

    _dataLock.lock ();
    BT_RET retCode = checkBuf(_data, _size);

    if (__BT_SUCC != retCode){
        _dataLock.unlock ();
        return retCode;
    }

    memcpy(image.imageData, _data, _size);
    image.imageWidth    = _width;
    image.imageHeight   = _height;

    isUpdate = true;

    _dataLock.unlock ();
}


IdentImageInfo * BSharedImageData::getImageData()
{
    IdentImageInfo *retImage = NULL;

    int timeOut = 30;

    while (timeOut--){
        if (!_dataLock.tryLock (10))
            continue;

        if (image.imageData && tmpImage.imageData){
            if (isUpdate){
                //qDebug()<<__func__<<"isUpdate:"<<isUpdate;
                if (1){
                memcpy(tmpImage.imageData, image.imageData, image.lenData);
                tmpImage.imageWidth     = image.imageWidth;
                tmpImage.imageHeight    = image.imageHeight;
                tmpImage.lenData        = image.lenData;

                retImage = &tmpImage;
                }
                isUpdate = false;
                _dataLock.unlock ();
                break;
            }else{
                QThread::msleep (5);
            }
        }else{
            retImage = NULL;
            _dataLock.unlock ();
            break;
        }


        //QThread::msleep (10);

        _dataLock.unlock ();
    }

    return retImage;
}

