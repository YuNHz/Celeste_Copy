#include "game.h"
#include "Funobj_Energy.h"
#include "Funobj_Spring.h"
#include "Funobj_Strawberry.h"
#include "Obstacle_Dream.h"
#include "Obstacle_Platform.h"
#include "Obstacle_Spike.h"

#include <QFile>
#include <QPushButton>
#include <QScrollBar>
#include <QThread>

#define DREAM 521
#define SPIKE 540
#define ENERGY 650
#define SPRING 659
#define BADELINE 820
#define PLATFORM 869
#define STRAWBERRY 1109

Game::Game(QObject* parent, const QString& mapName)
    : QObject { parent }
{

    assert(createObstacles("map1"));

    mScene = new QGraphicsScene { 0, 0, Obstacle::length * mapWidth, Obstacle::length * mapHeight, this };
    mGameView = new QGraphicsView { mScene };

    mGameView->setFixedSize(Obstacle::length * viewWidth, Obstacle::length * viewHeight);
    mGameView->setWindowTitle("Celeste_Copy");
    mGameView->setSceneRect(0, 0, mScene->width(), mScene->height());

    mGameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mGameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mGameView->centerOn(0, 0);

    mBackground = new QGraphicsPixmapItem { QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\background2.png").scaled(Obstacle::length * mapWidth, Obstacle::length * mapHeight) };
    mScene->addItem(mBackground);
    mScene->addItem(this);
    for (auto item : RectFMap)
        mScene->addItem(item);
    for (auto item : DreamMap)
        mScene->addItem(item);
    mScene->addItem(Hero);
    for(int i=0;i<5;++i)
        if(Bad[i]!=NULL) mScene->addItem(Bad[i]);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    grabKeyboard();

    if (Bad[0]==NULL)
        BackgroundMusic->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/mus_lvl2_badeline_loop.wav"));
    else
        BackgroundMusic->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/mus_lvl2_chase_loop.wav"));

    BackgroundMusic->setVolume(0.35f);
    BackgroundMusic->setLoopCount(BackgroundMusic->Infinite);
    BackgroundMusic->play();

    GameTimer->start(1000 / 1000);
    connect(GameTimer, &QTimer::timeout, this, [this]() { // 游戏主体connect函数
        Hero->operate(KeyList); // 读取操作
        update(); // 更新状态，检查碰撞

        for(int i=0;i<5;++i)
            if(Bad[i]!=NULL){
                Bad[i]->BadelineVector.pop_front();
                Bad[i]->BadelineVector.push_back(Hero->getBadState());
            }
//        }
    });
}

bool Game::createObstacles(const QString& mapName)
{
    QFile f("D:\\QTProject\\Celeste_Copy\\Maps\\" + mapName);
    if (!f.exists())
        return false;
    f.open(QIODevice::ReadOnly);
    QTextStream stream(&f);
    stream >> mapWidth >> mapHeight
        >> viewWidth >> viewHeight
        >> savePoint.rx() >> savePoint.ry();
    int badcnt,badtime;
    stream >> badcnt;
    for(int i=0;i<badcnt;++i){
        stream >> badtime;
        Bad[i] = new Badeline {badtime};
    }
    stream.readLine();
    for (int i = 0; i < mapHeight; ++i) {
        auto linec = stream.readLine();
        for (int j = 0; j < mapWidth; ++j)
            switch (linec[j].toLatin1()) {
            case 'b':
                RectFMap.emplace_back(new Platform { { j * Obstacle::length, i * Obstacle::length } });
                break;
            case 'd': // dream
                RectFMap.emplace_back(new Dream { { j * Obstacle::length, i * Obstacle::length } });
                break;
            case 'q': // spike1
                RectFMap.emplace_back(new Spike { { j * Obstacle::length, i * Obstacle::length }, 1 });
                break;
            case 'w': // spike2
                RectFMap.emplace_back(new Spike { { j * Obstacle::length, i * Obstacle::length+9 }, 2 });
                break;
            case 'e': // spike3
                RectFMap.emplace_back(new Spike { { j * Obstacle::length, i * Obstacle::length }, 3 });
                break;
            case 'r': // spike4
                RectFMap.emplace_back(new Spike { { j * Obstacle::length, i * Obstacle::length }, 4 });
                break;
            case 'y': // energe
                RectFMap.emplace_back(new Energy { { j * Obstacle::length, i * Obstacle::length } });
                break;
            case 's': // spring
                RectFMap.emplace_back(new Spring { { j * Obstacle::length, i * Obstacle::length + 15} });
                break;
            case 'p': // strawberry
                Strawberry * s = new Strawberry { { j * Obstacle::length, i * Obstacle::length } };
                s->StrawberryTimer->start(1000/8);
                RectFMap.emplace_back(s);
                break;
            }
    }
    f.close();

    Hero = new Madeline { savePoint,this };

    return true;
}

void Game::show()
{
    BackgroundMusic->play();
    mGameView->show();
}

void Game::hide()
{
    GameTimer->stop();
    BackgroundMusic->stop();
    mGameView->hide();
}

void Game::checkCollision()
{
    auto rchero = Hero->boundingRect();
    rchero.moveTopLeft(Hero->pos());
    int x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
        y1 = rchero.y(), y2 = rchero.y() + rchero.height();

    if (x1> mapWidth * Obstacle::length) {
        BackgroundMusic->stop();
        emit GoodGame();
        return;
    }
        for(int i=0;i<5;++i)
        if(Bad[i]!=NULL){
            Bad[i]->setPos(Bad[i]->BadelineVector[0].first);
            if(Bad[i]->BadelineVector[0].second)
                Bad[i]->setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Badeline.png").scaled(Badeline::length,Badeline::width));
            else
                Bad[i]->setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Badeline.png").scaled(Badeline::length,Badeline::width).transformed(QTransform().scale(-1, 1)));
            auto rc = Bad[i]->boundingRect();
            rc.moveTopLeft(Bad[i]->pos());
            if ((rc.contains(x1 + 1, y1) or rc.contains(x2 - 1, y1) or rc.contains((x1 + 2 * x2) / 3.0, y1) or rc.contains((2 * x1 + x2) / 3.0, y1))
                or (rc.contains(x1, y1 + 1) or rc.contains(x1, y2 - 1) or rc.contains(x1, (y1 + 2 * y2) / 3.0) or rc.contains(x1, (2 * y1 + y2) / 3.0))
                or (rc.contains(x2, y1 + 1) or rc.contains(x2, y2 - 1) or rc.contains(x2, (y1 + 2 * y2) / 3.0) or rc.contains(x2, (2 * y1 + y2) / 3.0))
                or (rc.contains(x1 + 1, y2) or rc.contains(x2 - 1, y2) or rc.contains((x1 + 2 * x2) / 3.0, y2) or rc.contains((2 * x1 + x2) / 3.0, y2))) {
                RestartGame();
                return;
            }
        }
//    }
    if (!RectFMap.empty()) {
        for (auto item : RectFMap) {
            auto rc = item->boundingRect();
            rc.moveTopLeft(item->pos());
            switch (item->get_type()) {
            case DREAM:
                // top
                if ((rc.contains(x1 + 1, y1) or rc.contains(x2 - 1, y1)
                     or rc.contains((x1 + 2 * x2) / 3.0, y1) or rc.contains((2 * x1 + x2) / 3.0, y1))
                    and Hero->getVy() < 0 and Hero->ifDash()) {
                    Hero->update(2, rc.y() - rchero.height());
                    rchero = Hero->boundingRect();
                    rchero.moveTopLeft(Hero->pos());
                    x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
                        y1 = rchero.y(), y2 = rchero.y() + rchero.height();
                    TmpMusic->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/snd_dream.wav"));
                    TmpMusic->setVolume(1.0f);
                    TmpMusic->play();
                    Hero->flushDash() = true;
                }
                // left
                if ((rc.contains(x1, y1 + 1) or rc.contains(x1, y2 - 1)
                     or rc.contains(x1, (y1 + 2 * y2) / 3.0) or rc.contains(x1, (2 * y1 + y2) / 3.0))
                    and Hero->getVx() < 0 and Hero->ifDash()) {
                    Hero->update(1, rc.x() - rchero.width()); // 更新Hero位置状态
                    rchero = Hero->boundingRect();
                    rchero.moveTopLeft(Hero->pos());
                    x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
                        y1 = rchero.y(), y2 = rchero.y() + rchero.height();
                    TmpMusic->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/snd_dream.wav"));
                    TmpMusic->setVolume(1.0f);
                    TmpMusic->play();
                    Hero->flushDash() = true;
                }
                // right
                if ((rc.contains(x2, y1 + 1) or rc.contains(x2, y2 - 1)
                     or rc.contains(x2, (y1 + 2 * y2) / 3.0) or rc.contains(x2, (2 * y1 + y2) / 3.0))
                    and Hero->getVx() > 0 and Hero->ifDash()) {
                    Hero->update(1, rc.x()+rc.width());
                    rchero = Hero->boundingRect();
                    rchero.moveTopLeft(Hero->pos());
                    x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
                        y1 = rchero.y(), y2 = rchero.y() + rchero.height();
                    TmpMusic->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/snd_dream.wav"));
                    TmpMusic->setVolume(1.0f);
                    TmpMusic->play();
                    Hero->flushDash() = true;
                }
                // down
                if ((rc.contains(x1 + 1, y2) or rc.contains(x2 - 1, y2)
                     or rc.contains((x1 + 2 * x2) / 3.0, y2) or rc.contains((2 * x1 + x2) / 3.0, y2))
                    and Hero->getVy() > 0 and Hero->ifDash()) {
                    Hero->update(2, rc.y()+rc.height());
                    rchero = Hero->boundingRect();
                    rchero.moveTopLeft(Hero->pos());
                    x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
                        y1 = rchero.y(), y2 = rchero.y() + rchero.height();
                    TmpMusic->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/snd_dream.wav"));
                    TmpMusic->setVolume(1.0f);
                    TmpMusic->play();
                    Hero->flushDash() = true;
                }
                // top
                if ((rc.contains(x1 + 1, y1) or rc.contains(x2 - 1, y1)
                     or rc.contains((x1 + 2 * x2) / 3.0, y1) or rc.contains((2 * x1 + x2) / 3.0, y1))
                    and Hero->getVy() < 0) {
                    Hero->getVy() = 0;
                    Hero->update(2, rc.y() + rc.height());
                    rchero = Hero->boundingRect();
                    rchero.moveTopLeft(Hero->pos());
                    x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
                        y1 = rchero.y(), y2 = rchero.y() + rchero.height();
                }
                // left
                if ((rc.contains(x1, y1 + 1) or rc.contains(x1, y2 - 1)
                     or rc.contains(x1, (y1 + 2 * y2) / 3.0) or rc.contains(x1, (2 * y1 + y2) / 3.0))
                    and Hero->getVx() < 0) {
                    Hero->getVx() = 0;
                    Hero->update(1, rc.x() + rc.width() + 3); // 更新Hero位置状态
                    rchero = Hero->boundingRect();
                    rchero.moveTopLeft(Hero->pos());
                    x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
                        y1 = rchero.y(), y2 = rchero.y() + rchero.height();
                }
                // right
                if ((rc.contains(x2, y1 + 1) or rc.contains(x2, y2 - 1)
                     or rc.contains(x2, (y1 + 2 * y2) / 3.0) or rc.contains(x2, (2 * y1 + y2) / 3.0))
                    and Hero->getVx() > 0) {
                    Hero->getVx() = 0;
                    Hero->update(1, rc.x() - rchero.width());
                    rchero = Hero->boundingRect();
                    rchero.moveTopLeft(Hero->pos());
                    x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
                        y1 = rchero.y(), y2 = rchero.y() + rchero.height();
                }
                // down
                if ((rc.contains(x1 + 1, y2) or rc.contains(x2 - 1, y2)
                     or rc.contains((x1 + 2 * x2) / 3.0, y2) or rc.contains((2 * x1 + x2) / 3.0, y2))
                    and Hero->getVy() > 0) {
                    Hero->getVy() = 0;
                    Hero->update(2, rc.y() - rchero.height());
                    rchero = Hero->boundingRect();
                    rchero.moveTopLeft(Hero->pos());
                    x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
                        y1 = rchero.y(), y2 = rchero.y() + rchero.height();

                    Hero->flushJump() = true;
                    Hero->flushDash() = true;
                }
                break;
            case SPIKE:
                switch (((Spike*)item)->get_direct()) {
                case 1:
                    if ((rc.contains(x1 + 1, y1) or rc.contains(x2 - 1, y1) or rc.contains((x1 + 2 * x2) / 3.0, y1) or rc.contains((2 * x1 + x2) / 3.0, y1)) and Hero->getVy() < 0) {
                        RestartGame();
                        return;
                    }
                    break;
                case 2:
                    if ((rc.contains(x1 + 1, y2) or rc.contains(x2 - 1, y2) or rc.contains((x1 + 2 * x2) / 3.0, y2) or rc.contains((2 * x1 + x2) / 3.0, y2)) and Hero->getVy() > 0) {
                        RestartGame();
                        return;
                    }
                    break;
                case 3:
                    if ((rc.contains(x2, y1 + 1) or rc.contains(x2, y2 - 1) or rc.contains(x2, (y1 + 2 * y2) / 3.0) or rc.contains(x2, (2 * y1 + y2) / 3.0)) and Hero->getVx() > 0) {
                        RestartGame();
                        return;
                    }
                    break;
                case 4:
                    if ((rc.contains(x1, y1 + 1) or rc.contains(x1, y2 - 1) or rc.contains(x1, (y1 + 2 * y2) / 3.0) or rc.contains(x1, (2 * y1 + y2) / 3.0)) and Hero->getVx() < 0) {
                        RestartGame();
                        return;
                    }
                    break;
                }
                break;
            case SPRING:
                if ((rc.contains(x1 + 1, y2) or rc.contains(x2 - 1, y2)
                     or rc.contains((x1 + 2 * x2) / 3.0, y2) or rc.contains((2 * x1 + x2) / 3.0, y2))
                    and Hero->getVy() > 0) {
                    Hero->getVy() = -768.0;
                    Hero->update(2, rc.y() - rchero.height());
                    rchero = Hero->boundingRect();
                    rchero.moveTopLeft(Hero->pos());
                    x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
                        y1 = rchero.y(), y2 = rchero.y() + rchero.height();
                    item->moveBy(0,-9);
                    item->setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Spring2.png").scaled(24,18));
                    QTimer::singleShot(100, this, [item]() {
                        item->moveBy(0,9);
                        item->setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Spring1.png").scaled(24,9));
                    });
                    TmpMusic->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/snd_spring.wav"));
                    TmpMusic->setVolume(1.0f);
                    TmpMusic->play();
                    Hero->flushDash() = true;
                }
                break;
            case ENERGY:
                if ((rc.contains(x1 + 1, y1) or rc.contains(x2 - 1, y1) or rc.contains((x1 + 2 * x2) / 3.0, y1) or rc.contains((2 * x1 + x2) / 3.0, y1))
                    or (rc.contains(x1, y1 + 1) or rc.contains(x1, y2 - 1) or rc.contains(x1, (y1 + 2 * y2) / 3.0) or rc.contains(x1, (2 * y1 + y2) / 3.0))
                    or (rc.contains(x2, y1 + 1) or rc.contains(x2, y2 - 1) or rc.contains(x2, (y1 + 2 * y2) / 3.0) or rc.contains(x2, (2 * y1 + y2) / 3.0))
                    or (rc.contains(x1 + 1, y2) or rc.contains(x2 - 1, y2) or rc.contains((x1 + 2 * x2) / 3.0, y2) or rc.contains((2 * x1 + x2) / 3.0, y2))) {
                    RectFMap.removeOne(item);
                    mScene->removeItem(item);
                    Hero->flushDash() = true;
                    QTimer::singleShot(5000, this, [item, this]() {
                        RectFMap.append(item);
                        mScene->addItem(item);
                    });
                    TmpMusic->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/snd_energy.wav"));
                    TmpMusic->setVolume(1.0f);
                    TmpMusic->play();
                }
                break;
            case PLATFORM:
                // top
                if ((rc.contains(x1 + 1, y1) or rc.contains(x2 - 1, y1)
                        or rc.contains((x1 + 2 * x2) / 3.0, y1) or rc.contains((2 * x1 + x2) / 3.0, y1))
                    and Hero->getVy() < 0) {
                    Hero->getVy() = 0;
                    Hero->update(2, rc.y() + rc.height());
                    rchero = Hero->boundingRect();
                    rchero.moveTopLeft(Hero->pos());
                    x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
                    y1 = rchero.y(), y2 = rchero.y() + rchero.height();
                }
                // left
                if ((rc.contains(x1, y1 + 1) or rc.contains(x1, y2 - 1)
                        or rc.contains(x1, (y1 + 2 * y2) / 3.0) or rc.contains(x1, (2 * y1 + y2) / 3.0))
                    and Hero->getVx() < 0) {
                    Hero->getVx() = 0;
                    Hero->update(1, rc.x() + rc.width() + 3); // 更新Hero位置状态
                    rchero = Hero->boundingRect();
                    rchero.moveTopLeft(Hero->pos());
                    x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
                    y1 = rchero.y(), y2 = rchero.y() + rchero.height();
                }
                // right
                if ((rc.contains(x2, y1 + 1) or rc.contains(x2, y2 - 1)
                        or rc.contains(x2, (y1 + 2 * y2) / 3.0) or rc.contains(x2, (2 * y1 + y2) / 3.0))
                    and Hero->getVx() > 0) {
                    Hero->getVx() = 0;
                    Hero->update(1, rc.x() - rchero.width());
                    rchero = Hero->boundingRect();
                    rchero.moveTopLeft(Hero->pos());
                    x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
                    y1 = rchero.y(), y2 = rchero.y() + rchero.height();
                }
                // down
                if ((rc.contains(x1 + 1, y2) or rc.contains(x2 - 1, y2)
                        or rc.contains((x1 + 2 * x2) / 3.0, y2) or rc.contains((2 * x1 + x2) / 3.0, y2))
                    and Hero->getVy() > 0) {
                    Hero->getVy() = 0;
                    Hero->update(2, rc.y() - rchero.height());
                    rchero = Hero->boundingRect();
                    rchero.moveTopLeft(Hero->pos());
                    x1 = rchero.x(), x2 = rchero.x() + rchero.width(),
                    y1 = rchero.y(), y2 = rchero.y() + rchero.height();

                    Hero->flushJump() = true;
                    Hero->flushDash() = true;
                }
                break;
            case STRAWBERRY:
                if ((rc.contains(x1 + 1, y1) or rc.contains(x2 - 1, y1) or rc.contains((x1 + 2 * x2) / 3.0, y1) or rc.contains((2 * x1 + x2) / 3.0, y1))
                    or (rc.contains(x1, y1 + 1) or rc.contains(x1, y2 - 1) or rc.contains(x1, (y1 + 2 * y2) / 3.0) or rc.contains(x1, (2 * y1 + y2) / 3.0))
                    or (rc.contains(x2, y1 + 1) or rc.contains(x2, y2 - 1) or rc.contains(x2, (y1 + 2 * y2) / 3.0) or rc.contains(x2, (2 * y1 + y2) / 3.0))
                    or (rc.contains(x1 + 1, y2) or rc.contains(x2 - 1, y2) or rc.contains((x1 + 2 * x2) / 3.0, y2) or rc.contains((2 * x1 + x2) / 3.0, y2))) {
                    RectFMap.removeOne(item);
                    Strawberry* tmpIt = (Strawberry*)item;
                    tmpIt->StrawberryTimer->stop();
                    item->setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\1up.png").scaled(48, 24));
                    TmpMusic->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/snd_strawberry.wav"));
                    TmpMusic->setVolume(1.0f);
                    TmpMusic->play();
                    QTimer::singleShot(1000, this, [item, this] {
                        mScene->removeItem(item);
                    });
                }
                break;
            }
        }
    }
}

void Game::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_A:
        if (KeyList.contains(Qt::Key_D))
            KeyList.removeOne(Qt::Key_D);
        KeyList.append(event->key());
        break;
    case Qt::Key_D:
        if (KeyList.contains(Qt::Key_A))
            KeyList.removeOne(Qt::Key_A);
        KeyList.append(event->key());
        break;
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_K:
    case Qt::Key_L:
    case Qt::Key_Z:
        KeyList.append(event->key());
        break;
    case Qt::Key_Escape:
        emit Escape();
        break;
    }
}

