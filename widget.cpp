#include "Widget.h"
#include "ui_Widget.h"
#include <QPainter>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(1080,608);
    setWindowIcon(QIcon("D:/QTProject/Celeste_Copy/Image/Strawberry.png"));
    setWindowTitle("Welcome to celeste");
    MainInterface = new maininterface(WelcomePlayer);

    WelcomePlayer->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/mus_lvl0_intro_loop.wav"));
    WelcomePlayer->setVolume(0.35f);
    WelcomePlayer->setLoopCount(WelcomePlayer->Infinite);
    WelcomePlayer->play();
    setupWelcomeMovie();
}

void Widget::setupWelcomeMovie()
{
    BackgroundMovie = new QMovie("D:/QTProject/Celeste_Copy/Movie/welcomeinterface.gif");
    BackgroundMovie->setCacheMode(QMovie::CacheAll);
    //BackgroundMovie->setSpeed(100); // 可选：设置视频播放速度

    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setMovie(BackgroundMovie);
    backgroundLabel->setGeometry(0, 0, this->width(), this->height());
    backgroundLabel->lower();
    backgroundLabel->setScaledContents(true);

    BackgroundMovie->start();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_C) {
        PressPlayer->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/ui_main_button_climb.wav"));
        PressPlayer->setVolume(0.35f);
        PressPlayer->setLoopCount(1);
        PressPlayer->play();
        switchToMainInterface();
    }
    // 如果需要，你还可以处理其他键盘事件
}

void Widget::switchToMainInterface(){
    this->hide();
    MainInterface->show();
    connect(MainInterface, &maininterface::returnToWidget, this, &Widget::switchToWidget);
}
void Widget::switchToWidget()
{
    MainInterface->hide();
    this->show();
}

Widget::~Widget()
{
    delete ui;
}


