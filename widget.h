#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QtAlgorithms>
#include "sidebar.h"
#include "resizablestackedwidget.h"
#include "digitalclock.h"
#include "search.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    void addOption(QColor bgColor, QString icon, QString tip, QWidget* widget);

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    SideBar *sideBar;
    ResizableStackedWidget *stkWidget;

    QMenu *trayMenu;
    QAction *showAct;
    QAction *topAct;
    QAction *quitAct;
    QSystemTrayIcon *trayIcon;
    DigitalClock *digitalclock;
    Search *search;

    //窗口移动
    bool m_move = false;
    QPoint m_startPoint;
    QPoint m_windowPoint;

    void showWidget(QSystemTrayIcon::ActivationReason reason);
    void trayInit();
    void sideBarInit();
    void stkWidgetInit();
    void stkWidgetConnect(QWidget *currentWidget, QString SideBarOptionName);
};

#endif // WIDGET_H
