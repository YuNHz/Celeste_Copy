#ifndef GAME_H
#define GAME_H

#include "GameRectFItem.h"
#include "Madeline.h"
#include "Obstacle_Badeline.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>

#include <QProcess>

class Game : public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Game(QObject* parent = nullptr, const QString& mapName = "default");
    virtual ~Game() = default;
    void show();
    void hide();
signals:
    void GoodGame();
    void Escape();
private:
    bool createObstacles(const QString& mapName); // 从文本读入地图
    void checkCollision(); // 检查Madeline与RectFMap的碰撞情况并处理
    QList<GameRectFItem*> RectFMap; // 碰撞箱Map，用于brick、Spike等碰撞判定
    QList<GameRectFItem*> DreamMap; // 碰撞箱Map，用于Dream碰撞冲刺穿过判定
    QPointF savePoint;
    int CameraCnt = 0;
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;
    QList<int> KeyList; // 用于控制Madeline移动
    void update(); // 游戏主体，帧刷新函数，与GameTimer connect
    Madeline* Hero;
    Badeline* Bad[5] = {NULL,NULL,NULL,NULL,NULL};

    QTimer* GameTimer { new QTimer { this } };
    QTimer* TmpTimer { new QTimer { this } };

    QSoundEffect* BackgroundMusic { new QSoundEffect { this } };
    QSoundEffect* TmpMusic { new QSoundEffect { this } };

    QGraphicsView* mGameView;
    QGraphicsScene* mScene;
    QGraphicsPixmapItem* mBackground;
    int mapWidth, mapHeight, viewWidth, viewHeight;

    void RestartGame();
};

#endif // GAME_H
