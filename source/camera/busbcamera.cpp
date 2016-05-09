#include "busbcamera.h"
#include <QDebug>

#define _DEVICE(uDevice) (&((uVideoDevice *)uDevice->cameraInfo ())->Dev)

BUsbCamera::BUsbCamera(unsigned int iWidth, unsigned int iHeight,
                       unsigned int idProduct, unsigned int idVendor,
                       QString fmt, VIDEO_TYPE _videoType) : _cameraInfo(NULL)
{
    if (!_cameraInfo){
        _cameraInfo = new BUsbCamerainfo(iWidth, iHeight, idProduct, idVendor, fmt, _videoType);
    }else{
        delete _cameraInfo;
        _cameraInfo = new BUsbCamerainfo(iWidth, iHeight, idProduct, idVendor, fmt, _videoType);
    }
}

BUsbCamera::~BUsbCamera()
{
    if (_cameraInfo)
        delete _cameraInfo;
}

//BT_RET BUsbCamera::setCamera(BCameraInfo *_camera)
//{
//     _cameraInfo = _camera;
//}


BT_RET BUsbCamera::openCamera ()
{
    if (!_cameraInfo)
        return __BT_DATA_INVILD;

    int camRet = OpenUvcCamera(_cameraInfo->getCameraDevice_u ());

    return camRet?__BT_CAMERA_OPEN_FAIL:__BT_SUCC;
}




BT_RET BUsbCamera::closeCamera ()
{
    if (!_cameraInfo)
        return __BT_DATA_INVILD;

    CloseCamera(_cameraInfo->getCameraDevice ());

    return __BT_SUCC;
}


BT_RET BUsbCamera::captureData (unsigned char *_data, int *_len)
{
    if (!_cameraInfo || !_data || !_len)
        return __BT_DATA_INVILD;

    int retLen = GetImage (_cameraInfo->getCameraDevice (), (char *)_data);
    if (retLen <= 0)
        return __BT_CAMERA_CAPTURE_FAIL;

    *_len = retLen;

    return __BT_SUCC;
}

BT_RET BUsbCamera::openCameraStream ()
{
    if (!_cameraInfo)
        return __BT_DATA_INVILD;
    int ret = StartVideoStream(_cameraInfo->getCameraDevice ());
    if (ret)
        return __BT_CAMERA_STREAM_FAIL;

    return __BT_SUCC;
}

BT_RET BUsbCamera::closeCameraStream ()
{
    if (!_cameraInfo)
        return __BT_DATA_INVILD;
    int ret = StopVideoStream(_cameraInfo->getCameraDevice ());
    if (ret)
        return __BT_CAMERA_STREAM_FAIL;

    return __BT_SUCC;
}

BT_RET BUsbCamera::control (CameraCtrl_t &_ctrl)
{
    BT_RET errCode = __BT_SUCC;
    BT_RET ctrlRet;
    if (!_cameraInfo)
        return __BT_DATA_INVILD;

    switch (_ctrl._ctrlType){
    case CTRL_EXPOSURE:
        if (CTRL_IN == _ctrl._ctrlDirection){
            ctrlRet = getVideoExposure (_cameraInfo->getCameraDevice (), &_ctrl._ctrlValue);
        }else{
            ctrlRet = setVideoExposure(_cameraInfo->getCameraDevice (), _ctrl._ctrlValue);
        }
        errCode = (ctrlRet)?__BT_CAMERA_CTRL_EXPOSURE_FAIL:__BT_SUCC;
        break;
    case CTRL_WHITE_BALANCE:
    case CTRL_FOCUS:
    default:
        errCode = __BT_CAMERA_CTRL_NOT_SUPPORT;
        break;
    }

    return errCode;
}


int BUsbCamera::imageWidth()
{
    if (!_cameraInfo)
        return 0;
    return _cameraInfo->_imageWidth ();
}

int BUsbCamera::imageHeight()
{
    if (!_cameraInfo)
        return 0;

    return _cameraInfo->_imageHeight ();
}


void BUsbCamera::autoControlExp(unsigned char *_data, int _len, int *expValue)
{
    if (!_data || _len<=0 || expValue)
        return;

    checkAndUpdateExposure (_cameraInfo->getCameraDevice (), _data, _len, expValue);
}


int BUsbCamera::initCameraExposure(int mExpVal)
{
    return initExposure (_cameraInfo->getCameraDevice (), mExpVal);
}
