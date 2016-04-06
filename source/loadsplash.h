#ifndef LOADSPLASH_H
#define LOADSPLASH_H

#include <QSplashScreen>
#include <QProgressBar>
#include <QLabel>



class LoadSplash : public QSplashScreen
{
public:
    explicit LoadSplash(const QPixmap &map);
    ~LoadSplash();

private:
    QProgressBar *finishProgressBar;        //程序启动进度条
    QLabel *progressLabel;                  //显示启动进度
    QLabel *msgLabel;                       //显示启动加载信息



public slots:
    void showMessage (const QString & msg, int percentValue);
    void showMessage (const QString & msg);
};

#endif // LOADSPLASH_H
