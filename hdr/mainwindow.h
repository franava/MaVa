#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow ;
}
QT_END_NAMESPACE

class QGraphicsPixmapItem ;
class Knight ;
class Witch ;
class Character ;


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr) ;
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event) ;

private slots:
    void onActionAnimationKnightTriggered() ;
    void onActionAnimationWitchTriggered() ;
private:
    Ui::MainWindow* ui_;
    QGraphicsScene* qS_ ;
    Character* k_ ;
    QTimer* timer_ ;
};
#endif // MAINWINDOW_H
