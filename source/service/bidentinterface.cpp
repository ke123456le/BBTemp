#include "bidentinterface.h"

#include <QDebug>

BIdentInterface::BIdentInterface(QWidget *parent) : QDialog(parent)
{
    testCameraWidget = new BCameraWidget(this);
    testlabel = new QLabel("我们来测试", this);
    testButton = new QPushButton("退出显示", this);
    testButton->setDisabled (true);

    testlabel->setGeometry ((800-100)/2, 0, 100, 40);
    testButton->setGeometry ((800-100)/2, 480-50, 100, 40);

#if 0
    animation = new QPropertyAnimation(this, "geometry");
    //animation1 = new QPropertyAnimation(this, "geometry");
    //animationGroup = new QSequentialAnimationGroup(this);
    connect (animation, SIGNAL(finished()), this, SLOT(close()));
#endif

    this->setModal (true);

    connect (testButton, SIGNAL(clicked(bool)), this, SLOT(toReleaseAndClose ()));
}


void BIdentInterface::resizeEvent (QResizeEvent *event)
{
    QSize mSize = this->size ();
    //qDebug()<<"BIdentInterface"<<__func__<<"Width:"<<mSize.width ()<<"Height:"<<mSize.height ();
    testCameraWidget->setGeometry (0, 0, mSize.width (), mSize.height ());
    //testCameraWidget->setFixedSize (mSize);

    //this->accept ();
}


BCameraWidget *BIdentInterface::cameraWidget()
{
    return testCameraWidget;
}

void BIdentInterface::toInitAndShow()
{
    qDebug()<<"BIdentInterface::"<<__func__;
    testCameraWidget->clearAndFillBlock();

    this->show ();
}



void BIdentInterface::toReleaseAndClose()
{
#if 0
    animation->setDuration(2000);
    animation->setStartValue(QRect(0, 0, 800, 480));
    animation->setEndValue(QRect(800/2, 480/2, 0, 0));

    //animation1->setDuration(100);
    //animation1->setStartValue(QRect(0, (480-6)/2, 800, 6));
    //animation1->setEndValue(QRect(800/2, (480-6)/2, 0, 0));

    //animationGroup->addAnimation (animation);
    //animationGroup->addAnimation (animation1);

    //animationGroup->start();
    animation->start ();
#endif
    this->close ();
}
