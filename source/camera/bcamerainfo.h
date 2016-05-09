#ifndef BCAMERAINFO_H
#define BCAMERAINFO_H
#include <QObject>
#include <QString>
#include "extend/include/uVideo.h"

class BCameraInfo
{
public:
    BCameraInfo();
    virtual void *cameraInfo()=0;
    virtual int _imageWidth()=0;
    virtual int _imageHeight()=0;
};


class BUsbCamerainfo : public BCameraInfo
{
public:
    BUsbCamerainfo(unsigned int iWidth, unsigned int iHeight,
                   unsigned int idProduct, unsigned int idVendor,
                   QString fmt, VIDEO_TYPE _videoType);
    uVideoDevice * getCameraDevice_u();
    VideoDevice  * getCameraDevice ();
    int _imageWidth();
    int _imageHeight();

private:
    void * cameraInfo (void);

private:
    uVideoDevice _camera;
};

class BCsiCameraInfo : public BCameraInfo
{
public:
    BCsiCameraInfo(QString _devName, unsigned int iWidth, unsigned int iHeight,
                   QString fmt/*"jpg" or "yuv"*/, VIDEO_TYPE _videoType);
    VideoDevice  * getCameraDevice ();
    int _imageWidth();
    int _imageHeight();
private:
    void * cameraInfo (void);

private:
    VideoDevice _camera;
};

#endif // BCAMERAINFO_H
