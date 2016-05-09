#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QObject>
#include <QWidget>

class UserInterface : public QWidget
{
    Q_OBJECT
public:
    explicit UserInterface(QWidget *parent = 0);

signals:

public slots:
};

#endif // USERINTERFACE_H
