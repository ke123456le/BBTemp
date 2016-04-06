#include "apps/mainwindow.h"
#include <QApplication>
#include <QSplashScreen>

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
        g_splash->showMessage (msg, Qt::AlignRight|Qt::AlignBottom);
        if (app)
            app->processEvents ();
    }
}




int main(int argc, char *argv[])
{
    BT_RET errCode = __BT_FAIL;
    QApplication a(argc, argv);

    //init system
    g_splash = new QSplashScreen();
    Master master;

    errCode = master.init (showSplashMessage);
    if (__BT_SUCC == errCode){
        showSplashMessage(QString("加载主界面..."));
        MainWindow w;

        w.show();
    }else{

    }


    return a.exec();
}
