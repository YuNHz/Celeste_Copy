#include "UI_maininterface.h"
#include <QFile>
#include <QApplication>
#include <QLabel>

QString readInSave(QString saveIdx = "1"){
    QString s;
    QFile f("D:\\QTProject\\Celeste_Copy\\Maps\\save"+saveIdx);
    if (!f.exists())
        return "default";
    f.open(QIODevice::ReadOnly);
    QTextStream stream(&f);
    stream >> s;
    f.close();
    return s;
}

maininterface::maininterface(QSoundEffect * player,QWidget *parent)
    : QWidget{parent},WelcomePlayer(player)
{
    SettingInterface = new settinginterface;
    FinishInterface  = new goodgame;
    CreativeStaffInterface =new creativestaffinterface;

    setFixedSize(1080,608);
    setWindowIcon(QIcon("D:/QTProject/Celeste_Copy/Image/Strawberry.png"));
    setWindowTitle("start");

    setupMainInterfaceMovie();
    setupMainInterfaceText();

}

void maininterface::setupMainInterfaceMovie(){
    backgroundMovie = new QMovie("D:/QTProject/Celeste_Copy/Movie/maininterface0.gif");
    backgroundMovie->setCacheMode(QMovie::CacheNone);
    //backgroundMovie->setSpeed(100); // 可选：设置视频播放速度

    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setMovie(backgroundMovie);
    backgroundLabel->setGeometry(0, 0, this->width(), this->height());
    backgroundLabel->lower();
    backgroundLabel->setScaledContents(true);
    connect(backgroundMovie, &QMovie::frameChanged, this, &maininterface::loadCurrentFrame);

    backgroundMovie->start();
}
void maininterface::setupMainInterfaceText(){
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(24);

    QLabel * option1 = new QLabel;
    option1 -> setParent(this);
    option1 -> setStyleSheet("color:white;");
    option1 -> setFont(font);
    option1 -> setText("C");
    option1 -> setGeometry(80,160,90,170);

    QLabel * option2 = new QLabel;
    option2 -> setParent(this);
    option2 -> setStyleSheet("color:white;");
    option2 -> setFont(font);
    option2 -> setText("S");
    option2 -> setGeometry(80,195,90,205);

    QLabel * option3 = new QLabel;
    option3 -> setParent(this);
    option3 -> setStyleSheet("color:white;");
    option3 -> setFont(font);
    option3 -> setText("M");
    option3 -> setGeometry(80,225,90,235);

    QLabel * option4 = new QLabel;
    option4 -> setParent(this);
    option4 -> setStyleSheet("color:white;");
    option4 -> setFont(font);
    option4 -> setText("E");
    option4 -> setGeometry(80,255,90,265);
}
void maininterface::loadCurrentFrame()
{
    QLabel *backgroundLabel = qobject_cast<QLabel*>(sender());
    if (backgroundLabel) {
        QPixmap framePixmap = backgroundMovie->currentPixmap();
        backgroundLabel->setPixmap(framePixmap);
    }
}
void maininterface::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_C) {
        //qDebug()<<"进入Game界面";
        hide();
        WelcomePlayer->stop();
        PressPlayer->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/ui_main_button_climb.wav"));
        PressPlayer->setVolume(0.35f);
        PressPlayer->setLoopCount(1);
        PressPlayer->play();
        GameInterface = new Game(NULL,readInSave());
        GameInterface->show();
        connect(GameInterface, &Game::Escape, this, [this](){
            WelcomePlayer->play();
            GameInterface->hide();
            this->show();
        });
        connect(GameInterface, &Game::GoodGame, this, [this](){
            WelcomePlayer->play();
            GameInterface->hide();
            FinishInterface->show();
            PressPlayer->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/game_gen_strawberry_gold_get_1up.wav"));
            PressPlayer->setVolume(0.35f);
            PressPlayer->setLoopCount(1);
            PressPlayer->play();
        });
        connect(FinishInterface, &goodgame::returnToMainInterface, this,[this](){
            WelcomePlayer->play();
            FinishInterface->hide();
            this->show();

        });
    }
    if (event->key() == Qt::Key_X) {
        //qDebug()<<"返回欢迎界面";
        PressPlayer->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/ui_main_button_back.wav"));
        PressPlayer->setVolume(0.35f);
        PressPlayer->setLoopCount(1);
        PressPlayer->play();

        switchToWidget();
    }

    if (event->key() == Qt::Key_S) {
        //qDebug()<<"进入设置界面";
        WelcomePlayer->stop();
        PressPlayer->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/ui_main_button_climb.wav"));
        PressPlayer->setVolume(0.35f);
        PressPlayer->setLoopCount(1);
        PressPlayer->play();
        switchToSettingInterface();
    }

    if (event->key() == Qt::Key_M) {
        WelcomePlayer->stop();
        PressPlayer->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/ui_main_button_climb.wav"));
        PressPlayer->setVolume(0.35f);
        PressPlayer->setLoopCount(1);
        PressPlayer->play();
        switchToCreativeStaffInterface();
    }
    if (event->key() == Qt::Key_E){
        QApplication * app = nullptr;
        app->quit();
    }
}

void maininterface::switchToWidget(){
    this -> close();
    emit returnToWidget();
}

void maininterface::switchToMainInterface()
{
    WelcomePlayer->play();
    SettingInterface -> close();
    this->show();
}

void maininterface::switchToSettingInterface(){
    this -> close();
    SettingInterface -> show();
    connect(SettingInterface, &settinginterface::returnToMainInterface, this, &maininterface::switchToMainInterface);
}

void maininterface::switchToCreativeStaffInterface(){
    this -> close();
    CreativeStaffInterface -> show();
    connect(CreativeStaffInterface, &creativestaffinterface::returnToMainInterface, this, &maininterface::switchToMainInterface);
}