void Game::keyReleaseEvent(QKeyEvent* event)
{
    if (KeyList.contains(event->key())) {
        KeyList.removeAll(event->key());
    }
}

void Game::update()
{
    Hero->update(); // 更新Hero位置状态
    Hero->flushJump() = false;
    checkCollision(); // 检查Hero与RectFMap发生的碰撞，并进行处理，与地面碰撞赋予flushJump()
    if(CameraCnt>5){
        CameraCnt = 0;
        mGameView->centerOn(Hero->x()+Hero->boundingRect().width()/2, Hero->y());
    }
    CameraCnt += 1;
}

void Game::RestartGame()
{
    Hero->die();
    GameTimer->stop();
    QTimer::singleShot(1000,this,[this](){
        Hero->deleteLater();
        mScene->removeItem(Hero);
        for(int i=0;i<5;++i){
            if(Bad[i]!=NULL) mScene->removeItem(Bad[i]);
        }
        GameTimer->start(1000/1000);
        Hero = new Madeline { savePoint };
        for(int i=0;i<5;++i){
            if(Bad[i]!=NULL){
                Badeline * tmp = Bad[i];
                Bad[i] = new Badeline{Bad[i]->time};
                delete tmp;
                mScene->addItem(Bad[i]);
            }
        }
        mScene->addItem(Hero);
    });
}

