#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

class SideBarOption : public QPushButton {
public:
    static const int size = 30;
    static const int space = 10;
    static const int scale = 5;

    SideBarOption(QColor bgColor, QString icon, QString name, QWidget *parent = nullptr)
        : QPushButton(parent),
          rx(-1), ry(-1), name(name)
    {
        resize(size, size);

        setStyleSheet(QString(
            "QPushButton{ border-radius:%1; }"
            "QPushButton{ border-image:url(:img/sidebaroption/%2); }"
            "QPushButton{ background-color:rgba(%3,%4,%5,0.95); }"
            "QPushButton:hover{ background-color:rgba(%3,%4,%5,0.7); }"
            "QPushButton:pressed{ background-color:rgba(%3,%4,%5,1); }"
        ).arg("10px", icon)
         .arg(bgColor.red()).arg(bgColor.green()).arg(bgColor.blue()));

        scaleAnimation = new QPropertyAnimation(this, "geometry");
        scaleAnimation->setDuration(100);
    }

    QString getName() { return name; }

protected:
    void enterEvent(QEvent *)
    {
        if (rx == -1 || ry == -1)
            rx = x(), ry = y();

        scaleAnimation->setStartValue(QRect(rx, ry, size, size));
        scaleAnimation->setEndValue(QRect(rx - scale, ry - scale, size + 2 * scale, size + 2 * scale));
        scaleAnimation->start();
    }

    void leaveEvent(QEvent *)
    {
        scaleAnimation->setStartValue(QRect(rx - scale, ry - scale, size + 2 * scale, size + 2 * scale));
        scaleAnimation->setEndValue(QRect(rx, ry, size, size));
        scaleAnimation->start();
    }

private:
//    int idx;
    int rx, ry;
    QString name;
    QPropertyAnimation *scaleAnimation;

//signals:
//    void delOption(int idx);
};

class SideBar : public QWidget
{
    Q_OBJECT

public:
    SideBar(QWidget *parent = nullptr);

    void addOption(QColor bgColor, QString icon, QString name);
//    void delOption();
    void alignOption();
    void showAnimation();
    void dispearAnimation();

public:
    QVector<SideBarOption*> options;

protected:
    void paintEvent(QPaintEvent *event);

private:
    QGraphicsOpacityEffect *opacityEffect;
    QPropertyAnimation *opacityAnimation;

signals:
    void alignChanged();
};

#endif // SIDEBAR_H
