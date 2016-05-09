#ifndef BCSICAMERACTRLINTERFACE_H
#define BCSICAMERACTRLINTERFACE_H

//#include "bcameractrlinterface.h"
#include "bcamera.h"
#include "extend/include/uVideo.h"

//class BCsiCameraCtrlInterFace : public BCameraCtrlInterFace
class BCsiCamera : public BCamera
{
    Q_OBJECT
public:
    BCsiCamera(QString _devName, unsigned int iWidth, unsigned int iHeight,
               QString fmt/*"jpg" or "yuv"*/, VIDEO_TYPE _videoType);

    //BT_RET setCamera(BCameraInfo *_camera);

    BT_RET openCamera();
    BT_RET closeCamera();

    BT_RET captureData(unsigned char *_data, int *_len);
    BT_RET openCameraStream();
    BT_RET closeCameraStream();

    BT_RET control (CameraCtrl_t &_ctrl);

    int imageWidth();
    int imageHeight();

    void autoControlExp(unsigned char *_data, int _len, int *expValue);
    int initCameraExposure(int mExpVal);
private:
    BCsiCameraInfo *_cameraInfo;
};

#endif // BCSICAMERACTRLINTERFACE_H
