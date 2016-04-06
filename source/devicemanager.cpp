#include "devicemanager.h"

DeviceManager::DeviceManager()
{

}



int DeviceManager::init()
{

    return __BT_SUCC;
}

int DeviceManager::getDeviceInfo(DeviceInfo & _devInfo)
{
    _devInfo.softWareVersion        = "0.0.01";
    _devInfo.deviceType             = 0;
    _devInfo.macAddr                = "26:87:93:56:99:12";
    _devInfo.snNum                  = "BT-SN2016033011310000";
    _devInfo.legalInfo              = "北京巴塔科技有限公司";
    _devInfo.diskInfo.alreadSize    = 1024*1024*100;
    _devInfo.diskInfo.maxSize       = (long long)1024*1024*1024*2;

    return __BT_SUCC;
}

