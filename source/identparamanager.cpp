#include "identparamanager.h"


Para::Para(QString _name):_paraName(_name),
    _paraValue(0)
{

}


int Para::setParaValue(unsigned int _value)
{
     _paraValue = _value;

    return __BT_SUCC;
}





/*
 *
 */
IdentParaManager *IdentParaManager::_IdentParaManager = NULL;



IdentParaManager::IdentParaManager():paraSetting(NULL)
{
    paraSetting = new QSettings("./conf/ident_conf.ini", QSettings ::IniFormat);
}


IdentParaManager::~IdentParaManager()
{
    while (!identParaMap.isEmpty ()){
        QString key = identParaMap.firstKey ();
        identParaMap.remove (key);
    }
}


IdentParaManager *IdentParaManager::getInstance()
{
    if (_IdentParaManager == NULL){
        _IdentParaManager = new IdentParaManager();
        _IdentParaManager->init ();
    }

    return _IdentParaManager;
}

void IdentParaManager::releaseInstance()
{
    if (_IdentParaManager)
        delete _IdentParaManager;
}


int IdentParaManager::init ()
{
    int tmpValue = 0;

    if (!paraSetting)
        return __BT_FAIL;

    /*@1 ------识别参数-----@1*/
    /*人脸比对阈值参数*/
    Para faceMatchThrdPara(QString("FACE_MATCH_THRD"));
    tmpValue = paraSetting->value ("FACE/matchThrdValue").toInt ();
    if (tmpValue<FACE_MATCH_THRD_MIN || tmpValue>FACE_MATCH_THRD_MAX){
        faceMatchThrdPara.setParaValue (FACE_MATCH_THRD_DEF);
        paraSetting->setValue ("FACE/matchThrdValue", FACE_MATCH_THRD_DEF);
    }else{
        faceMatchThrdPara.setParaValue (tmpValue);
    }
    addIdentPara (PARA_FACE_MATCH_THRD, faceMatchThrdPara);

    /*人脸特征提取质量阈值参数*/
    Para faceFtrQualityPara(QString("FACE_QUALITY"));
    tmpValue = paraSetting->value ("FACE/qualityThrdValue").toInt ();
    if (tmpValue<FACE_QUALITY_MIN || tmpValue>FACE_QUALITY_MAX){
        faceFtrQualityPara.setParaValue (FACE_QUALITY_DEF);
        paraSetting->setValue ("FACE/qualityThrdValue", FACE_QUALITY_DEF);
    }else{
        faceFtrQualityPara.setParaValue (tmpValue);
    }
    addIdentPara (PARA_FACE_QUALITY_THRD, faceFtrQualityPara);

    /*虹膜识别比对阈值参数*/
    Para irisMatchThrdPara(QString("IRIS_MATCH_THRD"));
    tmpValue = paraSetting->value ("IRIS/matchThrdValue").toInt ();
    if (tmpValue<IRIS_MATCH_THRD_MIN || tmpValue>IRIS_MATCH_THRD_MAX){
        irisMatchThrdPara.setParaValue (IRIS_MATCH_THRD_DEF);
        paraSetting->setValue ("IRIS/matchThrdValue", IRIS_MATCH_THRD_DEF);
    }else{
        irisMatchThrdPara.setParaValue (tmpValue);
    }
    addIdentPara (PARA_IRIS_MATCH_THRD, irisMatchThrdPara);

    /*虹膜特征质量阈值参数(低阈值)*/
    Para irisQualityThrdPara(QString("IRIS_QUALITY"));
    tmpValue = paraSetting->value ("IRIS/qualityThrdValue").toInt ();
    if (tmpValue<IRIS_QUALITY_MIN || tmpValue>IRIS_QUALITY_MAX){
        irisQualityThrdPara.setParaValue (IRIS_QUALITY_DEF);
        paraSetting->setValue ("IRIS/qualityThrdValue", IRIS_QUALITY_DEF);
    }else{
        irisQualityThrdPara.setParaValue (tmpValue);
    }
    addIdentPara (PARA_IRIS_QUALITY_THRD, irisQualityThrdPara);

    /**/
    /*虹膜特征质量阈值参数(高阈值)*/
    Para irisQualityThrdParaH(QString("IRIS_QUALITY_H"));
    tmpValue = paraSetting->value ("IRIS/qualityThrdValueH").toInt ();
    if (tmpValue<IRIS_QUALITY_MIN || tmpValue>IRIS_QUALITY_MAX){
        /*在这暂时用最大值,由于算法暂时不支持单枚特征转模板,所以暂时设最大值,
         * 意味着注册时必须由三枚特征合成模板*/
        irisQualityThrdParaH.setParaValue (IRIS_QUALITY_MAX);
        paraSetting->setValue ("IRIS/qualityThrdValueH", IRIS_QUALITY_MAX);
    }else{
        irisQualityThrdParaH.setParaValue (tmpValue);
    }
    addIdentPara (PARA_IRIS_QUALITY_THRD_H, irisQualityThrdParaH);

    /*复合识别(人脸虹膜复合识别)比对阈值参数*/
    Para unionMatchThrdPara(QString("UNINON_MATCH_THRD"));
    tmpValue = paraSetting->value ("UNION/matchThrdValue").toInt ();
    if (tmpValue<UNION_MATCH_THRD_MIN || tmpValue>UNION_MATCH_THRD_MAX){
        unionMatchThrdPara.setParaValue (UNION_MATCH_THRD_DEF);
        paraSetting->setValue ("UNION/matchThrdValue", UNION_MATCH_THRD_DEF);
    }else{
        unionMatchThrdPara.setParaValue (tmpValue);
    }
    addIdentPara (PARA_FACE_IRIS_MATCH_THRD, unionMatchThrdPara);


    /*安全等级参数*/
    Para safeLevelPara(QString("SAFE_LEVEL"));
    tmpValue = paraSetting->value ("IDENT/safeLevel").toInt ();
    if (tmpValue<SAFE_LEVEL_L || tmpValue>SAFE_LEVEL_H){
        safeLevelPara.setParaValue (SAFE_LEVEL_DEF);
        paraSetting->setValue ("IDENT/safeLevel", SAFE_LEVEL_DEF);
    }else{
        safeLevelPara.setParaValue (tmpValue);
    }
    addIdentPara (PARA_SAFE_LEVEL, safeLevelPara);

    /*识别类型参数*/
    Para matchTypePara(QString("MATCH_TYPE"));
    tmpValue = paraSetting->value ("IDENT/matchType").toInt ();
    if (tmpValue<ONE_TO_MANY || tmpValue>ONE_TO_ONE){
        matchTypePara.setParaValue (ONE_TO_MANY);
        paraSetting->setValue ("IDENT/matchType", ONE_TO_MANY);
    }else{
        matchTypePara.setParaValue (tmpValue);
    }
    addIdentPara (PARA_MATCH_TYPE, matchTypePara);

    /*生物特征参数*/
    Para featurePara(QString("FEATURE_TYPE"));
    tmpValue = paraSetting->value ("IDENT/featureType").toInt ();
    if (tmpValue<=FEATURE_TYPE_MIN || tmpValue>=FEATURE_TYPE_MAX){
        featurePara.setParaValue (FEATURE_TYPE_DEF);
        paraSetting->setValue ("IDENT/featureType", FEATURE_TYPE_DEF);
    }else{
        featurePara.setParaValue (tmpValue);
    }
    addIdentPara (PARA_FEATURE_TYPR, featurePara);

    return __BT_SUCC;
}


