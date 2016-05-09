#ifndef BIDENTINTERFACE_H
#define BIDENTINTERFACE_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

#include "../camera/bcamerawidget.h"


class BIdentInterface : public QDialog
{
    Q_OBJECT
public:
    explicit BIdentInterface(QWidget *parent = 0);
    ~BIdentInterface(){};

    BCameraWidget *cameraWidget();

protected:
    void resizeEvent (QResizeEvent *event);

signals:

public slots:
    void toInitAndShow();
    void toReleaseAndClose();

private:
    QLabel *testlabel;
    QPushButton *testButton;
    BCameraWidget *testCameraWidget;

    QPropertyAnimation *animation;
    QPropertyAnimation *animation1;
    QSequentialAnimationGroup *animationGroup;
};

#endif // BIDENTINTERFACE_H
