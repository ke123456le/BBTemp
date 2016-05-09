#ifndef BIRISIDENTCAMERA_H
#define BIRISIDENTCAMERA_H

#include <QImage>

#include "extend/include/uVideo.h"
//#include "bcamera.h"
#include "busbcamera.h"
#include "bcamerainfo.h"
#include "bcamerawidget.h"

class BIrisIdentCamera : public BUsbCamera
{
public:
    BIrisIdentCamera();
    ~BIrisIdentCamera();

    int imageDataSize();

private:
    DeCode *jpegDeCode;

signals:

//public slots:

private:
    unsigned char *dataBuffer;


private:
    void func();
};

#endif // BIRISIDENTCAMERA_H
