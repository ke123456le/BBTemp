#include "userftrmanager.h"



/*****************************************************************************************
 *
 * class UserMap
 *
 * ***************************************************************************************/
UserMap::UserMap():isLoadUser(false)
{
    //loadUserFromDb();
}

UserMap::~UserMap()
{

}

bool UserMap::isLoadUserFromDb()
{
    return isLoadUser;
}

bool UserMap::loadUserFromDb()
{
    if (isLoadUserFromDb ())
        return __BT_SUCC;

    QSqlQuery _FtrQuery;

    _FtrQuery.exec (QString("SELECT user_id, user_name, user_org, passwd, user_role "
                            "FROM UserInfo"));

    while(_FtrQuery.next ()){
       QString _userCode = _FtrQuery.value (0).toString ();
       QString _userName = _FtrQuery.value (1).toString ();
       QString _userOrg = _FtrQuery.value (2).toString ();
       QString _userPswd = _FtrQuery.value (3).toString ();
       unsigned int _ftrNum = _FtrQuery.value (4).toUInt ();

       UserInfoFtr mUserInfo(_userName, _userCode, _userOrg, _userPswd, _ftrNum);

       this->insertMulti (mUserInfo.userID, mUserInfo);
    }

    isLoadUser = true;

    return __BT_SUCC;
}

void UserMap::deleteUser(QString _UserId)
{
    this->remove (_UserId);
}

bool UserMap::insertUser(UserInfoFtr _FtrData)
{
    if (_FtrData.userID.isEmpty ())
        return false;
    this->insertMulti (_FtrData.userID, _FtrData);

    return true;
}

void UserMap::UserTest()
{
    QHash<QString, UserInfoFtr>::iterator mItem = this->begin ();

    while (mItem != this->end ()) {
        qDebug()<<__func__<<"ID:"<<mItem.value ().userID<<"Name:"<<mItem.value ().userName<<"Org:"
               <<mItem.value ().userOrg;
        mItem++;
    }
    qDebug()<<"\n";

    UserInfoFtr _TestFtrData1("Name", "id", "Org", "123456", 0);
    UserInfoFtr _TestFtrData2("Name1", "id", "Org1", "123456", 1);

    insertUser (_TestFtrData1);
    insertUser (_TestFtrData2);

    mItem = this->begin ();

    while (mItem != this->end ()) {
        qDebug()<<__func__<<"ID:"<<mItem.value ().userID<<"Name:"<<mItem.value ().userName<<"Org:"
               <<mItem.value ().userOrg;
        mItem++;
    }
    qDebug()<<"\n";

    deleteUser ("id");

    mItem = this->begin ();

    while (mItem != this->end ()) {
        qDebug()<<__func__<<"ID:"<<mItem.value ().userID<<"Name:"<<mItem.value ().userName<<"Org:"
               <<mItem.value ().userOrg;
        mItem++;
    }
    qDebug()<<"\n";
}



/****************************************************************************************
 *
 *
 *
 * **************************************************************************************/
FeatureDataMap::FeatureDataMap(FEATURE_MANAGER_TYPE _featureType):isLoadFeatureData(false),
    featureCount(0), featureType(UNKONW_FEATHRE)
{
    featureType = (unsigned int)_featureType;

    //loadFeatureFromDb ();
}

FeatureDataMap::~FeatureDataMap()
{

}

bool FeatureDataMap::isLoadFeatureFromDb() const
{
    return isLoadFeatureData;
}

bool FeatureDataMap::loadFeatureFromDb()
{
    if (isLoadFeatureFromDb())
        return __BT_SUCC;

    QString mTableName = "";
    switch (featureType) {
    case FACE_FEATURE:
        mTableName = "FaceFtr";
        break;
    case IRIS_FEATURE:
        mTableName = "IrisFtr";
        break;
    case FINGER_FEATURE:
        mTableName = "FingerFtr";
        break;
    case FINGER_VEIN_FEATURE:
        mTableName = "FingerVeinFtr";
        break;
    default:
        break;
    }

    if (mTableName.isEmpty ())
        return __BT_INIT_FEATURE_FAIL;

    QSqlQuery _FtrQuery;
    _FtrQuery.exec (QString("SELECT user_id, ftr_num, reg_time, mod_time, ftr_data "
                            "FROM %1").arg(mTableName));

    while(_FtrQuery.next ()){
       QString UserCode = _FtrQuery.value (0).toString ();
       int FtrNum = _FtrQuery.value (1).toInt ();
       QString RegTime = _FtrQuery.value (2).toString ();
       QString ModTime = _FtrQuery.value (3).toString ();
       QByteArray _FtrData = _FtrQuery.value (4).toByteArray ();

       //FtrData *m_FtrData = new FtrData(UserCode, FtrNum, RegTime, ModTime, _FtrData);
       FeatureData m_FeatureData(UserCode, FtrNum, RegTime, ModTime, _FtrData);

       this->insertMulti (m_FeatureData.userId, m_FeatureData);
       featureCount++;
    }

    isLoadFeatureData = __BT_SUCC;

    return true;
}

