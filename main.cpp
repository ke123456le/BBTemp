#include "apps/mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QThread>

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




int main(int argc, char *argv[])
{
    BT_RET errCode = __BT_FAIL;
    QApplication a(argc, argv);
    MainWindow *w;
    qDebug()<<"-------------------------------";
    //init system
    g_splash = new QSplashScreen();
    g_splash->setPixmap (QPixmap(":/public/backImage").scaled (800, 480));

    g_splash->show ();
    Master master;

    errCode = master.init (showSplashMessage);
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
