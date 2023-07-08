#include "Madeline.h"

double approach_pos(double current, double target, double step)
{
    if (current < target) {
        return std::min(current + step, target);
    } else {
        return target;
    }
}

double approach_neg(double current, double target, double step)
{
    if (current > target) {
        return std::max(current + step, target);
    } else {
        return target;
    }
}

Madeline::Madeline(QPointF pos, QObject* parent)
    : GameRectFItem { pos, QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Madeline.png").scaled(30, 36), parent }
{
}

void Madeline::moveLeft()
{
    if (vx > 0)
        vx = 0;
    vx = approach_neg(vx, -runMaxSpeed, -runAccel / 1000.0);
    faceRight = false;
}

void Madeline::moveRight()
{
    if (vx < 0)
        vx = 0;
    vx = approach_pos(vx, runMaxSpeed, runAccel / 1000.0);
    faceRight = true;
}

void Madeline::moveClear()
{
    if (vx > 0)
        vx = approach_neg(vx, 0, -runReduce / 1000.0);
    else
        vx = approach_pos(vx, 0, runReduce / 1000.0);
}

void Madeline::jump(QList<int> & KeyList)
{
    if (onGround) {
        if (KeyList.contains(Qt::Key_D)) {
            faceRight = true;
            vx += jumpHBoost;
        } else if (KeyList.contains(Qt::Key_A)) {
            faceRight = false;
            vx -= jumpHBoost;
        }
        vy = jumpSpeed;
        onGround = false;
        madelinePlayer->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/snd_jump.mp3"));
        madelinePlayer->setVolume(1.0f);
        madelinePlayer->play();
    }
}

void Madeline::dash(QList<int> & KeyList)
{
    if (canDash) {
        if (!KeyList.contains(Qt::Key_W) && !KeyList.contains(Qt::Key_S)) {
            if (KeyList.contains(Qt::Key_D)) {
                vx = runMaxSpeed + 3*jumpHBoost;
                faceRight = true;
            } else if (KeyList.contains(Qt::Key_A)) {
                vx = -(runMaxSpeed + 3*jumpHBoost);
                faceRight = false;
            } else if (faceRight)
                vx = runMaxSpeed + 3*jumpHBoost;
            else
                vx = -(dashMaxSpeed);
        } else if (KeyList.contains(Qt::Key_W) && KeyList.contains(Qt::Key_D)) {
            vx = runMaxSpeed + jumpHBoost;
            vy = -dashMaxSpeed;
            faceRight = true;
        } else if (KeyList.contains(Qt::Key_W) && KeyList.contains(Qt::Key_A)) {
            vx = -(runMaxSpeed + jumpHBoost);
            vy = -dashMaxSpeed;
            faceRight = false;
        } else if (KeyList.contains(Qt::Key_W)) {
            vy = -dashMaxSpeed;
        } else if (KeyList.contains(Qt::Key_S) && KeyList.contains(Qt::Key_D)) {
            vx = runMaxSpeed + jumpHBoost;
            vy = dashMaxSpeed;
            faceRight = true;
        } else if (KeyList.contains(Qt::Key_S) && KeyList.contains(Qt::Key_A)) {
            vx = -(runMaxSpeed + jumpHBoost);
            vy = dashMaxSpeed;
            faceRight = false;
        } else if (KeyList.contains(Qt::Key_S)) {
            vy = dashMaxSpeed;
        }
        canOperator = false;
        isDash = true;
        canDash = false;

        if (faceRight)
            setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDashing.png").scaled(30, 24));
        else
            setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDashing.png").scaled(30, 24).transformed(QTransform().scale(-1, 1)));
        madelinePlayer->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/snd_dash.mp3"));
        madelinePlayer->setVolume(1.0f);
        madelinePlayer->play();
    }
}

void Madeline::operate(QList<int> & KeyList)
{
    if (!canOperator)
        return;
    if (KeyList.contains(Qt::Key_L)) {
        dash(KeyList);
        return;
    }
    if (!KeyList.contains(Qt::Key_A) && !KeyList.contains(Qt::Key_D)) {
        moveClear();
    }

    for (int keyCode : KeyList) {
        switch (keyCode) {
        case Qt::Key_K:
            jump(KeyList);
            break;
        case Qt::Key_A:
            moveLeft();
            break;
        case Qt::Key_D:
            moveRight();
            break;
        default:
            break;
        }
    }
}

void Madeline::die()
{
    madelinePlayer->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/snd_dead.mp3"));
    madelinePlayer->setVolume(1.0f);
    madelinePlayer->play();

    isDead = true;
    isDash = false;
    canOperator = false;
    vx /= sqrt(vx * vx + vy * vy);
    vy /= sqrt(vx * vx + vy * vy);


    DieTimer->start(1000 / 1000);
    connect(DieTimer, &QTimer::timeout, this, &Madeline::DieGraphic);
}

void Madeline::DieGraphic()
{
    dieGraphicCnt += 1;
    if (1 <= dieGraphicCnt && dieGraphicCnt <= 30) {
        moveBy(-2.5 * vx, -1.0 * vy);
    }
    if (1 <= dieGraphicCnt && dieGraphicCnt < 60) {
        if (faceRight)
            setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDead0.png").scaled(30, 36));
        else
            setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDead0.png").scaled(30, 36).transformed(QTransform().scale(-1, 1)));
    } else if (60 == dieGraphicCnt) {
        moveBy(-7.5, -4.5);
    } else if (60 < dieGraphicCnt && dieGraphicCnt < 100) {
        setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDead1.png").scaled(45, 45));
    } else if (100 == dieGraphicCnt) {
        moveBy(-22.5, -22.5);
    } else if (100 < dieGraphicCnt && dieGraphicCnt < 200) {
        setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDead2.png").scaled(45 * 2, 45 * 2));
    } else if (200 == dieGraphicCnt) {
        moveBy(-19, -19);
    } else if (1000 <= dieGraphicCnt) {
        dieGraphicCnt = 0;
        DieTimer->stop();
    } else {
        int i = dieGraphicCnt % 300;
        if (0 <= i && i < 100) {
            setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDead3.png").scaled(64 * 2, 64 * 2));
        } else if (100 <= i && i < 200) {
            setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDead4.png").scaled(64 * 2, 64 * 2));
        } else if (200 <= i && i < 300) {
            setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDead5.png").scaled(64 * 2, 64 * 2));
        }
    }
}

void Madeline::update(int backaxis, double fixed)
{
    static QPointF record_pos;
    if (backaxis) {
        if (backaxis & 1)
            setX(fixed);
        if (backaxis & 2)
            setY(fixed);
        return;
    }
    record_pos = pos();
    moveBy(vx / 1000.0, vy / 1000.0);
    if (isDash) {
        if (vy < 0)
            vy = approach_pos(vy, 0, (dashMaxSpeed - dashEndSpeed) / 150.0);
        else
            approach_neg(vy, 0, -(dashMaxSpeed - dashEndSpeed) / 150.0);
        if (dashUpdateFlash > 0)
            dashUpdateFlash -= 1;
        else {
            canOperator = true;
            isDash = false;
            dashUpdateFlash = 150;
        }
    } else {
        double mult = (abs(vy) < halfGravCtrl) ? 0.5 : 1.0;
        vy = approach_pos(vy, maxFall, mult * gravity / 1000.0);
        if (faceRight && canDash)
            setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Madeline.png").scaled(30, 36));
        else if (!faceRight && canDash)
            setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Madeline.png").scaled(30, 36).transformed(QTransform().scale(-1, 1)));
        else if (faceRight && !canDash)
            setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDashed.png").scaled(30, 36));
        else if (!faceRight && !canDash)
            setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDashed.png").scaled(30, 36).transformed(QTransform().scale(-1, 1)));
    }
}
