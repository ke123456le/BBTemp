#include "featurematch.h"
#include "identparamanager.h"

/************************************face****************************************/
/*
 *
 */
FaceMatch::FaceMatch()
{

}

BT_RET FaceMatch::match (MATCH_USER_T *_user, void *_data, void *arg)
{
    if (!_user || !_data)
        return __BT_DATA_INVILD;
    int isFoundUser = false;

    UserFtrManager *userFtrManager = UserFtrManager::getInstance ();
    if (!userFtrManager)
        return __BT_NOT_FOUND_FEATURE_LIB;

    SF_FEATURE *matchFtr = (SF_FEATURE*)_data;

    int faceThrdValue = matchThresholdValue ();

    FeatureDataMap *faceFeatureMap = userFtrManager->featureMap (FACE_FEATURE_MAP);
    if (!faceFeatureMap)
        return __BT_NOT_FOUND_FEATURE_LIB;
    if (faceFeatureMap->count () <= 0)
        return __BT_FEATURE_RMPTY;

    FeatureDataMap::iterator item = faceFeatureMap->begin ();
    for (;item!=faceFeatureMap->end ();item++){
        int tmpScore = 0;
        if (item.value ().featureData.length () < (int)sizeof(MY_SF_FEATURE_SET_ONE))
            continue;

        int mRet = BataInfraredFace_MatchM(matchFtr, (MY_SF_FEATURE_SET_ONE*)
                                           item.value ().featureData.data (), true, &tmpScore);

        if ((SFE_OK==mRet) || (SFE_FEATURE_ADAPT==mRet)){
            if (SFE_FEATURE_ADAPT==mRet){
                isFoundUser     = true;
                //update
                updateFaceFeatureToDataBase(item.value ().userId, (MY_SF_FEATURE_SET_ONE*)
                                            item.value ().featureData.data (), item.value ().featureNum);
            }

            if (tmpScore > faceThrdValue){
                isFoundUser     = true;
            }

            if (isFoundUser){
                _user->mScore   = tmpScore;
                _user->mUser    = item.value ().userId;
                _user->mQuality = matchFtr->Quality;
                break;
            }
        }
    }

    return (isFoundUser)?__BT_SUCC:__BT_NOT_FOUND_USER;
}



BT_RET FaceMatch::match (QString _id, void *_data, int *_score, void *arg)
{
    if (!_data || _id.isEmpty ())
        return __BT_DATA_INVILD;

    int isFoundUser = false;

    UserFtrManager *userFtrManager = UserFtrManager::getInstance ();
    if (!userFtrManager)
        return __BT_NOT_FOUND_FEATURE_LIB;

    SF_FEATURE *matchFtr = (SF_FEATURE*)_data;

    FeatureDataMap *faceFeatureMap = userFtrManager->featureMap (FACE_FEATURE_MAP);
    if (!faceFeatureMap)
        return __BT_NOT_FOUND_FEATURE_LIB;
    if (faceFeatureMap->count () <= 0)
        return __BT_FEATURE_RMPTY;

    FeatureDataMap::iterator item = faceFeatureMap->find (_id);
    for (;item!=faceFeatureMap->end () && item.key ()==_id;item++){
        int tmpScore = 0;
        if (item.value ().featureData.length () < (int)sizeof(MY_SF_FEATURE_SET_ONE))
            continue;

        int mRet = BataInfraredFace_MatchM(matchFtr, (MY_SF_FEATURE_SET_ONE*)
                                           item.value ().featureData.data (), true, &tmpScore);

        if ((SFE_OK==mRet) || (SFE_FEATURE_ADAPT==mRet)){
            isFoundUser     = true;
            if (SFE_FEATURE_ADAPT==mRet){
                //update
                updateFaceFeatureToDataBase(item.value ().userId, (MY_SF_FEATURE_SET_ONE*)
                                            item.value ().featureData.data (), item.value ().featureNum);
            }

            *_score    = tmpScore;
            break;
        }
    }

    return (isFoundUser)?__BT_SUCC:__BT_NOT_FOUND_USER;
}

