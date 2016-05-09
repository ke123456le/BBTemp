#ifndef BFACEIDENTCAMERA_H
#define BFACEIDENTCAMERA_H

//#include "bcamera.h"
#include "busbcamera.h"
#include "extend/include/uVideo.h"

class BFaceIdentCamera : public BUsbCamera
{

public:
    BFaceIdentCamera();
    ~BFaceIdentCamera();

    int imageDataSize();

private:
    unsigned char *dataBuffer;


private:
    void func();
};

#endif // BFACEIDENTCAMERA_H
