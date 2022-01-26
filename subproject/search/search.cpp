#include "search.h"
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QKeyEvent>
#include <QApplication>

#include <QDebug>

Search::Search(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(350, 40);

    lineEdit = new QLineEdit(this);
    lineEdit->setGeometry(50, 0, 300, 40);

    enter = new QComboBox(this);
    enter->setGeometry(0, 0, 50, 40);

    enter->addItem(QIcon("://img/baidu.png"), "百度");
    enter->addItem(QIcon("://img/google.png"), "谷歌");
    enter->addItem(QIcon("://img/local.png"), "本地");

    QFile file("://search.qss");
    file.open(QFile::ReadOnly);
    qApp->setStyleSheet(file.readAll());
    file.close();
}

void Search::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Return:
            search(enter->currentText());
            break;
    }
}

void Search::search(QString item)
{
    bool success = true;
    if (item == "百度") {
        success = QDesktopServices::openUrl(QUrl(
            "https://www.baidu.com/s?&wd=" + lineEdit->text())
        );
    }
    else if (item == "谷歌") {
        success = QDesktopServices::openUrl(QUrl(
            "https://www.google.com/search?&q=" + lineEdit->text())
        );
    }
    else if (item == "本地") {
        success = QDesktopServices::openUrl(QUrl(
            lineEdit->text())
        );
    }

    if (success == false) {
        QMessageBox::warning(this, "File Not Found",
                             QString("%1 cannot be found!").arg(lineEdit->text()));
    }
}
