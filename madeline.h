#ifndef MADELINE_H
#define MADELINE_H

#include <QGraphicsPixmapItem>
#include <QSoundEffect>
#include <QTimer>
#include <QList>

class Madeline : public QGraphicsPixmapItem/*public GameObject*/
{
public:
    Madeline(double startX=0.0,double startY=0.0,int tmp=0);
    ~Madeline();
    void moveLeft();
    void moveRight();
    void moveClear();
//    void duck();
//    void notduck();
    void graphics();
    void jump(const QList<int>& KeyList);
    void climb(const QList<int>& KeyList);
    void dash(const QList<int>& KeyList);
    void operate(const QList<int>& KeyList);
    void update();
    void climbupdate();
    void dashupdate();
    void die();
    bool isDead();
    void deadGraphics();
    QRectF Box();
    void Reborn(double x,double y);
    double x,y,vx,vy;
    int m_tmp,grap=0;
private:
    inline static bool onGround=true,isDuck=false,Dead=false,
        canOperator=true,canDash=true,faceRight=true;
    inline static int dashUpdateFlash=9,graphicsFlag=0;
    inline static const double runAccel=2880.0,runReduce=5760.0,runMaxSpeed=288.0,
        dashMaxSpeed=768.0,dashEndSpeed=512.0,
        gravity=2560.0,jumpHBoost=128.0,jumpSpeed=-648.0,maxFall=768.0,halfGravCtrl=128.0;
//    QMediaPlayer * madelinePlayer = new QMediaPlayer;
    QSoundEffect * player = new QSoundEffect;
};

#endif // MADELINE_H