int FaceMatch::matchThresholdValue ()
{
    BT_RET errCode = __BT_FAIL;

    IdentParaManager *identParaManager = IdentParaManager::getInstance ();
    if (!identParaManager)
        return __BT_FAIL;
    Para *matchThrdPara = identParaManager->getPara (PARA_FACE_MATCH_THRD, errCode);
    if (!matchThrdPara)
        return errCode;

    return matchThrdPara->getPataValue ();
}

int FaceMatch::updateFaceFeatureToDataBase(QString _User, MY_SF_FEATURE_SET_ONE *mFeature,
                                           unsigned int mNum)
{
    QString mCurrTime = QDateTime::currentDateTime ().toString ("yyyy-MM-dd hh:mm:ss");

    QSqlQuery _featureQuery;
    //_FtrQuery.exec ();

    _featureQuery.prepare(QString("UPDATE FaceFtr SET mod_time=?, ftr_data=?"
                              " WHERE user_id='%1' AND ftr_num=%2").arg(_User).arg (mNum));

    _featureQuery.addBindValue (mCurrTime);
    _featureQuery.addBindValue (QVariant(QByteArray((char *)mFeature, sizeof(MY_SF_FEATURE_SET_ONE))));

    //qDebug()<<__func__<<"mCurrTime:"<<mCurrTime<<"mNum:"<<mNum;

    //_FeatureQuery.bindValue (0, mCurrTime);
    //_FeatureQuery.bindValue (1, QVariant(QByteArray((char *)mFeature, sizeof(MY_SF_FEATURE_SET_ONE))));

    if (!_featureQuery.exec ()){
        qDebug()<<"Update FaceFeature Fail!";
        return __BT_UPDATA_DATA_FAIL;
    }

    return __BT_SUCC;
}




/*******************************************************************************/
/*
 *
 */
IrisMatch::IrisMatch()
{

}


#define IRIS_LEFT                   0
#define IRIS_RIGHT                  1
BT_RET IrisMatch::match (MATCH_USER_T *_user, void *_data, void *arg)
{
    if (!_user || !_data || arg)
        return __BT_DATA_INVILD;

    int isFoundUser = false;
    int irisNum = *(int*)arg;
    if (irisNum<IRIS_LEFT || irisNum>IRIS_RIGHT)
        return __BT_PARA_INVILD;

    UserFtrManager *userFtrManager = UserFtrManager::getInstance ();
    if (!userFtrManager)
        return __BT_NOT_FOUND_FEATURE_LIB;

    I_QFEATURE *matchFtr = (I_QFEATURE*)_data;

    int irisThrdValue = matchThresholdValue ();

    FeatureDataMap *irisFeatureMap = userFtrManager->featureMap (IRIS_FEATURE_MAP);
    if (!irisFeatureMap)
        return __BT_NOT_FOUND_FEATURE_LIB;
    if (irisFeatureMap->count () <= 0)
        return __BT_FEATURE_RMPTY;

    FeatureDataMap::iterator item = irisFeatureMap->begin ();
    for (;item!=irisFeatureMap->end (); item++){
        int tmpScore = 0;
        if (item.value ().featureNum != irisNum)
            continue;
        if (item.value ().featureData.length () < (int)sizeof(I_QFEATURE_EN))
            continue;

        if (BataIris_Match((I_QFEATURE_EN &)(*item.value ().featureData.data ()), *matchFtr, &tmpScore)){
            continue;
        }

        if (tmpScore > irisThrdValue){
            isFoundUser   = true;
            _user->mScore   = tmpScore;
            _user->mUser    = item.value ().userId;
            break;
        }
    }

    return isFoundUser?__BT_SUCC:__BT_NOT_FOUND_USER;
}

