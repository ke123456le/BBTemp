#include "loadsplash.h"

LoadSplash::LoadSplash(const QPixmap &map):finishProgressBar(0),
    msgLabel(0),progressLabel(0)
{
    msgLabel = new QLabel();
    progressLabel = new QLabel();
    finishProgressBar = new QProgressBar();

    setPixmap (map);
}

LoadSplash::~LoadSplash()
{
    if (msgLabel)
        delete msgLabel;
    if (progressLabel)
        delete progressLabel;
    if (finishProgressBar)
        delete finishProgressBar;
}



/*
 *
 */
void LoadSplash::showMessage (const QString & msg, int percentValue)
{

}


void LoadSplash::showMessage (const QString & msg)
{

}
