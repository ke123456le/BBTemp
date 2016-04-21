#ifndef MASTER_H
#define MASTER_H

#include <QString>

#include "errorcode.h"
#include "dbmanager.h"

typedef void (* showMessage)(QString msg);

class Master
{
public:
    Master();

    int init(showMessage showMsgFunc);

private:
    DbManager *sysDbManager;


private:
    //private api
    BT_RET loadData();
    BT_RET initFaceData(void);
    BT_RET initIrisData(void);

    //test
    BT_RET testCamera();
};

#endif // MASTER_H
