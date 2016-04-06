#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QString>

#include "errorcode.h"

enum DEV_TYPE
{

};

struct DiskInfo
{
    long long alreadSize;
    long long maxSize;
};

class DeviceInfo
{
public:
    QString     softWareVersion;
    int         deviceType;
    QString     macAddr;
    QString     snNum;
    QString     legalInfo;
    DiskInfo    diskInfo;
};


class DeviceManager
{
public:
    DeviceManager();

    int init();

    int getDeviceInfo(DeviceInfo & _devInfo);

private:


};

#endif // DEVICEMANAGER_H
