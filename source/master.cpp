#include "master.h"


#define __ShowSplashMsg(func, msg) (!func)?;:func(msg);

//人脸和虹膜数据
#define FACE_DATA_PATH   "./data/face.dat"
#define IRIS_DATA_PATH   "./data/Iris.dat"


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
    if (!sysDbManager){

    }
    errCode = sysDbManager->InitDb ();
    if (errCode)
        return errCode;

    //加载算法数据
    showMsgFunc(QString("加载算法数据..."));


    //加载系统参数
    showMsgFunc(QString("加载系统参数..."));

    //加载识别认证参数
    showMsgFunc(QString("加载识别参数..."));

    //初始化用户模块并加载用户信息
    showMsgFunc(QString("加载用户数据"));

    //初始化特征模块并加载特征数据
    showMsgFunc(QString("加载用户特征数据..."));


    //初始化摄像头及识别模块


    //根据参数启动相关的系统服务

    return __BT_SUCC;
}








/*
 *private api of master
 */
/*
 * 加载人脸虹膜数据
 */
int Master::loadData ()
{

    return __BT_SUCC;
}
