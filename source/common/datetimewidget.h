#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QDateTime>
#include <QLabel>
#include <QTimer>
#include <QDate>
#include <QDateTime>
#include <QPainter>

#include <QDebug>



class DateTimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DateTimeWidget(QWidget *parent = 0);
    ~DateTimeWidget();

private:
    QLabel *m_Time;
    QLabel *m_Date;
    QLabel *m_Week;
    QTimer *m_UpdateTimer;
    QDateTime m_DateTime;


signals:

public slots:
    void UpdateDateTime();
};

#endif // DATETIMEWIDGET_H
