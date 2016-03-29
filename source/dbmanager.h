#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QIODevice>
#include <QTextStream>


#include <QDebug>


class DbManager
{
public:
    DbManager();
    ~DbManager();

public:
    bool InitDb();
    bool DbIsEnable();

private:
    QSqlDatabase m_DB;
    bool b_isEnable;

};

#endif // DBMANAGER_H
