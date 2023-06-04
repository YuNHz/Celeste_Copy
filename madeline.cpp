#include "madeline.h"

double approach_pos(double current, double target, double step) {
    if (current < target) {
        return std::min(current + step, target);
    } else {
        return target;
    }
}

double approach_neg(double current, double target, double step) {
    if (current > target) {
        return std::max(current + step, target);
    } else {
        return target;
    }
}

Madeline::Madeline(double startX,double startY,int tmp)
{
    m_tmp = tmp;
    x = startX; y = startY;
    vx = 0; vy = 0;
    setPos(startX,startY);
    setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Madeline.png").scaled(40,48));
}

Madeline::~Madeline(){
//    setPixmap(QPixmap())
}

void Madeline::moveLeft(){
    if(vx>0) vx = 0;
    vx = approach_neg(vx,-runMaxSpeed,-runAccel/60.0);
    faceRight = false;
}

void Madeline::moveRight(){
    if(vx<0) vx = 0;
    vx = approach_pos(vx,runMaxSpeed,runAccel/60.0);
    faceRight = true;
}

void Madeline::moveClear(){
    vx = 0;
}

//void Madeline::duck(){isDuck = true;}

//void Madeline::notduck(){isDuck = false;}

void Madeline::graphics(){
    graphicsFlag = faceRight + 2*(dashUpdateFlash!=9) + 4*(1-canDash);
    switch(graphicsFlag){
    case 0: setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Madeline.png").scaled(40,48).transformed(QTransform().scale(-1,1)));
        break;
    case 1: setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Madeline.png").scaled(40,48));
        break;
    case 6: setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDashing.png").scaled(50,36).transformed(QTransform().scale(-1,1)));
        break;
    case 7: setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDashing.png").scaled(50,36));
        break;
    case 4: setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDashed.png").scaled(40,48).transformed(QTransform().scale(-1,1)));
        break;
    case 5: setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDashed.png").scaled(40,48));
        break;
    default:
        break;
    }
}

void Madeline::jump(const QList<int>& KeyList){
    if(onGround){
        if(KeyList.contains(Qt::Key_D)) vx += jumpHBoost;
        else if(KeyList.contains(Qt::Key_A)) vx -= jumpHBoost;
        vy = jumpSpeed;
        onGround = false;
        player->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/snd_jump.mp3"));
        player->play();
    }
}

void Madeline::climb(const QList<int>& KeyList){}

void Madeline::dash(const QList<int>& KeyList){
    if(canDash){
        if(!KeyList.contains(Qt::Key_W)&&!KeyList.contains(Qt::Key_S)){
            if(KeyList.contains(Qt::Key_D)){
                vx = dashMaxSpeed;
                faceRight = true;
            }
            else if(KeyList.contains(Qt::Key_A)){
                vx = -(dashMaxSpeed);
                faceRight = false;
            }
            else if(faceRight) vx = dashMaxSpeed;
            else vx = -(dashMaxSpeed);
        }
        else if(KeyList.contains(Qt::Key_W)&&KeyList.contains(Qt::Key_D)){
            vx = runMaxSpeed+jumpHBoost;
            vy = -dashMaxSpeed;
            faceRight = true;
        }
        else if(KeyList.contains(Qt::Key_W)&&KeyList.contains(Qt::Key_A)){
            vx = -(runMaxSpeed+jumpHBoost);
            vy = -dashMaxSpeed;
            faceRight = false;
        }
        else if(KeyList.contains(Qt::Key_W)){
            vy = -dashMaxSpeed;
        }
        else if(KeyList.contains(Qt::Key_S)&&KeyList.contains(Qt::Key_D)){
            vx = runMaxSpeed+jumpHBoost;
            vy = dashMaxSpeed;
            faceRight = true;
        }
        else if(KeyList.contains(Qt::Key_S)&&KeyList.contains(Qt::Key_A)){
            vx = -(runMaxSpeed+jumpHBoost);
            vy = dashMaxSpeed;
            faceRight = false;
        }
        else if(KeyList.contains(Qt::Key_S)){
            vy = dashMaxSpeed;
        }
        canOperator = false;
        canDash = false;

        player->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/snd_dash.mp3"));
        player->play();
    }
}

