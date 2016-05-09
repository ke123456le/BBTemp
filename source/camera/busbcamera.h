#ifndef BUSBCAMERACTRLINTERFACE_H
#define BUSBCAMERACTRLINTERFACE_H


//#include "bcameractrlinterface.h"
#include "bcamera.h"
#include "extend/include/uVideo.h"

//class BUsbCameraCtrlInterFace : public BCameraCtrlInterFace
class BUsbCamera : public BCamera
{
    Q_OBJECT
public:
    BUsbCamera(unsigned int iWidth, unsigned int iHeight,
               unsigned int idProduct, unsigned int idVendor,
               QString fmt, VIDEO_TYPE _videoType);
    ~BUsbCamera();

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
    BUsbCamerainfo *_cameraInfo;
};

#endif // BUSBCAMERACTRLINTERFACE_H
