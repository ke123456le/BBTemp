#include <QDir>
#include <QDateTime>
#include "bidentserviceproc.h"
#include "../identparamanager.h"

#include "../featurematch.h"

//#include "extend/include/bata.h"

BIdentServiceProc::BIdentServiceProc() : faceIdentSharedData(NULL),irisIdentSharedData(NULL),
    isFaceIdentImage(false), isIrisIdentImage(false)
{
    connect (this, SIGNAL(finished()), this, SLOT(serviceRelease()));
}

BIdentServiceProc::~BIdentServiceProc()
{
    if (faceIdentSharedData)
        delete faceIdentSharedData;
    if (irisIdentSharedData)
        delete irisIdentSharedData;
}


void BIdentServiceProc::run()
{
    toIdentProc ();
}


void BIdentServiceProc::toIdentProc()
{
    BT_RET retCode = __BT_SUCC;

    IdentParaManager * ParaManager = IdentParaManager::getInstance ();
    if (!ParaManager){
        //return __BT_NOT_FOUND_PARA_LIB;
        return;
    }

    BT_RET errCode = __BT_SUCC;
    Para * m_Para = ParaManager->getPara (PARA_FEATURE_TYPR, errCode);
    if (!m_Para){
        //return errCode;
        return;
    }

    int paraValue = m_Para->getPataValue ();
    qDebug()<<__func__<<"paraValue"<<paraValue;

    while(!QThread::currentThread ()->isInterruptionRequested ()){
        switch (paraValue) {
        case FACE_FEATURE_TYPE: /*单人脸特征*/
            toFaceIdent ();
            break;
        case IRIS_FEATURE_TYPE:/*单虹膜特征*/
            toIrisIdent ();
            break;
        case FACE_IRIS_FRATURE_TYPE:/*人脸虹膜结合*/
            toFaceAndIrisIdent ();
            break;
        default:
            //retVal = ;
            break;
        }

        if (QThread::currentThread ()->isInterruptionRequested ())
            break;

        QThread::msleep (10);
    }

    if (retCode){

    }
}

//face
void BIdentServiceProc::toFaceIdent()
{

}

//iris
void BIdentServiceProc::toIrisIdent()
{
    IdentImageInfo *faceData = NULL;
    IdentImageInfo *irisData = NULL;

    SF_FEATURE mTempRegFaceFtr;
    SF_DETAIL_FACE mTempEyeInfo;


    if (faceIdentSharedData){
        faceData = faceIdentSharedData->getImageData ();
    }

    if (irisIdentSharedData){
        irisData = irisIdentSharedData->getImageData ();
    }

    if (!faceData || !irisData){
        //qDebug()<<__func__<<"!faceData   !irisData";
        return;
    }


}

//face-iris
void BIdentServiceProc::toFaceAndIrisIdent()
{
    //qDebug()<<__func__;


    IdentImageInfo *faceData = NULL;
    IdentImageInfo *irisData = NULL;

    SF_FEATURE mTempRegFaceFtr;
    SF_DETAIL_FACE mTempEyeInfo;


    if (faceIdentSharedData){
        faceData = faceIdentSharedData->getImageData ();
    }

    //QThread::msleep (200);
    //return;
    //qDebug()<<__func__<<"11";
    if (irisIdentSharedData){
        irisData = irisIdentSharedData->getImageData ();
    }

    if (!faceData || !irisData){
        //qDebug()<<__func__<<"!faceData   !irisData";
        return;
    }


    //SaveBmp (faceData->imageData, faceData->imageWidth, faceData->imageHeight,"FACE_","dgd");
    //SaveBmp (irisData->imageData, irisData->imageWidth, irisData->imageHeight,"IRIS_","dgd");

    qDebug()<<__func__<<"Next BataInfratedFace_GetFeature";
    int mFaceFtrRet = BataInfratedFace_GetFeature(
                faceData->imageData, faceData->imageHeight, faceData->imageWidth,
                mTempRegFaceFtr, &mTempEyeInfo);
    qDebug()<<__func__<<"BataInfratedFace_GetFeature mFaceFtrRet:"<<mFaceFtrRet;
    if (SFE_OK != mFaceFtrRet){
        //emit sendMessage (FACE_FTR_FAIL);
        return;
    }

    int mEyeNum = 0;
    Eye_Feature m_EyeInfo[2];
    Eye_Feature mFaceEyeInfo[2];

    I_QFEATURE mLeftEyeFtr, mRightEyeFtr;

    memset(m_EyeInfo, 0, sizeof(Eye_Feature)*2);
    memset(mFaceEyeInfo, 0, sizeof(Eye_Feature)*2);

    tranFaceEyeInfoToIris(&mTempEyeInfo, &mFaceEyeInfo[0], &mFaceEyeInfo[1]);

    memset(&mLeftEyeFtr, 0, sizeof(I_QFEATURE));
    memset(&mRightEyeFtr, 0, sizeof(I_QFEATURE));
    //qDebug()<<__func__<<" Next BataIris_GetFeature_R_F ";
    int retIrisFtr = BataIris_GetFeature_R_F(irisData->imageData, irisData->imageHeight, irisData->imageWidth,
                                             mFaceEyeInfo, &mEyeNum, m_EyeInfo,&mLeftEyeFtr,
                                             &mRightEyeFtr, 0);
    //qDebug()<<__func__<<" BataIris_GetFeature_R_F retIrisFtr:"<<retIrisFtr;
    if (SFE_OK != retIrisFtr)
        return;

    MATCH_USER_T matchUser;
    unionMatchStrategy unionMatch(&mTempRegFaceFtr, &mLeftEyeFtr, &mRightEyeFtr);
    BT_RET matchRet = unionMatch.tomatch (&matchUser);
    qDebug()<<__func__<<"unionMatch====>matchRet:"<<matchRet;
    if (__BT_SUCC == matchRet){
        qDebug()<<__func__<<">>====>>===>>\nUser:"<<matchUser.mUser<<"\nScore:"<<matchUser.mScore;
    }
}


