#ifndef BCSICAMERACTRLINTERFACE_H
#define BCSICAMERACTRLINTERFACE_H

#include "bcameractrlinterface.h"

class BCsiCameraCtrlInterFace : public BCameraCtrlInterFace
{
public:
    BCsiCameraCtrlInterFace();

public:
    BT_RET openCamera(void *_camera);
    BT_RET closeCamera(void *_camera);

    BT_RET captureData(void *_camera, unsigned char**_data, long long *_len);
    BT_RET openCameraStream(void *_camera);
    BT_RET closeCameraStream(void *_camera);

    BT_RET control (void *_camera, CameraCtrl_t &_ctrl);
};

#endif // BCSICAMERACTRLINTERFACE_H
