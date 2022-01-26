#include "sidebar.h"
#include <QPainter>

#include <QDebug>

SideBar::SideBar(QWidget *parent)
    : QWidget(parent)
{
    resize(SideBarOption::size + SideBarOption::space * 2, 100);

    opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(1);
    setGraphicsEffect(opacityEffect);

    opacityAnimation = new QPropertyAnimation(opacityEffect, "opacity");
}

void SideBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QColor(128, 118, 163, 40));
    painter.setBrush(QColor(128, 118, 163, 40));
    painter.drawRoundedRect(rect(), SideBarOption::space, SideBarOption::space);
}

void SideBar::addOption(QColor bgColor, QString icon, QString name)
{
    options.push_back(new SideBarOption(bgColor, icon, name, this));
}

void SideBar::alignOption()
{
    resize(SideBarOption::size + SideBarOption::space * 2,
           options.size() * (SideBarOption::size + SideBarOption::space) + SideBarOption::space);

    for (int i = 0; i < options.size(); i ++ ) {
        options[i]->move(SideBarOption::space,
                         i * (SideBarOption::size + SideBarOption::space) + SideBarOption::space);
    }

    emit alignChanged();
}

void SideBar::showAnimation()
{
    opacityAnimation->stop();
    opacityAnimation->setDuration(500);
    opacityAnimation->setStartValue(0);
    opacityAnimation->setEndValue(1);
    opacityAnimation->start();
}

void SideBar::dispearAnimation()
{
    opacityAnimation->stop();
    opacityAnimation->setDuration(2000);
    opacityAnimation->setStartValue(1);
    opacityAnimation->setEndValue(0);
    opacityAnimation->start();
}
