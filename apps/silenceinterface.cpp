#include "silenceinterface.h"
#include <QFontDialog>



SilenceInterface::SilenceInterface(QWidget *parent) : QWidget(parent)
{
    dataTimeWidget = new DateTimeWidget(this);
    dataTimeWidget->setGeometry (100, (480-200)/2, 240, 200);

    identService = new BIdentService;



    //showWidget = new BCameraWidget(this);
    //testShowWidget = new BIdentInterface();
    //showWidget->setGeometry (350, 80, 400, 300);
    //showWidget->setGeometry (0, 15, 800, 450);
   // showWidget->setGeometry (0, 0, 800, 480);

    //testShowWidget->setGeometry (0, 0, 800, 480);
    //testShowWidget->setFixedSize (800, 450);

    ctrlTimer = new QTimer(this);

    showButton = new QPushButton("显示图像", this);
    showButton->setGeometry (400, 200, 100, 50);
    showButton->setDisabled (true);



    connect (ctrlTimer, SIGNAL(timeout()), this, SLOT(timerProc()));
    connect (showButton, SIGNAL(clicked(bool)), this, SLOT(toShowCamera()));


    ctrlTimer->start (1000*8);
}


void SilenceInterface::showimageFunc()
{

}




void SilenceInterface::timerProc()
{
    static bool showOrHind = false;

    if (showOrHind){
        identService->startService ();
        showOrHind = false;
    }else{
        identService->stopService ();
        showOrHind = true;
    }
}


void SilenceInterface::toShowCamera()
{
    identService->startService ();
}
