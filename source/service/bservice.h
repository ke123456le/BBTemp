#ifndef BSERVICE_H
#define BSERVICE_H

#include <QObject>

#include "../errorcode.h"


class BServiceInfo
{

};




class BService
{
public:
    BService();

    virtual BT_RET startService()=0;
    virtual BT_RET stopService()=0;
    virtual BServiceInfo *serviceInfo()=0;
};

#endif // BSERVICE_H