QString IdentParaManager::paraTypeToName(PARA_ENUM _paraType)
{
    return (QString("PARA_%1").arg (_paraType));
}

int IdentParaManager::addIdentPara(PARA_ENUM _paraType, Para & _identPara)
{
    QString paraName = paraTypeToName (_paraType);

    if (paraName.isEmpty ())
        return __BT_PARA_INVILD;
    QMap<QString, Para>::const_iterator item = identParaMap.find (paraName);

    if ((item.key ()==paraName) || (item!=identParaMap.end ()))
        return __BT_PARA_INVILD;

    identParaMap.insert (paraName, _identPara);

    return __BT_SUCC;
}


int IdentParaManager::removeIdentPara(PARA_ENUM _paraType)
{
    QString paraName = paraTypeToName (_paraType);

    if (paraName.isEmpty ())
        return __BT_PARA_INVILD;

    QMap<QString, Para>::const_iterator item = identParaMap.find (paraName);

    if ((item.key ()==paraName) || (item!=identParaMap.end ()))
        identParaMap.remove (paraName);

    return __BT_SUCC;
}


Para *IdentParaManager::getPara(PARA_ENUM _Para, BT_RET & _errRet)
{
    Para *retPara = NULL;
    QString paraName = paraTypeToName (_Para);

    if (paraName.isEmpty ()){
        _errRet = __BT_PARA_INVILD;
        return NULL;
    }

    QMap<QString, Para>::const_iterator item = identParaMap.find (paraName);
    if (item.key ()==paraName || item!=identParaMap.end ()){
        retPara = (Para *)&item.value ();
        _errRet = __BT_SUCC;
    }else{
        _errRet = __BT_NOT_FOUND_IDENT_PARA;
    }

    return retPara;
}

