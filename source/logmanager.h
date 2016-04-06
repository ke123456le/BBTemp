#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QString>

//日志类型
enum LOG_TYPE
{

};

//这是一个日志信息
class Log
{
public:
    QString     logId;                      //日志ID
    QString     userId;                     //用户ID
    QString     deviceSn;                   //设备SN号
    int         logType;                    //日志类型
    QString     genTime;                    //产生时间
    QString     logContent;                 //日志内容
    QString     logReMark;                  //备注标记
};

//这是一个条件,如查询日志,删除日志时
class LogContidion
{
    QString     userId;                     //用户ID
    int         logType;                    //日志类型
    QString     timeBegin;                  //起始时间
    QString     timeEnd;                    //结束时间
    int         limitCont;                  //限制条件,sql中limit
    int         startNo;                    //开始序号
};


//日志管理类
class LogManager
{
public:
    LogManager();

public:
    //保存一条日志
    int addOneLog(QString _user/*用户id*/, LOG_TYPE _type/*日志类型*/,
                  QString _content/*日志内容*/, QString _remark/*标注*/);
    //获取日志
    int getLog();

    //删除日志
    int removeLog(LogContidion & _logCont);
    int removeOneLog(QString _logId);

private:

};

#endif // LOGMANAGER_H
