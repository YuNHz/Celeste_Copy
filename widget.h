#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include "madeline.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void PlaneMove();
    QList<int> mKeyList;
    QTimer* madelineTimer;
private:
    Ui::Widget *ui;

    QGraphicsView mGameView;
    QGraphicsScene mScene;
    QGraphicsPixmapItem mBackground;
    Madeline Hero;
};
#endif // WIDGET_H
