#ifndef BCAMERAVIEW_H
#define BCAMERAVIEW_H

#include <QWidget>
#include <QEvent>
#include <QVideoFrame>
#include <QMutex>
#include <QLabel>

#include "bcamera_p.h"

class BCameraWidgetPrivate;
class BCameraWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BCameraWidget(QWidget *parent = 0);
    ~BCameraWidget();

    bool clearAndFillBlock();
    bool presentImage(const QImage __image, bool isMirrored);

signals:
    void widgetResize(QSize size);

public slots:

protected:
    //void paintEvent (QPaintEvent *event);
    void resizeEvent (QResizeEvent * event);

    BCameraWidgetPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(BCameraWidget)
    QImage m_image;
    QMutex imageLock;
    QLabel *showLabel;
};

#endif // BCAMERAVIEW_H
