#ifndef USERFTRMANAGER_H
#define USERFTRMANAGER_H

#include <QString>
#include <QHash>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include <QDebug>

#include "errorcode.h"


/*
 * 用户信息
 */
class UserInfoFtr
{
public:
    UserInfoFtr(QString _name, QString _id, QString _org, QString _pswd, int _role){
        userName = _name;
        userID = _id;
        userOrg = _org;
        userPasswdStr = _pswd;
        userRole = _role;
    }

    QString userName;
    QString userID;
    QString userOrg;
    QString userPasswdStr;
    unsigned int userRole;
};


class UserMap : public QHash<QString, UserInfoFtr>
{
public:
    UserMap();
  ~UserMap();

    bool isLoadUserFromDb();
    bool loadUserFromDb();
    void deleteUser(QString _userId);
    bool insertUser(UserInfoFtr _userData);

    //--test-
    void UserTest();

private:
    bool isLoadUser;
};



/*
 *特征数据
 */
class FeatureData
{
public:
    FeatureData(){}
    FeatureData(QString _UserId, int _FtrNum, QString _FtrRegTime,
            QString FtrModTime, /*unsigned char* _FtrData, int _FtrLen*/ QByteArray _FtrData)
    {
        if (/*!_FtrData ||*/ _UserId.isEmpty () || /*_FtrLen <=0 ||*/ _FtrNum<0)
            return;
        featureNum      = _FtrNum;
        userId          = _UserId;
        featureRegTime  = _FtrRegTime;
        featureModTime  = FtrModTime;

        featureData = _FtrData;
    }
    ~FeatureData(){
        //if (m_FtrData)
        //    delete m_FtrData;
    }

public:
    int featureNum;
    QString userId;
    QString featureRegTime;
    QString featureModTime;
    QByteArray featureData;
};


enum FEATURE_MANAGER_TYPE{
    UNKONW_FEATHRE = 0,
    FACE_FEATURE,
    IRIS_FEATURE,
    FINGER_FEATURE,
    FINGER_VEIN_FEATURE
};

class FeatureDataMap : public QHash<QString, FeatureData>
{
public:
    FeatureDataMap(FEATURE_MANAGER_TYPE _ftrType);
    ~FeatureDataMap();
public:
    bool isLoadFeatureFromDb() const;
    bool loadFeatureFromDb();
    bool deleteFeatureData(QString _userId);
    bool deleteFeatureData(QString _userId, int _ftrNum);
    bool insertFeatureData(FeatureData _featureData);
    //---test--
    void FeatureTest(void);
//public:
//    QList<FtrData> m_FtrDataList;
private:
    bool isLoadFeatureData;
    unsigned int featureCount;
    unsigned int featureType;
};




/*
 * 用户特征管理
 * 定义为一个单例
 */
typedef enum
{
    FACE_FEATURE_MAP = 0,
    IRIS_FEATURE_MAP
}FEATURE_MAP_TYPE;

class UserFtrManager
{
public:
    static UserFtrManager *getInstance();
    static void releaseInstance();
    BT_RET init();
    UserMap * getUserMap();
    FeatureDataMap *featureMap(FEATURE_MAP_TYPE _ftrType);
private:
    UserFtrManager();
    ~UserFtrManager();

private:
    static UserFtrManager *_userFtrManager;

private:
    /**/
    bool isInit;
    /*data*/
    UserMap *userMap;
    FeatureDataMap *faceFeatureMap;
    FeatureDataMap *irisFeatureMap;
};

#endif // USERFTRMANAGER_H