BT_RET IrisMatch::match (QString _id, void *_data, int *_score, void *arg)
{
    if (_id.isEmpty ()|| !_data || arg)
        return __BT_DATA_INVILD;

    int isFoundUser = false;
    int irisNum = *(int*)arg;
    if (irisNum<IRIS_LEFT || irisNum>IRIS_RIGHT)
        return __BT_PARA_INVILD;

    UserFtrManager *userFtrManager = UserFtrManager::getInstance ();
    if (!userFtrManager)
        return __BT_NOT_FOUND_FEATURE_LIB;

    I_QFEATURE *matchFtr = (I_QFEATURE*)_data;

    //int irisThrdValue = matchThresholdValue ();

    FeatureDataMap *irisFeatureMap = userFtrManager->featureMap (IRIS_FEATURE_MAP);
    if (!irisFeatureMap)
        return __BT_NOT_FOUND_FEATURE_LIB;
    if (irisFeatureMap->count () <= 0)
        return __BT_FEATURE_RMPTY;
    FeatureDataMap::iterator item = irisFeatureMap->find (_id);
    for (;item!=irisFeatureMap->end () && item.value ().userId==_id;item++){
        int tmpScore = 0;
        if (item.value ().featureNum != irisNum)
            continue;
        if (item.value ().featureData.length () < (int)sizeof(I_QFEATURE_EN))
            continue;

        if (BataIris_Match((I_QFEATURE_EN &)(*item.value ().featureData.data ()), *matchFtr, &tmpScore)){
            continue;
        }

        *_score     = tmpScore;
        isFoundUser = true;
        break;
    }

    return isFoundUser?__BT_SUCC:__BT_NOT_FOUND_USER;
}


int IrisMatch::matchThresholdValue ()
{
    BT_RET errCode = __BT_FAIL;

    IdentParaManager *identParaManager = IdentParaManager::getInstance ();
    if (!identParaManager)
        return __BT_FAIL;
    Para *matchThrdPara = identParaManager->getPara (PARA_IRIS_MATCH_THRD, errCode);
    if (!matchThrdPara)
        return errCode;

    return matchThrdPara->getPataValue ();
}











/*******************************************************************************************
 *
 * 下面是比对策略
 *
 * ****************************************************************************************/
AbstractMatchStrategy::AbstractMatchStrategy()
{

}

BT_RET AbstractMatchStrategy::matchFtr(MATCH_USER_T *_user, void *_data,
                        AbstractMatch *_match, void *_arg)
{
    if (!_match)
        return __BT_DATA_INVILD;
    return _match->match (_user,_data,_arg);
}

BT_RET AbstractMatchStrategy::matchFtr(QString _user, void *_data, int *_score,
                        AbstractMatch *_match, void *_arg)
{
    if (!_match)
        return __BT_DATA_INVILD;
    return _match->match (_user,_data,_score,_arg);
}



/*
 *
 */
faceMatchStrategy::faceMatchStrategy(SF_FEATURE * _feature):faceFeature(NULL)
{
    if (_feature)
        faceFeature = _feature;
}


int faceMatchStrategy::tomatch (MATCH_USER_T *_user)
{
    if (!_user)
        return __BT_DATA_INVILD;
    if (!faceFeature)
        return __BT_DATA_INVILD;

    FaceMatch faceMatch;

    return matchFtr (_user, faceFeature, &faceMatch);
}



/*
 *
 */
irisMatchStrategy::irisMatchStrategy(I_QFEATURE *_irisLeftFeature, I_QFEATURE *_irisRightFeature):
    irisLeftFeature(NULL),irisRightFeature(NULL)
{
    if (_irisLeftFeature)
        irisLeftFeature = _irisLeftFeature;
    if (_irisRightFeature)
        irisRightFeature = _irisRightFeature;
}

