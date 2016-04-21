#ifndef BFACEIDENTCAMERA_H
#define BFACEIDENTCAMERA_H

#include "bcamera.h"
#include "extend/include/uVideo.h"

class BFaceIdentCamera : public BCamera
{
public:
    BFaceIdentCamera(unsigned int iWidth, unsigned int iHeight,
                     unsigned int idProduct, unsigned int idVendor,
                     QString fmt);
    BFaceIdentCamera(QString _devName, unsigned int iWidth, unsigned int iHeight,
                     QString fmt/*"jpg" or "yuv"*/);
private:
    uVideoDevice cameraDevice;
};

#endif // BFACEIDENTCAMERA_H
