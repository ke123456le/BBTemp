#include "silenceinterface.h"
#include <QFontDialog>

SilenceInterface::SilenceInterface(QWidget *parent) : QWidget(parent)
{
    dataTimeWidget = new DateTimeWidget(this);
    dataTimeWidget->setGeometry (100, (480-200)/2, 240, 200);

    bool ok;
    QFont font = QFontDialog::getFont (&ok);
    if (ok){
        qDebug()<<__func__<<font;
    }
}

