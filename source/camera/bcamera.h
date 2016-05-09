#ifndef BCAMERA_H
#define BCAMERA_H

#include <QString>
#include <QThread>
#include <QCameraViewfinder>

#include "../errorcode.h"
#include "bcamera_p.h"
#include "bcamerainfo.h"
#include "bcamerawidget.h"

#include "decode.h"




/****/
//typedef void (*proFunc)(void);
class BCamera : public QThread
{
    Q_OBJECT
public:
    BCamera();

    enum CameraState{NO_CAMERA=0, CAMERA_OPEN, CAMERA_STREAM_ON};

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
        int _ctrlValue;
    };


    BT_RET startCamera();
    BT_RET stopCamera();

    BT_RET setDeCode(DeCode *_decode);
    //BT_RET setCameraCtrl(BCameraCtrlInterFace *_ctrl);
    //BT_RET setCameraFunc(proFunc _func);

    BT_RET setBuffer(unsigned char *_buf);
    //virtual BT_RET setCamera(BCameraInfo *_camera)=0;

    BT_RET setShowWidget(BCameraWidget *_showWidget);

    virtual BT_RET openCamera()=0;
    virtual BT_RET closeCamera()=0;

    virtual BT_RET captureData(unsigned char *_data, int *_len)=0;
    virtual BT_RET openCameraStream()=0;
    virtual BT_RET closeCameraStream()=0;

    virtual BT_RET control (CameraCtrl_t &_ctrl)=0;

    //virtual void cameraInfo()=0;
    virtual int imageDataSize()=0;
    virtual int imageWidth()=0;
    virtual int imageHeight()=0;

    virtual void autoControlExp(unsigned char *_data, int _len, int *expValue)=0;
    virtual int initCameraExposure(int mExpVal)=0;

    void doYuvToRgb(unsigned char *rgbPtr, unsigned char *yuvPtr,
                    int iWidth, int iHight);

protected:
    void run ();
    virtual void func()=0;
    BT_RET updateCameraState(CameraState _state);

signals:
    void sendFailureCode(BT_RET code);
    void sendIamge(const QImage _image);
    void sendImageData(const unsigned char *_data, const int _size,
                       const int _width, const int _height);

public slots:
    void updateImage(const QImage _image);
    void releaseData();

public:
    BCameraWidget *showWidget;
    BT_RET procShowimage(QSize srcSize, unsigned char *srcData,
                       QSize dstSize, unsigned char *dstData);

private:
    //BCameraCtrlInterFace *_cameraCtrl;
    //proFunc func;
    DeCode *_jpgDeCode;
    CameraState cameraState;
    unsigned char *buffer;

    CYuvToRgb *yuvToRgb;
};

#endif // BCAMERA_H
