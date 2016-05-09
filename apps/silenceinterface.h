#ifndef SILENCEINTERFACE_H
#define SILENCEINTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>

#include "source/common/datetimewidget.h"
#include "source/service/bidentservice.h"



class SilenceInterface : public QWidget
{
    Q_OBJECT
public:
    explicit SilenceInterface(QWidget *parent = 0);

signals:

public slots:
    void timerProc();
    void toShowCamera();

private:
    DateTimeWidget *dataTimeWidget;

    //BCameraWidget *showWidget;
    //BIrisIdentCamera *myShowCamera;
    //BIdentInterface *testShowWidget;


    BIdentService *identService;
    QPushButton *showButton;
    QTimer *ctrlTimer;


private:
    void showimageFunc();
};

#endif // SILENCEINTERFACE_H
