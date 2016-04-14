#ifndef FEATUREMATCH_H
#define FEATUREMATCH_H

#include <QDateTime>

#include "extend/include/bata.h"
#include "source/errorcode.h"
#include "userftrmanager.h"


struct MATCH_USER_T{
    QString mUser;
    int mScore;
    int mQuality;
    MATCH_USER_T(QString _user="", int _score=0, int _quality=0){
        mUser       = _user;
        mScore      = _score;
        mQuality    = _quality;
    }
};



/*
 * 比对抽象类
 */
class AbstractMatch{
public:
    AbstractMatch(){}
    virtual BT_RET match(MATCH_USER_T *_user, void *_data, void *arg)=0;
    virtual BT_RET match(QString _id, void *_data, int *_score, void *arg)=0;

private:
    virtual int matchThresholdValue() = 0;
};



/*
 * 人脸特征比对
 */
class FaceMatch : public AbstractMatch
{
public:
    FaceMatch();

    BT_RET match(MATCH_USER_T *_user, void *_data, void *arg=NULL);
    BT_RET match(QString _id, void *_data, int *_score, void *arg=NULL);
private:
    int matchThresholdValue();
    int updateFaceFeatureToDataBase(QString _User, MY_SF_FEATURE_SET_ONE *mFeature,
                                    unsigned int mNum);
};



/*
 * 虹膜特征比对
 */
class IrisMatch : public AbstractMatch
{
public:
    IrisMatch();
    BT_RET match(MATCH_USER_T *_user, void *_data, void *arg=NULL);
    BT_RET match(QString _id, void *_data, int *_score, void *arg=NULL);

private:
    int matchThresholdValue();
};




/*******************************************************************************************
 *
 * 下面是比对策略
 *
 * ****************************************************************************************/
/*
 * 比对策略抽象类
 */
class AbstractMatchStrategy
{
public:
    AbstractMatchStrategy();
    virtual BT_RET tomatch(MATCH_USER_T *_user)=0;
//private:
    BT_RET matchFtr(MATCH_USER_T *_user, void *_data,
                            AbstractMatch *_match, void *_arg=NULL);
    BT_RET matchFtr(QString _user, void *_data, int *_score,
                            AbstractMatch *_match, void *_arg=NULL);
};



/*
 * 人脸比对策略
 */
class faceMatchStrategy : public AbstractMatchStrategy
{
public:
    faceMatchStrategy(SF_FEATURE * _feature);
    int tomatch(MATCH_USER_T *_user);
private:
    SF_FEATURE * faceFeature;
};




/*
 * 虹膜比对策略
 */
class irisMatchStrategy : public AbstractMatchStrategy
{
public:
    irisMatchStrategy(I_QFEATURE *_irisLeftFeature, I_QFEATURE *_irisRightFeature);
    int tomatch(MATCH_USER_T *_user);
private:
    I_QFEATURE * irisLeftFeature;
    I_QFEATURE * irisRightFeature;
};



/*
 * 人脸虹膜复合比对策略
 */
class unionMatchStrategy : public AbstractMatchStrategy
{
public:
    unionMatchStrategy(SF_FEATURE *_faceFeature, I_QFEATURE *_irisLeftFeature,
                       I_QFEATURE *_irisRightFeature);
    int tomatch(MATCH_USER_T *_user);

private:
    SF_FEATURE * faceFeature;
    I_QFEATURE * irisLeftFeature;
    I_QFEATURE * irisRightFeature;
};




#endif // FEATUREMATCH_H
