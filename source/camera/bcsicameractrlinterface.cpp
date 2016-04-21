#include "bcsicameractrlinterface.h"

BCsiCameraCtrlInterFace::BCsiCameraCtrlInterFace()
{

}


BT_RET BCsiCameraCtrlInterFace::openCamera (void *_camera)
{
    if (!_camera)
        return __BT_DATA_INVILD;
    int camRet = OpenCamera((VideoDevice *)_camera);

    return camRet?__BT_CAMERA_OPEN_FAIL:__BT_SUCC;
}

BT_RET BCsiCameraCtrlInterFace::closeCamera (void *_camera)
{
    if (!_camera)
        return __BT_DATA_INVILD;

    CloseCamera((VideoDevice *)_camera);

    return __BT_SUCC;
}

BT_RET BCsiCameraCtrlInterFace::captureData (void *_camera, unsigned char **_data,
                                      long long *_len)
{
    if (!camera || !_data || !_len)
        return __BT_DATA_INVILD;
    int retLen = GetImage ((VideoDevice *)_camera, _data);
}

BT_RET BCsiCameraCtrlInterFace::openCameraStream (void *_camera)
{

}

BT_RET BCsiCameraCtrlInterFace::closeCameraStream (void *_camera)
{

}

BT_RET BCsiCameraCtrlInterFace::control (void *_camera, CameraCtrl_t &_ctrl)
{

}


