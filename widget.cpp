#include "widget.h"
#include <QMouseEvent>

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground, true);

    trayInit();
    sideBarInit();
    stkWidgetInit();

    // 最小化到托盘
    sideBar->addOption(QColor(93, 190, 138), "minimize", "最小化");
    connect(sideBar->options[0], &SideBarOption::clicked, showAct, &QAction::toggle);
    // 时钟
    digitalclock = new DigitalClock(stkWidget);
    addOption(QColor(240, 124, 130), "clock.png", "时钟", digitalclock);
    // 搜索
    search = new Search(stkWidget);
    addOption(QColor(240, 124, 130), "search.png", "搜索", search);

    sideBar->addOption(QColor(0, 0, 255), "setting.png", "设置");

    sideBar->alignOption();
}

void Widget::enterEvent(QEvent *)
{
    sideBar->showAnimation();
}

void Widget::leaveEvent(QEvent *)
{
    sideBar->dispearAnimation();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    m_move = true;

    if (m_move) {
        m_startPoint = event->globalPos();
        m_windowPoint = this->frameGeometry().topLeft();
    }
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_move) {
        QPoint relativePos = event->globalPos() - m_startPoint;
        this->move(m_windowPoint + relativePos);
    }
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_move = false;
    }
}

void Widget::addOption(QColor bgColor, QString icon, QString name, QWidget* widget)
{
    sideBar->addOption(bgColor, icon, name);
    stkWidget->addWidget(widget);
    stkWidgetConnect(widget, name);
}

void Widget::trayInit()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon("://img/trayicon/Eevee.png"));
    trayIcon->setToolTip("Clocky");
    trayIcon->show();
    connect(trayIcon, &QSystemTrayIcon::activated, this, &Widget::showWidget);

    showAct = new QAction("显示", this);
    showAct->setCheckable(true);
    showAct->setChecked(true);
    connect(showAct, &QAction::toggled, this,
            [=]() { if (showAct->isChecked()) show(); else hide(); });
    topAct = new QAction("置顶", this);
    topAct->setCheckable(true);
    topAct->setChecked(false);
    connect(topAct, &QAction::toggled, this,
            [=]() {
        if (topAct->isChecked())
            setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
        else
            setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
        showAct->setChecked(false);
        showAct->setChecked(true);
    });
    quitAct = new QAction("退出", this);
    connect(quitAct, &QAction::triggered, this, [=](){ exit(0); });

    trayMenu = new QMenu(this);
    trayMenu->addAction(showAct);
    trayMenu->addAction(topAct);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAct);
    trayIcon->setContextMenu(trayMenu);
}

void Widget::sideBarInit()
{
    sideBar = new SideBar(this);
    sideBar->move(0, 0);

    connect(sideBar, &SideBar::alignChanged, this,
            [=]() {
        if (sideBar->height() >= 100)
            resize(width(),
                   qMax(sideBar->height(), stkWidget->height()) + 10);
    });
}

void Widget::showWidget(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:
        break;
    case QSystemTrayIcon::DoubleClick:
        this->showNormal();
        break;
    default:
        break;
    }
}

void Widget::stkWidgetInit()
{
    stkWidget = new ResizableStackedWidget(this);
    stkWidget->move(sideBar->width(), 0);

    connect(stkWidget, &ResizableStackedWidget::currentChanged, this,
            [=]() {
        stkWidget->resize(stkWidget->currentWidget()->width(),
                          stkWidget->currentWidget()->height());
        resize(sideBar->width() + stkWidget->width() + 10,
               qMax(sideBar->height(), stkWidget->height()) + 10);
    });
}

void Widget::stkWidgetConnect(QWidget *currentWidget, QString SideBarOptionName)
{
    for (auto& opt : sideBar->options) {
        if (opt->getName() == SideBarOptionName) {
            connect(opt, &SideBarOption::clicked, stkWidget,
                    [=]() { stkWidget->setCurrentWidget(currentWidget); });
            break;
        }
    }
}
