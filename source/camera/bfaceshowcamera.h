#ifndef BFACESHOWCAMERA_H
#define BFACESHOWCAMERA_H

#include <QString>
//#include "bcamera.h"
#include "bcsicamera.h"
#include "extend/include/uVideo.h"
#include "bcamerainfo.h"

class BFaceShowCamera : public BCsiCamera
{
public:
    BFaceShowCamera();
    ~BFaceShowCamera();

    int imageDataSize();


private:
    unsigned char *dataBuffer;

private:
    void func();
};

#endif // BFACESHOWCAMERA_H