void Madeline::operate(const QList<int>& KeyList)
{
    //若处于dash，则Madeline不可控
    if(KeyList.contains(Qt::Key_X)) dash(KeyList);
    if(!canOperator){
        dashupdate();
        if(dashUpdateFlash>0) dashUpdateFlash -= 1;
        else{
            canOperator = true;
            dashUpdateFlash = 9;
        }
        return;
    }
    //dash End

    if(!KeyList.contains(Qt::Key_A)&&!KeyList.contains(Qt::Key_D)){
        moveClear();
    }
    //无移动方向输入，清空水平速度

//    if(KeyList.contains(Qt::Key_Z)){
//        climb(KeyList);
//        climbupdate();
//        return;
//    }

//    if(KeyList.length()==1&&KeyList.contains(Qt::Key_S)) duck();
//    else notduck();
//    //下蹲判定

    for(int keyCode:KeyList){
        switch(keyCode){
        case Qt::Key_A:     moveLeft();break;
        case Qt::Key_D:     moveRight();break;
        case Qt::Key_C:     jump(KeyList);break;
        default:            break;
        }
    }

    // Update pixmap position and check Collision
    update();
}

void Madeline::update(){
    x += vx / 60.0;
    y += vy / 60.0;
    double mult = (abs(vy) < halfGravCtrl) ? 0.5:1.0;
    vy = approach_pos(vy, maxFall, mult*gravity/60.0);
//    if(BoxCollision) reUpdate(x,y);
    if(m_tmp){
        if(y>420){
            y = 420;
            onGround = true;
            canDash = true;
            vy = 0;
        }
    }
    else{
    if(0<=x&&x<=120&&y>540-120-48){
        y = 540-120-48;
        onGround = true;
        canDash = true;
        vy = 0;
    }
    else if(120<x&&x<=240&&y>540-24*2-48){
        y = 540-24*2-48;
        onGround = true;
        canDash = true;
        vy = 0;
        die();
    }
    else if(240<x&&x<=312&&y>540-24*7-48){
        y = 540-24*7-48;
        onGround = true;
        canDash = true;
        vy = 0;
    }
    else if(312<x&&x<=432&&y>540-24*4-48){
        y = 540-24*4-48;
        onGround = true;
        canDash = true;
        vy = 0;
        die();
    }
    else if(432<x&&x<=528&&y>540-24*13-48){
        y = 540-24*13-48;
        onGround = true;
        canDash = true;
        vy = 0;
    }
    else if(528<x&&x<=624&&y>540-24*7-48){
        y = 540-24*7-48;
        onGround = true;
        canDash = true;
        vy = 0;
        die();
    }
    else if(624<x&&x<=696&&y>540-24*3-48){
        y = 540-24*3-48;
        onGround = true;
        canDash = true;
        vy = 0;
        die();
    }
    else if(696<x&&x<=744&&y>540-48){
        y = 540-48;
        onGround = true;
        canDash = true;
        vy = 0;
        die();
    }
    else if(744<x&&x<=864&&y>540-24*16-48){
        y = 540-24*16-48;
        onGround = true;
        canDash = true;
        vy = 0;
    }
    else if(864<x&&x<=888&&y>540-24*21-48){
        y = 540-24*21-48;
        onGround = true;
        canDash = true;
        vy = 0;
    }
    else if(888<x&&x<=1080){
        x = 888;
    }
    else if(x<0){
        x = 0;
    }
    }
//    if(x <= 0 || x >= 960){
//        vx = -vx;
//    }


    setPos(x,y);
    graphics();
}

void Madeline::climbupdate(){}

void Madeline::dashupdate(){

    x += vx/60.0;
    y += vy/60.0;
    if(vy<0) vy = approach_pos(vy,0,(dashMaxSpeed-dashEndSpeed)/9.0);
    else approach_neg(vy,0,-(dashMaxSpeed-dashEndSpeed)/9.0);
//    if(BoxCollision) reUpdate(x,y);


    setPos(x,y);
    graphics();
}

void Madeline::die(){
    Dead = true;
    player->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/snd_dead.mp3"));
    player->play();
}

bool Madeline::isDead(){
    return Dead;
}

void Madeline::deadGraphics(){
    switch(grap){
    case 0:setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDead00.png").scaled(45,51));break;
    case 1:setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDead01.png").scaled(48,45));break;
    case 2:setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDead02.png").scaled(46,50));break;
    case 3:setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDead03.png").scaled(42,44));break;
    case 4:setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\MadelineDead04.png").scaled(56,52));break;
    }
    grap+=1;
}

QRectF Madeline::Box(){
    return QRectF(x+5,y+4,30,40);
}

void Madeline::Reborn(double startX,double startY){

    x = startX; y = startY;
    vx = 0; vy = 0;
    grap = 0;
    onGround = 1;Dead = false;
    canOperator=true;canDash=true;faceRight=true;
    setPos(startX,startY);
    setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Madeline.png").scaled(40,48));
}
