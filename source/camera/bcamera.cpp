#include "bcamera.h"

BCamera::BCamera(): _cameraCtrl(NULL),func(NULL),
    jpgDeCode(NULL),cameraState(NO_CAMERA),camera(NULL)
{

}

BT_RET BCamera::setDeCode(DeCode *_decode)
{
    if (_decode)
        jpgDeCode = _decode;
    else
        return __BT_DATA_INVILD;

    return __BT_SUCC;
}

BT_RET BCamera::setCameraCtrl(BCameraCtrlInterFace *_ctrl)
{
    if (_ctrl)
        _cameraCtrl = _ctrl;
    else
        return __BT_DATA_INVILD;

    return __BT_SUCC;
}


BT_RET BCamera::setCameraFunc(proFunc _func)
{
    if (_func)
        func = _func;
    else
        return __BT_DATA_INVILD;

    return __BT_SUCC;
}


BT_RET BCamera::updateCameraState(CameraState _state)
{
    cameraState = _state;

    return __BT_SUCC;
}

BT_RET BCamera::setCamera (void *_camera)
{
    if (_camera)
        camera = _camera;
    else
        return __BT_DATA_INVILD;

    return __BT_SUCC;
}


void BCamera::run()
{
    if (func && _cameraCtrl){
        if (NO_CAMERA == cameraState){
            _cameraCtrl->openCamera (camera);
        }

        if (CAMERA_OPEN == cameraState){
            _cameraCtrl->openCameraStream (camera);
        }

        if (CAMERA_STREAM_ON == cameraState){
            func();
        }

        if (CAMERA_STREAM_ON == cameraState){
            _cameraCtrl->closeCameraStream (camera);
        }
    }
}

