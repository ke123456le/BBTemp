#include "birisidentcamera.h"





BIrisIdentCamera::BIrisIdentCamera(unsigned int iWidth, unsigned int iHeight,
                 unsigned int idProduct, unsigned int idVendor,
                 QString fmt)
{
    cameraDevice.idProduct          = idProduct;
    cameraDevice.idVendor           = idVendor;

    if (fmt.compare ("ipg"))
        cameraDevice.Dev.videoFmt   = MJPG_FMT;
    else
        cameraDevice.Dev.videoFmt   = YUYV_FMT;

    cameraDevice.Dev.videoWidth     = iWidth;
    cameraDevice.Dev.videoHeight    = iHeight;
    cameraDevice.Dev.videoType      = I_IRIS_VIDEO;

    setCamera (&cameraDevice);
}


BIrisIdentCamera::BIrisIdentCamera(QString _devName, unsigned int iWidth, unsigned int iHeight,
                 QString fmt/*"jpg" or "yuv"*/)
{
    memset(cameraDevice.Dev.devPath, 0, sizeof(cameraDevice.Dev.devPath));
    memcpy(cameraDevice.Dev.devPath, _devName.toStdString ().c_str (),
           sizeof(cameraDevice.Dev.devPath));

    if (0 == fmt.compare ("ipg"))
        cameraDevice.Dev.videoFmt   = MJPG_FMT;
    else
        cameraDevice.Dev.videoFmt   = YUYV_FMT;

    cameraDevice.Dev.videoWidth     = iWidth;
    cameraDevice.Dev.videoHeight    = iHeight;
    cameraDevice.Dev.videoType      = I_IRIS_VIDEO;

    setCamera (&cameraDevice);
}