bool FeatureDataMap::deleteFeatureData(QString _userId)
{
    if (_userId.isEmpty ())
        return false;

    this->remove (_userId);

    return true;
}

bool FeatureDataMap::deleteFeatureData(QString _userId, int _ftrNum)
{
    if (_userId.isEmpty ())
        return false;

    QHash<QString, FeatureData>::iterator mItem = this->find (_userId);

    while(mItem!=this->end ()){
        if (mItem.key ()==_userId && mItem.value ().featureNum==_ftrNum){
            mItem = this->erase (mItem);
            continue;
        }
        mItem++;
    }

    return true;
}

bool FeatureDataMap::insertFeatureData(FeatureData _featureData)
{
    if (_featureData.userId.isEmpty ())
        return false;

    this->insertMulti (_featureData.userId, _featureData);

    return true;
}


void FeatureDataMap::FeatureTest(void)
{
    QHash<QString, FeatureData>::iterator mItem = this->begin ();

    while (mItem != this->end ()) {
        qDebug()<<__func__<<"ID:"<<mItem.value ().userId<<"Num:"<<mItem.value ().featureNum<<"Length:"
               <<mItem.value ().featureData.length ();
        mItem++;
    }
}







//用户特征管理
UserFtrManager *UserFtrManager::_userFtrManager = NULL;
UserFtrManager::UserFtrManager():isInit(NULL),userMap(NULL),faceFeatureMap(NULL),
    irisFeatureMap(NULL)
{
    userMap = new UserMap();
    faceFeatureMap = new FeatureDataMap(FACE_FEATURE);
    irisFeatureMap = new FeatureDataMap(IRIS_FEATURE);
}

UserFtrManager::~UserFtrManager()
{
    if (userMap)
        delete userMap;
    if (faceFeatureMap)
        delete faceFeatureMap;
    if (irisFeatureMap)
        delete irisFeatureMap;
}


UserFtrManager *UserFtrManager::getInstance()
{
    if (!_userFtrManager){
        _userFtrManager = new UserFtrManager();
        _userFtrManager->init ();
    }

    return _userFtrManager;
}

void UserFtrManager::releaseInstance ()
{
    if (_userFtrManager){
        delete _userFtrManager;
        _userFtrManager = NULL;
    }
}


#define LOAD_MAP(map, state, func)   do{if (!map->func())state++;}while(0)
#define CHECK_RETCODE(code, ret)    do{if(_)}while(0);
BT_RET UserFtrManager::init()
{
    int loadStat = 0;
    if (isInit)
        return __BT_SUCC;
    if (!userMap->isLoadUserFromDb ())
        LOAD_MAP(userMap, loadStat, loadUserFromDb);
        //userMap->loadUserFromDb ();
    if (!faceFeatureMap->isLoadFeatureFromDb ())
        faceFeatureMap->loadFeatureFromDb ();
    if (!irisFeatureMap->isLoadFeatureFromDb ())
        irisFeatureMap->loadFeatureFromDb ();


    if (loadStat){
        isInit = false;
    }else{
        isInit = true;
    }

    return loadStat?__BT_INIT_FEATURE_FAIL:__BT_SUCC;
}


UserMap * UserFtrManager::getUserMap()
{
    return userMap;
}


FeatureDataMap *UserFtrManager::featureMap(FEATURE_MAP_TYPE _ftrType)
{
    FeatureDataMap *returnMap = NULL;
    switch (_ftrType) {
    case FACE_FEATURE_MAP:
        returnMap = faceFeatureMap;
        break;
    case IRIS_FEATURE_MAP:
        returnMap = irisFeatureMap;
        break;
    default:
        returnMap = NULL;
        break;
    }

    return returnMap;
}

