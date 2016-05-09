#include "bcameramanager.h"

BCameraManager::BCameraManager()
{

}


BCameraManager *BCameraManager::_BCameraManager = NULL;

BCameraManager *BCameraManager::getInstance()
{
    if (_BCameraManager == NULL){
        _BCameraManager = new BCameraManager();
        _BCameraManager->init ();
    }

    return _BCameraManager;
}

void BCameraManager::releaseInstance()
{
    if (_BCameraManager)
        delete _BCameraManager;
}


BT_RET BCameraManager::init ()
{
    mVisibleFaceCamera = new BFaceShowCamera();
    mInfraredFaceCamera = new BFaceIdentCamera();
    mIrisCamera = new BIrisIdentCamera();

    return __BT_SUCC;
}


BCamera *BCameraManager::getCamera(ENUM_CAMERA_DEVICEO _camera)
{
    BCamera *mCamera;
    switch(_camera){
    case VISIBLE_FACE_CAMERA:
        mCamera = mVisibleFaceCamera;
        break;
    case INFRARED_FACE_CAMERA:
        mCamera = mInfraredFaceCamera;
        break;
    case INFRARED_IRIS_CAMERA:
        mCamera = mIrisCamera;
        break;
    default:
        mCamera = NULL;
        break;
    }

    return mCamera;
}
