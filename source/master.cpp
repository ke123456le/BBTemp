#include <QDebug>

#include "extend/include/bata.h"
#include "master.h"
#include "identparamanager.h"
#include "userftrmanager.h"




#define __ShowSplashMsg(func, msg) (!func)?;:func(msg);

//人脸和虹膜数据
#define FACE_DATA_PATH   "./data/face.dat"
#define IRIS_DATA_PATH   "./data/iris.dat"



Master::Master():sysDbManager(NULL)
{

}



int Master::init (showMessage showMsgFunc)
{

    int errCode = (-1);

    //加载Board信息并验证是否注册

    //初始化数据库
    showMsgFunc(QString("初始化数据库..."));
    sysDbManager = new DbManager();
    /*if (!sysDbManager){

    }*/
    errCode = sysDbManager->InitDb ();
    CHECK_ERROR_RETURN(errCode);

    //加载算法数据
    showMsgFunc(QString("加载算法数据..."));
    errCode = loadData();
    CHECK_ERROR_RETURN(errCode);

    //加载系统参数
    showMsgFunc(QString("加载系统参数..."));

    //加载识别认证参数
    showMsgFunc(QString("加载识别参数..."));
    IdentParaManager *identParamanager = IdentParaManager::getInstance ();
    if (!identParamanager)
        return __BT_NOT_FOUND_PARA_LIB;

    Para *FaceIris = IdentParaManager::getInstance ()->getPara (PARA_FACE_IRIS_MATCH_THRD, errCode);
    if (FaceIris){
        qDebug()<<"FaceIris:"<<FaceIris->paraName ();
        qDebug()<<"FaceIrisValue:"<<FaceIris->getPataValue ();
    }

    //初始化用户模块并加载用户信息
    //初始化特征模块并加载特征数据
    showMsgFunc(QString("加载用户和特征数据"));
    UserFtrManager *userFtrManager = UserFtrManager::getInstance ();
    if (!userFtrManager)
        return __BT_NOT_FOUND_FEATURE_LIB;
    errCode = userFtrManager->init ();
    CHECK_ERROR_RETURN(errCode);

    //-----test-----
    FeatureDataMap *faceFeature = userFtrManager->featureMap (FACE_FEATURE_MAP);
    //faceFeature->FeatureTest ();


    //初始化摄像头及识别模块

    /*---tets---*/
    testCamera();

    //根据参数启动相关的系统服务

    return __BT_SUCC;
}








/*
 *private api of master
 */
/*
 * 加载人脸虹膜数据
 */
BT_RET Master::loadData ()
{
    BT_RET retCode = __BT_FAIL;

    retCode = initFaceData ();
    CHECK_ERROR_RETURN(retCode);

    retCode = initIrisData ();
    CHECK_ERROR_RETURN(retCode);

    return __BT_SUCC;
}


BT_RET Master::initFaceData(void)
{
    MYFILE mf;
    FILE *fp;
    fp = fopen(FACE_DATA_PATH, "rb");
    if (fp ==NULL)
    {
        printf("no initial file\n");
        return __BT_NOT_FOUND_ALGORITHM_DATA;
    }
    fseek(fp,0,SEEK_END);	//移到最末端
    mf.size = ftell(fp);	//Get size of wave data
    mf.buf = new unsigned char[mf.size]; //never delete
    mf.pos = 0;
    fseek(fp,0,SEEK_SET);	//移到最前端
    fread(mf.buf,1,mf.size,fp);
    fclose(fp);
    unsigned char * b1 = 0, * b2 = 0;
    int ret = BataInfraredFace_Init((struct MYFILE *)&mf,b1,b2);
    if (ret !=0){
        qDebug()<<"initial fail";
        return SFE_NOT_INITIALIZED;
    }

    return __BT_SUCC;
}

BT_RET Master::initIrisData(void)
{
    Iris_MYFILE mf;
    FILE *fp;
    fp = fopen(IRIS_DATA_PATH, "rb");
    if(!fp)
    {
        printf("open Iris.dat fail\n");
        return __BT_NOT_FOUND_ALGORITHM_DATA;
    }
    fseek(fp,0,SEEK_END);	//移到最末端
    mf.size = ftell(fp);	//Get size of wave data
    mf.buf = new unsigned char[mf.size]; //never delete
    mf.pos = 0;
    fseek(fp,0,SEEK_SET);	//移到最前端
    fread(mf.buf,1,mf.size,fp);
    fclose(fp);

    int ret = BataIris_init(&mf);
    if(ret !=0 )
    {
        printf("BataIris_init fail");
        delete[]mf.buf;
        return SFE_NOT_INITIALIZED;
    }

    return 0;
}



/*----------------------------------------------------------------------------------*/
#include <QCamera>
#include <qcamerainfo.h>
#include <QList>

BT_RET Master::testCamera()
{
    qDebug()<<__func__<<"CameraCount:"<<QCameraInfo::availableCameras ().count ();
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras) {
        //if (cameraInfo.deviceName() == "mycamera")
        //    camera = new QCamera(cameraInfo);
        qDebug()<<__func__<<"CameraName:"<<cameraInfo.deviceName();
    }
    return __BT_SUCC;
}
