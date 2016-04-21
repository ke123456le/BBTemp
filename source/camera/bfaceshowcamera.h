#ifndef BFACESHOWCAMERA_H
#define BFACESHOWCAMERA_H

#include "bcamera.h"
#include "extend/include/uVideo.h"

class BFaceShowCamera : public BCamera
{
public:
    BFaceShowCamera(unsigned int iWidth, unsigned int iHeight,
                    unsigned int idProduct, unsigned int idVendor,
                    QString fmt);
    BFaceShowCamera(QString _devName, unsigned int iWidth, unsigned int iHeight,
                    QString fmt/*"jpg" or "yuv"*/);
private:
    uVideoDevice cameraDevice;
};

#endif // BFACESHOWCAMERA_H
