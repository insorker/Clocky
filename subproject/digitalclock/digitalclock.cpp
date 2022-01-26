#include "digitalclock.h"
#include <QTime>
#include <QTimer>
#include <QPalette>

DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent)
{
    setMinimumSize(150, 60);
    setSegmentStyle(Flat);
    setAutoFillBackground(true);

    QPalette palette = this->palette();
    palette.setColor(palette.WindowText, QColor(226, 225, 228));
    palette.setColor(palette.Background, QColor(53, 51, 60));
    this->setPalette(palette);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1000);

    showTime();
}

void DigitalClock::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    display(text);
}
