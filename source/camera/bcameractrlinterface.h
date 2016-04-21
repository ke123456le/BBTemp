#ifndef BCAMERACTRLINTERFACE_H
#define BCAMERACTRLINTERFACE_H

#include "../errorcode.h"

class BCameraCtrlInterFace
{
public:
    BCameraCtrlInterFace();

    virtual BT_RET openCamera(void *_camera)=0;
    virtual BT_RET closeCamera(void *_camera)=0;

    virtual BT_RET captureData(void *_camera, unsigned char**_data, long long *_len)=0;
    virtual BT_RET openCameraStream(void *_camera)=0;
    virtual BT_RET closeCameraStream(void *_camera)=0;

    /**控制**/
    enum CAMERA_CTRL_TYPE
    {
        CTRL_EXPOSURE=0,
        CTRL_WHITE_BALANCE,
        CTRL_FOCUS
    };

    enum CAMERA_CTRL_DIRECTION{
        CTRL_IN = 0,
        CTRL_OUT
    };

    struct CameraCtrl_t{
        CAMERA_CTRL_TYPE _ctrlType;
        CAMERA_CTRL_DIRECTION _ctrlDirection;
    };
    virtual BT_RET control(void *_camera, CameraCtrl_t & _ctrl)=0;
};

#endif // BCAMERACTRLINTERFACE_H
