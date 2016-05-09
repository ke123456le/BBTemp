#ifndef BCAMERAMANAGER_H
#define BCAMERAMANAGER_H

#include "../errorcode.h"
#include "bcamera.h"
#include "birisidentcamera.h"
#include "bfaceidentcamera.h"
#include "bfaceshowcamera.h"



class BCameraManager
{
public:
    typedef enum{
        VISIBLE_FACE_CAMERA = 0,
        INFRARED_FACE_CAMERA,
        INFRARED_IRIS_CAMERA
    }ENUM_CAMERA_DEVICEO;

    static BCameraManager *getInstance();/*单例*/
    static void releaseInstance();
    BCamera *getCamera(ENUM_CAMERA_DEVICEO _camera);

private:
    BCameraManager();
    BT_RET init ();

private:
    static BCameraManager *_BCameraManager;

    BFaceShowCamera *mVisibleFaceCamera;
    BFaceIdentCamera *mInfraredFaceCamera;
    BIrisIdentCamera *mIrisCamera;
};

#endif // BCAMERAMANAGER_H
