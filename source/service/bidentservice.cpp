#include "bidentservice.h"
#include "../camera/bcameramanager.h"
#include "../identparamanager.h"

BIdentService::BIdentService()
{
    BCameraManager *cameraManager = BCameraManager::getInstance ();

    if (cameraManager){
        identShowWidget = new BIdentInterface();

        showFaceCamera      = (BFaceShowCamera*)cameraManager->getCamera (BCameraManager::VISIBLE_FACE_CAMERA);
        identFaceCamera     = (BFaceIdentCamera*)cameraManager->getCamera (BCameraManager::INFRARED_FACE_CAMERA);
        identIrisCamera     = (BIrisIdentCamera*)cameraManager->getCamera (BCameraManager::INFRARED_IRIS_CAMERA);

        identServiceProc = new BIdentServiceProc();

        identShowWidget->setFixedSize (800, 480);

        QObject::connect (identIrisCamera, SIGNAL(sendImageData(const unsigned char*,int,int,int)),
                          identServiceProc, SLOT(updateIrisData(const unsigned char*,int,int,int)));
        QObject::connect (identFaceCamera, SIGNAL(sendImageData(const unsigned char*,int,int,int)),
                          identServiceProc, SLOT(updateFaceData(const unsigned char*,int,int,int)));
    }
}

BIdentService::~BIdentService()
{
    if (identShowWidget)
        delete identShowWidget;

    if (identIrisCamera)
        delete identIrisCamera;

    if (identFaceCamera)
            delete identFaceCamera;

    if (showFaceCamera)
        delete showFaceCamera;

    if (identServiceProc)
        delete identServiceProc;
}


BT_RET BIdentService::startService()
{
#if 0
    identIrisCamera->setShowWidget (identShowWidget->cameraWidget ());
    identShowWidget->toInitAndShow ();

    identIrisCamera->startCamera ();

    identServiceProc->startIdent ();
#else
    /*初始化开始显示*/
    //showFaceCamera->setShowWidget (identShowWidget->cameraWidget ());
    //showFaceCamera->startCamera ();

    identIrisCamera->setShowWidget (identShowWidget->cameraWidget ());


    identShowWidget->toInitAndShow ();
    /*识别相关关联*/

    identIrisCamera->startCamera ();

    identFaceCamera->startCamera ();

    /*启动识别处理*/
    identServiceProc->startIdent ();
#endif
}


BT_RET BIdentService::stopService()
{
#if 0
    identServiceProc->stopIdent ();

    identIrisCamera->stopCamera ();
    identShowWidget->toReleaseAndClose ();
#else
    /*停止识别处理*/
    identServiceProc->stopIdent ();
    /*释放识别相关*/
    identIrisCamera->stopCamera ();
    identFaceCamera->stopCamera ();

    /**/
    showFaceCamera->stopCamera ();
    identShowWidget->toReleaseAndClose ();
#endif
}


BServiceInfo *BIdentService::serviceInfo()
{
    return NULL;
}


BT_RET BIdentService::initIdent()
{
    return __BT_SUCC;
}

BT_RET BIdentService::releaseIdent()
{
    return __BT_SUCC;
}