//-----------------------------------------------
BT_RET BIdentServiceProc::initIdentData()
{
    IdentParaManager * ParaManager = IdentParaManager::getInstance ();
    if (!ParaManager){
        return __BT_NOT_FOUND_PARA_LIB;
    }

    BT_RET errCode = __BT_SUCC;
    Para * m_Para = ParaManager->getPara (PARA_FEATURE_TYPR, errCode);
    if (!m_Para){
        return errCode;
    }

    int paraValue = m_Para->getPataValue ();

    if (paraValue & IRIS_FEATURE_TYPE){
        isFaceIdentImage = true;
        isIrisIdentImage = true;
    }else {
        isFaceIdentImage = true;
    }

    return __BT_SUCC;

    return __BT_SUCC;
}


BT_RET BIdentServiceProc::releaseIdentData()
{
    isFaceIdentImage = false;
    isIrisIdentImage = false;
#if 0
    if (faceIdentSharedData){
        delete faceIdentSharedData;
        faceIdentSharedData = NULL;
    }

    if (irisIdentSharedData){
        delete irisIdentSharedData;
        irisIdentSharedData = NULL;
    }
#endif
    return __BT_SUCC;
}


//---private slots
void BIdentServiceProc::serviceRelease()
{
    qDebug()<<"======================="<<__func__;
    releaseIdentData ();
}




BT_RET BIdentServiceProc::startIdent()
{
    if (isRunning ()){
        return __BT_IDENT_SERVICE_BUSY;
    }

    if (initIdentData())
        return __BT_IDENT_INIT_FAIL;

    qDebug()<<"======================="<<__func__;
    start ();

    return __BT_SUCC;
}


BT_RET BIdentServiceProc::stopIdent()
{
    if (isRunning ())
         requestInterruption ();

    return __BT_SUCC;
}


BT_RET BIdentServiceProc::updateFaceData(const unsigned char *_data, const int _size,
                                          const int _width, const int _height)
{
    //qDebug()<<"BIdentServiceProc"<<__func__;
    if (faceIdentSharedData){
        return faceIdentSharedData->updateImageData (_data, _size, _width, _height);
    }else{
        faceIdentSharedData = new BSharedImageData(_size);
        if (faceIdentSharedData)
            return faceIdentSharedData->updateImageData (_data, _size, _width, _height);
    }

    return __BT_FAIL;
}

BT_RET BIdentServiceProc::updateIrisData(const unsigned char *_data, const int _size,
                                          const int _width, const int _height)
{
    //qDebug()<<"BIdentServiceProc"<<__func__;
    if (irisIdentSharedData){
        return irisIdentSharedData->updateImageData (_data, _size, _width, _height);
    }else{
        irisIdentSharedData = new BSharedImageData(_size);
        if (irisIdentSharedData)
            return irisIdentSharedData->updateImageData (_data, _size, _width, _height);
    }

    return __BT_FAIL;
}


/*BT_RET updateImageData(BCameraManager::ENUM_CAMERA_DEVICEO _camera,
                     unsigned char *_data, int _size)
{

}*/



void BIdentServiceProc::tranFaceEyeInfoToIris(SF_DETAIL_FACE *FaceEyeInfo,
                           Eye_Feature *LeftEyeInfo, Eye_Feature *RightEyeInfo)
{
    LeftEyeInfo->x = FaceEyeInfo->leftEye.x;
    LeftEyeInfo->y = FaceEyeInfo->leftEye.y;
    LeftEyeInfo->r = 0;

    RightEyeInfo->x = FaceEyeInfo->rightEye.x;
    RightEyeInfo->y = FaceEyeInfo->rightEye.y;
    RightEyeInfo->r = 0;
}

BT_RET BIdentServiceProc::SaveBmp(unsigned char *data, int w, int h, QString mSomeString, QString _User)
{
    QString mDirStr = "/app/Bata/TT/" + _User;
    QDir mDir = QDir(mDirStr);
    if (!mDir.exists ()){
        //bool ret = mDir.mkdir (mDirStr);
        bool ret = mDir.mkpath (mDirStr);
        if (!ret)
            qDebug()<<__func__<<"mDir.mkpath fail";
    }

    QString mName = mDirStr + "/";
    mName += mSomeString;
    mName += QDateTime::currentDateTime ().toString ("yyyyMMddhhmmsszzz") + ".bmp";

    qDebug()<<__func__<<"mName:"<<mName;
    if (!data){
        qDebug()<<__func__<<"data is NULL";
    }

    //clSaveImage((char *)mName.toStdString ().c_str (), &oImage);
    QImage OutImg((uchar *)data, w, h, QImage::Format_Indexed8);

    QPixmap OutMap = QPixmap::fromImage (OutImg);
    OutMap.save (mName,"BMP");
    qDebug()<<__func__<<" OK!!!";

    return 0;
}





