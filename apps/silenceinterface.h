#ifndef SILENCEINTERFACE_H
#define SILENCEINTERFACE_H

#include <QWidget>

#include "source/common/datetimewidget.h"

class SilenceInterface : public QWidget
{
    Q_OBJECT
public:
    explicit SilenceInterface(QWidget *parent = 0);

signals:

public slots:

private:
    DateTimeWidget *dataTimeWidget;
};

#endif // SILENCEINTERFACE_H
