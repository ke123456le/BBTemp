#ifndef BCAMERA_H
#define BCAMERA_H

#include <QString>
#include <QThread>

#include "../errorcode.h"
#include "bcameractrlinterface.h"
#include "bcsicameractrlinterface.h"
#include "busbcameractrlinterface.h"

#include "decode.h"



/****/
typedef void (*proFunc)(void);
class BCamera : QThread
{
public:
    BCamera();

    enum CameraState{NO_CAMERA=0, CAMERA_OPEN, CAMERA_STREAM_ON};

    BT_RET setDeCode(DeCode *_decode);
    BT_RET setCameraCtrl(BCameraCtrlInterFace *_ctrl);
    BT_RET setCameraFunc(proFunc _func);
    BT_RET setCamera(void *_camera);

protected:
    void run ();
    BT_RET updateCameraState(CameraState _state);

private:
    BCameraCtrlInterFace *_cameraCtrl;
    proFunc func;
    DeCode *jpgDeCode;
    CameraState cameraState;
    void *camera;
};

#endif // BCAMERA_H
