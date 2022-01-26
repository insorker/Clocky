#ifndef RESIZABLESTACKEDWIDGET_H
#define RESIZABLESTACKEDWIDGET_H

#include <QStackedWidget>
#include <QDebug>

class ResizableStackedWidget : public QStackedWidget
{
    Q_OBJECT

public:
    ResizableStackedWidget(QWidget *parent = nullptr)
        : QStackedWidget(parent)
    {
        connect(this, &ResizableStackedWidget::currentChanged,
                this, &ResizableStackedWidget::onCurrentChanged);
    }

    void addWidget(QWidget* pWidget)
    {
        pWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        QStackedWidget::addWidget(pWidget);
    }

private slots:
    void onCurrentChanged(int index)
    {
       QWidget* pWidget = widget(index);
       Q_ASSERT(pWidget);
       pWidget->adjustSize();
    }
};

#endif // RESIZABLESTACKEDWIDGET_H
