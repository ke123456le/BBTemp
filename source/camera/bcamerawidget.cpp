#include "bcamerawidget.h"
#include <QPainter>

#include <QDebug>

BCameraWidget::BCameraWidget(QWidget *parent) : QWidget(parent)
{
    showLabel = new QLabel(this);
    showLabel->setGeometry (this->rect ());

    QPixmap tmpPixMap = QPixmap(showLabel->size ());
    tmpPixMap.fill (Qt::black);
    showLabel->setPixmap (tmpPixMap);
}

BCameraWidget::~BCameraWidget()
{
    if (showLabel)
        delete showLabel;
}


#if 0
void BCameraWidget::paintEvent (QPaintEvent *event)
{

    Q_D(BCameraWidget);
    /*if (d->m_frame.isMapped ()){
        ;
    }
    */
    QPainter painter(this);
    //painter.fillRect (this->rect (), Qt::black);
    if (m_image.isNull ()){
        painter.fillRect (this->rect (), Qt::black);
    }else{
        //qDebug()<<__func__<<"drawImage";
        imageLock.lock ();
        painter.drawImage (this->rect (), m_image);
        imageLock.unlock ();
        //qDebug()<<__func__<<"drawImage";
    }

}
#endif

void BCameraWidget::resizeEvent (QResizeEvent * event)
{
    if (showLabel){
        showLabel->setGeometry (0, 0, this->size ().width (), this->size ().height ());
    }

    //emit widgetResize(this->size ());
}

#include <QObject>
bool BCameraWidget::clearAndFillBlock()
{
    QPixmap tmpPixMap = QPixmap(showLabel->size ());
    tmpPixMap.fill (Qt::black);
    showLabel->setPixmap (tmpPixMap);
}

bool BCameraWidget::presentImage(const QImage __image, bool isMirrored)
{
    //qDebug()<<__func__;
    //imageLock.lock ();
    //m_image = __image;
    //imageLock.unlock ();
    //repaint ();
    if (isMirrored)
        showLabel->setPixmap (QPixmap().fromImage (__image.mirrored (true, false).scaled (this->size ())));
    else
        showLabel->setPixmap (QPixmap().fromImage (__image).scaled (this->size ()));
}
