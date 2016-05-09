#ifndef BIDENTSERVICE_H
#define BIDENTSERVICE_H

#include <QObject>
#include <QWidget>

#include "bservice.h"
#include "source/camera/birisidentcamera.h"
#include "source/camera/bfaceidentcamera.h"
#include "source/camera/bfaceshowcamera.h"

#include "source/service/bidentinterface.h"
#include "bidentserviceproc.h"



class BIdentService : public BService
{
public:
    BIdentService();
    ~BIdentService();

    BT_RET startService();
    BT_RET stopService();
    BServiceInfo *serviceInfo();

private:
/*private API*/
    BT_RET initIdent();
    BT_RET releaseIdent();

private:
    BIrisIdentCamera *identIrisCamera;
    BFaceIdentCamera *identFaceCamera;
    BFaceShowCamera *showFaceCamera;

    BIdentInterface *identShowWidget;
    BIdentServiceProc * identServiceProc;

private:/*data*/

};

#endif // BIDENTSERVICE_H
