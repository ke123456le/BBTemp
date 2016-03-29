#include "dbmanager.h"


//数据库脚本路径
#define DB_SQL_PATH                     "./db/demo.db"


DbManager::DbManager():b_isEnable(false)
{

}

DbManager::~DbManager()
{

}


bool DbManager::InitDb()
{
    bool isCreateDb;

    if (QFile::exists (DB_SQL_PATH))
        isCreateDb = false;
    else
        isCreateDb = true;

    m_DB = QSqlDatabase::addDatabase ("QSQLITE");
    m_DB.setDatabaseName (QString(DB_SQL_PATH));
    bool b_Ret = m_DB.open ();
    //qDebug()<<"isCreateDb"<<isCreateDb<<" b_Ret"<<b_Ret;
    if (!b_Ret)
        return false;

    if (isCreateDb){
        #if 0
        QString _sql;
        QFile _fSql("./db/demo.sql");
        if (!_fSql.open (QIODevice::ReadOnly))
            return false;
        QTextStream _input(&_fSql);
        while(!_input.atEnd ()){
            //_sql += _input.readAll ();
            _sql += _input.readLine ();
            _sql += "\n";
        }

        qDebug()<<"SQL:"<<_sql;
        QSqlQuery _query;
        _query.exec (_sql);
        #endif

        system("sqlite3 ./db/demo.db < ./db/demo.sql");
        return true;
    }

    return true;
}

bool DbManager::DbIsEnable ()
{
    return b_isEnable;
}
