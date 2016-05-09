#include "bcamerainfo.h"

#include <QDebug>

BCameraInfo::BCameraInfo()
{

}


BUsbCamerainfo::BUsbCamerainfo(unsigned int iWidth, unsigned int iHeight,
               unsigned int idProduct, unsigned int idVendor,
               QString fmt, VIDEO_TYPE _videoType)
{

    memset(&_camera, 0, sizeof(uVideoDevice));

    _camera.idProduct           = idProduct;
    _camera.idVendor            = idVendor;

    if (0 == fmt.compare ("jpg"))
        _camera.Dev.videoFmt    = MJPG_FMT;
    else
        _camera.Dev.videoFmt    = YUYV_FMT;

    _camera.Dev.videoWidth      = iWidth;
    _camera.Dev.videoHeight     = iHeight;
    _camera.Dev.videoType       = _videoType;
}

void *BUsbCamerainfo::cameraInfo (void)
{
    //qDebug()<<__func__<<"BUsbCamerainfo";
    return &_camera;
}

uVideoDevice * BUsbCamerainfo::getCameraDevice_u()
{
    return (uVideoDevice *)cameraInfo ();
}


VideoDevice  * BUsbCamerainfo::getCameraDevice ()
{
    return (VideoDevice*)&((uVideoDevice *)cameraInfo ())->Dev;
}

int BUsbCamerainfo::_imageWidth()
{
    VideoDevice * camDev = getCameraDevice ();
    if (camDev){
        return camDev->videoWidth;
    }

    return 0;
}


int BUsbCamerainfo::_imageHeight()
{
    VideoDevice * camDev = getCameraDevice ();
    if (camDev){
        return camDev->videoHeight;
    }

    return 0;
}

//---------------------------------

BCsiCameraInfo::BCsiCameraInfo(QString _devName, unsigned int iWidth, unsigned int iHeight,
               QString fmt/*"jpg" or "yuv"*/, VIDEO_TYPE _videoType)
{

    memset(&_camera, 0, sizeof(VideoDevice));

    memcpy(_camera.devPath, _devName.toStdString ().c_str (),
           sizeof(_camera.devPath));

    if (0 == fmt.compare ("ipg"))
        _camera.videoFmt   = MJPG_FMT;
    else
        _camera.videoFmt   = YUYV_FMT;

    _camera.videoWidth     = iWidth;
    _camera.videoHeight    = iHeight;
    _camera.videoType      = _videoType;
}


void *BCsiCameraInfo::cameraInfo (void)
{
    return &_camera;
}


VideoDevice  * BCsiCameraInfo::getCameraDevice ()
{
    return (VideoDevice *)cameraInfo ();
}


int BCsiCameraInfo::_imageWidth()
{
    VideoDevice * camDev = getCameraDevice ();
    if (camDev){
        return camDev->videoWidth;
    }

    return 0;
}


int BCsiCameraInfo::_imageHeight()
{
    VideoDevice * camDev = getCameraDevice ();
    if (camDev){
        return camDev->videoHeight;
    }

    return 0;
}