#define CHECK_CODE_PRO(code) do{if(__BT_SUCC == code)return code;}while(0);
int irisMatchStrategy::tomatch(MATCH_USER_T *_user)
{
    BT_RET errRet = __BT_FAIL;
    if (!_user)
        return __BT_DATA_INVILD;

    if (!irisLeftFeature || !irisRightFeature)
        return __BT_DATA_INVILD;

    int irisNum;
    IrisMatch irisMatch;
    irisNum = IRIS_LEFT;
    errRet = matchFtr (_user, irisLeftFeature, &irisMatch, &irisNum);
    CHECK_CODE_PRO(errRet);

    irisNum = IRIS_RIGHT;
    errRet = matchFtr (_user, irisRightFeature, &irisMatch, &irisNum);
    CHECK_CODE_PRO(errRet);

    return errRet;
}





/*
 *
 */
unionMatchStrategy::unionMatchStrategy(SF_FEATURE *_faceFeature, I_QFEATURE *_irisLeftFeature,
                                       I_QFEATURE *_irisRightFeature):
    faceFeature(NULL),irisLeftFeature(NULL),irisRightFeature(NULL)
{
    if (_faceFeature)
        faceFeature = _faceFeature;
    if (_irisLeftFeature)
        irisLeftFeature = _irisLeftFeature;
    if (_irisRightFeature)
        irisRightFeature = _irisRightFeature;
}

int unionMatchStrategy::tomatch (MATCH_USER_T *_user)
{
    BT_RET errRet = __BT_FAIL;
    if (!_user)
        return __BT_DATA_INVILD;

    if (!faceFeature || !irisLeftFeature || !irisRightFeature)
        return __BT_DATA_INVILD;

    UserFtrManager *userFtrManager = UserFtrManager::getInstance ();
    if (!userFtrManager)
        return __BT_NOT_FOUNT_USERS_LIB;
    UserMap * userMap = userFtrManager->getUserMap ();
    if (!userMap)
        return __BT_NOT_FOUNT_USERS_LIB;
    if (userMap->isEmpty ())
        return __BT_USERS_EMPTY;

    IdentParaManager *_identParaManager = IdentParaManager::getInstance ();
    if (!_identParaManager)
        return __BT_NOT_FOUND_PARA_LIB;

    Para *safePara = _identParaManager->getPara (PARA_SAFE_LEVEL, errRet);
    Para *unionThrdPara = _identParaManager->getPara (PARA_FACE_IRIS_MATCH_THRD, errRet);
    if (!safePara || !unionThrdPara)
        return __BT_PARA_INVILD;

    int irisNum;
    int isFoundUser = false;
    FaceMatch faceMatch;
    IrisMatch irisMatch;


    int safeLevelValue = safePara->getPataValue ();
    int unionThrdValue = unionThrdPara->getPataValue ();

    UserMap::iterator item = userMap->begin ();

    for (;item!=userMap->end (); item++){
        int faceScore       = 0;
        int irisLeftScore   = 0;
        int irisRightScore  = 0;
        isFoundUser = false;
        matchFtr (item.value ().userID, faceFeature, &faceScore, &faceMatch);
        irisNum = IRIS_LEFT;
        matchFtr (item.value ().userID, irisLeftFeature, &irisLeftScore, &irisMatch, &irisNum);
        irisNum = IRIS_RIGHT;
        matchFtr (item.value ().userID, irisRightFeature, &irisRightScore, &irisMatch, &irisNum);

        #define UNION_IRIS_FIRIS_THRD               535
        if (SAFE_LEVEL_H == safeLevelValue){
            if ((UNION_IRIS_FIRIS_THRD>irisLeftScore)
                    && (UNION_IRIS_FIRIS_THRD>irisRightScore))
                continue;
        }

        int lastScore = 0;
        int lastMatch = BataFIM(faceFeature->Quality, faceScore,
                            irisLeftFeature->iQuality, irisLeftScore,
                            irisRightFeature->iQuality, irisRightScore,
                            &lastScore);

        if (0 == lastMatch){
            if (lastScore > unionThrdValue){
                isFoundUser      = true;
                _user->mScore   = lastScore;
                _user->mQuality = 0;
                _user->mUser    = item.value ().userID;
                break;
            }
        }
    }

    return isFoundUser?__BT_SUCC:__BT_NOT_FOUND_USER;
}
