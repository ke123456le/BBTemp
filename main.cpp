#include "apps/mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QThread>
#include <QDir>

#include <QCamera>

//#include <QJsonObject>

//#include <QPluginLoader>
//#include <QMediaObject>

#include "source/errorcode.h"
#include "source/master.h"
struct mainInit{
    QSplashScreen *g_splash;
    QApplication *app;
};


QSplashScreen *g_splash = NULL;
QApplication *app = NULL;

void showSplashMessage(QString msg)
{


    if (g_splash){
        qDebug()<<__func__<<msg;
        //g_splash->showMessage (msg, Qt::AlignRight|Qt::AlignBottom);
        g_splash->showMessage (msg, Qt::AlignCenter);
        if (app)
            app->processEvents ();
    }
}



#include <QMediaServiceProviderPlugin>
int main(int argc, char *argv[])
{
    BT_RET errCode = __BT_FAIL;
    QApplication a(argc, argv);
    MainWindow *w;



    qDebug()<<__func__<<a.libraryPaths ();

 #if 0
    QObjectList _list = a.children ();


    for (int i=0; i<_list.size (); i++){
        qDebug()<<__func__<<":"<<_list.at (i)->metaObject ()->className ();
        qDebug()<<__func__<<":"<<_list.at (i)->metaObject ()->classInfoCount ();
    }

#endif

#if 0
    qDebug()<<"-------------------------------";
    QDir pluginsDir = QDir(qApp->applicationDirPath());
    pluginsDir.cd ("plugin");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));

        qDebug()<<__func__<<"errorString:"<<loader.errorString();

        qDebug()<<__func__<<"loader:"<<loader.load ();

        qDebug()<<__func__<<"isLoaded:"<<loader.isLoaded ();
        QObject *plugin = loader.instance();

        QJsonObject _json = loader.metaData ();
        QJsonObject::iterator item = _json.begin ();

        for (;item!=_json.end (); item++){
            qDebug()<<"Json:"<<item.value ().toString ();
        }

        //if (plugin) {
            qDebug()<<__func__<<"plugin fileName:"<<loader.fileName ();
            //populateMenus(plugin);
            //pluginFileNames += fileName;
        //}
    }

    qDebug()<<"-------------------------------";
#endif
    //init system
    g_splash = new QSplashScreen();
    g_splash->setPixmap (QPixmap(":/public/backImage").scaled (800, 480));

    g_splash->show ();
    Master master;

    errCode = master.init (showSplashMessage);
    //errCode = __BT_SUCC;

    showSplashMessage(QString("加载主界面..."));
    if (__BT_SUCC == errCode){
        w = new MainWindow();
        w->show();
        g_splash->finish (w);
    }else{
        showSplashMessage (QString("加载失败,错误代码:%1").arg (errCode));
    }

    return a.exec();
}
