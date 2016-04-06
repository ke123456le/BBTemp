#ifndef IDENTPARAMANAGER_H
#define IDENTPARAMANAGER_H

#include <QString>
#include <QMap>
#include <QSettings>
#include <QMutex>

#include "errorcode.h"


/*
 *参数界限及默认值
 */
/*人脸比对阈值*/
#define FACE_MATCH_THRD_MIN                 520
#define FACE_MATCH_THRD_MAX                 900
#define FACE_MATCH_THRD_DEF                 575
/*虹膜比对阈值*/
#define IRIS_MATCH_THRD_MIN                 500
#define IRIS_MATCH_THRD_MAX                 900
#define IRIS_MATCH_THRD_DEF                 550
/*人脸虹膜复合比对阈值*/
#define UNION_MATCH_THRD_MIN                480
#define UNION_MATCH_THRD_MAX                900
#define UNION_MATCH_THRD_DEF                500
/*人脸特征质量阈值*/
#define FACE_QUALITY_MIN                    40
#define FACE_QUALITY_MAX                    100
#define FACE_QUALITY_DEF                    70
/*虹膜特征质量阈值*/
#define IRIS_QUALITY_MIN                    30
#define IRIS_QUALITY_MAX                    100
#define IRIS_QUALITY_DEF                    33

/*
 * 安全等级
 */
typedef enum{
    SAFE_LEVEL_L = 0,                       /*低等级*/
    SAFE_LEVEL_M,                           /*中*/
    SAFE_LEVEL_H                            /*高*/
}SAFE_LEVEL;


/*
 *特征类型
 */
typedef enum{
    FACE_FEATURE_TYPE = 1,                  /*单人脸特征*/
    IRIS_FEATURE_TYPE = 2,                  /*单虹膜特征*/
    FACE_IRIS_FRATURE_TYPE = 3              /*人脸虹膜结合*/

    /*在以后增加新的类型是时注意,在这里每一种单类型的特征占一位,,如0位:人脸,1位:虹膜,2位:指纹.
     * 人脸+虹膜=3,人脸+虹膜+指纹=7
     */
}FEATURE_TYPE;


/*
 *比对类型
 */
typedef enum{
    ONE_TO_MANY = 0,                        /*一对多*/
    ONE_TO_ONE                              /*一对一*/
}MATCH_TYPE;



enum PARA_ENUM
{
    PARA_FACE_MATCH_THRD            = 1000,         //单人脸比对阈值参数
    PARA_FACE_QUALITY_THRD,                         //人脸特征提取质量阈值
    PARA_IRIS_MATCH_THRD,                           //单虹膜比对阈值参数
    PARA_IRIS_QUALITY_THRD,                         //虹膜特征提取质量阈值
    PARA_FACE_IRIS_MATCH_THRD,                      //人脸虹膜复合识别比对阈值d
    PARA_FINGER_MATCH_THRD,                         //指纹比对阈值
    PARA_IRIS_QUALITY_THRD_H,                       //虹膜特征提取质量高阈值

    PARA_SAFE_LEVEL,                                //安全等级参数
    PARA_TEATURE_TYPR,                              //特征类型参数
    PARA_MATCH_TYPE                                 //比对方式参数
};


//比对参数类
class Para
{
public:
    explicit Para(QString _name);

    inline QString paraName() const{/*参数名称*/
        return _paraName;
    }

    inline int getPataValue() const{/*获取参数值*/
        return _paraValue;
    }

    int setParaValue(unsigned int _value);/*设置参数值*/

private:
    QString _paraName;               //参数名称
    int _paraValue;                  //参数值
};



/*
 *是被参数管理类.定义为一个单例
 */
class IdentParaManager
{
public:
    static IdentParaManager *getInstance();/*单例*/
    static void releaseInstance();


private:
    IdentParaManager();
    ~IdentParaManager();

    int init();

private:
    static IdentParaManager *_IdentParaManager;
    QMap <QString, Para> identParaMap;
    QSettings *paraSetting;

private:
    QString paraTypeToName(PARA_ENUM _paraType);
    int addIdentPara(PARA_ENUM _paraType, Para &_identPara);
    int removeIdentPara(PARA_ENUM _paraType);
};

#endif // IDENTPARAMANAGER_H
