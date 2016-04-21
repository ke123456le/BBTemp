#include <QVBoxLayout>

#include "datetimewidget.h"

DateTimeWidget::DateTimeWidget(QWidget *parent) : QWidget(parent)
{

    m_Time = new QLabel;
    m_Date = new QLabel;
    m_Week = new QLabel;

    QVBoxLayout *m_DateTimeLayout = new QVBoxLayout;
    m_DateTimeLayout->addWidget (m_Time);
    m_DateTimeLayout->addStretch();
    m_DateTimeLayout->addWidget (m_Date);
    m_DateTimeLayout->addStretch();
    m_DateTimeLayout->addWidget (m_Week);
    this->setLayout (m_DateTimeLayout);
    m_DateTimeLayout->addSpacing(1000);

    m_UpdateTimer = new QTimer;

    connect (m_UpdateTimer, SIGNAL(timeout()),this, SLOT(UpdateDateTime()));
    m_UpdateTimer->start (500);
}

DateTimeWidget::~DateTimeWidget()
{
    delete m_Time;
    delete m_Date;
    delete m_Week;
    delete m_UpdateTimer;
}


void DateTimeWidget::UpdateDateTime ()
{
    //qDebug()<<__func__;
    m_DateTime = QDateTime::currentDateTime ();
    QString _Weeks[7] = {"星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期日"};
    //QString _Weeks[7] = {"Monday", "Tuesday", "Wednesday", "Thursday",
    //                     "Friday", "Saturday", "Sunday"};

    //QImage _TimeImage;
    //QPainter painter(&_TimeImage);
    //painter.setPen(Qt::blue);
    //painter.setFont(QFont("Arial", 14));


    //m_Time->setText (QString("%1").arg ((m_DateTime.time ().toString ())));
    //m_Date->setText (QString("%1").arg ((m_DateTime.date ().toString ())));
    //m_Week->setText (QString("%1").arg ((m_DateTime..toString ())));

    QString _TimeString = m_DateTime.time ().toString ();
    QString _DateString = m_DateTime.date().toString ("yyyy-MM-dd");

    //painter.drawText(0,0, _TimeString);
    //m_Time->setFont (QFont("Arial", 36));
    m_Time->setFont (QFont("Microsoft YaHei", 42));

    m_Time->setStyleSheet ("color:#CC66FF");
    //m_Date->setFont (QFont("Arial", 16));
    m_Date->setFont (QFont("Microsoft YaHei", 16));
    //m_Week->setFont (QFont("ukai", 16));
    //m_Week->setFont (QFont("wqy-microhei", 18));
    m_Week->setFont (QFont("Microsoft YaHei", 16));

    m_Date->setStyleSheet ("color:#FFFFFF");
    m_Week->setStyleSheet ("color:#CC66FF");

    m_Time->setAlignment (Qt::AlignCenter);
    m_Date->setAlignment (Qt::AlignCenter);
    m_Week->setAlignment (Qt::AlignCenter);

    m_Time->setText (_TimeString);
    //QPixmap _TextMap = QPixmap::fromImage (_TimeImage);
    //m_Time->setPixmap(_TextMap);
    m_Date->setText (_DateString);

    m_Week->setText (_Weeks[QDate::currentDate ().dayOfWeek ()-1]/*+QString(QStringLiteral("测试"))*/);
   //m_Week->setText (QString("%1").arg(QDate::currentDate ().dayOfWeek ()));
   // qDebug()<<m_Week->text ();
}
