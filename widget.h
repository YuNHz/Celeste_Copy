#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QSoundEffect>
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
    QList<int> mKeyList;

    QList<QGraphicsPixmapItem *> Map;
    QSoundEffect backGroundMusic;

    QTimer * GameTimer;
    QTimer * madelineTimer[10];

private:
    Ui::Widget *ui;
    QGraphicsView mGameView;
    QGraphicsScene mScene,mSceneBack;
    QGraphicsPixmapItem mBackground,mBackgroundBack;
    Madeline * Hero;
    void Game();
    void Collosion();
    inline static bool first = true;
    void Map1();
};
#endif // WIDGET_H


//backGroundMusic[1].setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/mus_lvl2_chase_loop.wav"));
//backGroundMusic[1].setLoopCount(-1);
//backGroundMusic[1].play();
