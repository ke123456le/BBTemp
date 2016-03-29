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
    int loadData();
};

#endif // MASTER_H
