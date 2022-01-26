#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QAction>
#include <QMenu>

class Search : public QWidget
{
    Q_OBJECT
public:
    Search(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QLineEdit *lineEdit;
    QComboBox *enter;

    void search(QString item);
};
#endif // SEARCH_H
