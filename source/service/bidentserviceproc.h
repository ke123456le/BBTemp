#ifndef BIDENTSERVICEPROC_H
#define BIDENTSERVICEPROC_H

#include <QObject>
#include <QThread>
#include "extend/include/bata.h"
#include "../errorcode.h"
#include "../camera/bcameramanager.h"
#include "bsharedimagedata.h"

class BIdentServiceProc : public QThread
{
    Q_OBJECT
public:
    explicit BIdentServiceProc();
    ~BIdentServiceProc();

    BT_RET startIdent();
    BT_RET stopIdent();

public slots:
    BT_RET updateFaceData(const unsigned char *_data, const int _size,
                           const int _width, const int _height);
    BT_RET updateIrisData(const unsigned char *_data, const int _size,
                           const int _width, const int _height);

protected:
    void run();

private:
    void toIdentProc();

    void toFaceIdent();
    void toIrisIdent();
    void toFaceAndIrisIdent();

    BT_RET initIdentData();
    BT_RET releaseIdentData();

    void tranFaceEyeInfoToIris(SF_DETAIL_FACE *FaceEyeInfo,
                               Eye_Feature *LeftEyeInfo, Eye_Feature *RightEyeInfo);
    BT_RET SaveBmp(unsigned char *data, int w, int h, QString mSomeString, QString _User);

private:
    BSharedImageData *faceIdentSharedData;
    BSharedImageData *irisIdentSharedData;

    bool isFaceIdentImage;
    bool isIrisIdentImage;

signals:

public slots:
    void serviceRelease();
    /*BT_RET updateImageData(BCameraManager::ENUM_CAMERA_DEVICEO _camera,
                         unsigned char *_data, int _size);*/

};

#endif // BIDENTSERVICEPROC_H
