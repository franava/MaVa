#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow ;
}
QT_END_NAMESPACE

class QGraphicsPixmapItem ;
class Character ;


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr) ;
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event) ;

private slots:
    void onActionAnimationTriggered() ;

private:
    Ui::MainWindow* ui_;
    QGraphicsScene* qS_ ;
    Character* c_ ;
    QTimer* timer_ ;
};
#endif // MAINWINDOW_H
