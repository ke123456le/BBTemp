#ifndef BATAWINDOW_H
#define BATAWINDOW_H

#include <QMainWindow>

namespace Ui {
class BataWindow;
}

class BataWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BataWindow(QWidget *parent = 0);
    ~BataWindow();

private:
    Ui::BataWindow *ui;
};

#endif // BATAWINDOW_H
