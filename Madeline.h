#ifndef MADELINE_H
#define MADELINE_H

#include "GameRectFItem.h"
#include <QKeyEvent>
#include <QSoundEffect>
#include <QTimer>

class Madeline : public GameRectFItem {
    Q_OBJECT
public:
    Madeline(QPointF pos, QObject* parent = nullptr);
    virtual ~Madeline() = default;
    virtual int get_type() override { return 0; }
    void operate(QList<int> & KeyList);
    void update(int backaxis = 0, double fixed = 0); // 1 for x 2 for y
    double& getVx() {return vx;}
    double& getVy() {return vy;}
    bool& flushJump(){return onGround;}
    bool& flushDash(){return canDash;}
    bool ifDash() const{return isDash;}
    std::pair<QPointF,bool> getBadState(){return {{this->pos()},faceRight};}
    void die();
private:
    bool isDead = false;
    int dieGraphicCnt = 0;
    bool canOperator = true;
    bool onGround = true;
    bool faceRight = true;

    inline static constexpr double runAccel = 2880.0;
    inline static constexpr double runReduce = 5760.0;
    inline static constexpr double runMaxSpeed = 288.0; // Run End
    bool canDash = true;
    bool isDash = false;
    int dashUpdateFlash = 150;
    int dashCnt = 1;
    inline static constexpr double dashMaxSpeed = 768.0;
    inline static constexpr double dashEndSpeed = 512.0; // Dash End
    inline static constexpr double gravity = 2560.0;
    inline static constexpr double jumpHBoost = 128.0;
    inline static constexpr double jumpSpeed = -648.0;
    inline static constexpr double maxFall = 768.0;
    inline static constexpr double halfGravCtrl = 128.0; // Jump End

    QSoundEffect* madelinePlayer { new QSoundEffect { this } };
    QTimer* DieTimer = new QTimer(this);
    double vx = 0, vy = 0;

//    virtual void keyPressEvent(QKeyEvent* event) override;
//    virtual void keyReleaseEvent(QKeyEvent* event) override;
//    QList<int> KeyList; // 用于控制Madeline移动

    void moveLeft();
    void moveRight();
    void moveClear();
    void jump(QList<int> & KeyList);
    void dash(QList<int> & KeyList);
    void DieGraphic();
};

#endif // MADELINE_H
