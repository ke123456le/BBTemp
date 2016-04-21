#ifndef BIRISIDENTCAMERA_H
#define BIRISIDENTCAMERA_H

#include "bcamera.h"
#include "extend/include/uVideo.h"

class BIrisIdentCamera : public BCamera
{
public:
    BIrisIdentCamera(unsigned int iWidth, unsigned int iHeight,
                     unsigned int idProduct, unsigned int idVendor,
                     QString fmt);
    BIrisIdentCamera(QString _devName, unsigned int iWidth, unsigned int iHeight,
                     QString fmt/*"jpg" or "yuv"*/);
private:
    uVideoDevice cameraDevice;
};

#endif // BIRISIDENTCAMERA_H
