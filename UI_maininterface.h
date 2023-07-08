#ifndef UI_MAININTERFACE_H
#define UI_MAININTERFACE_H


#include "game.h"
#include <QWidget>
#include <QSoundEffect>
#include <QMovie>
#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include "UI_goodgame.h"
#include "UI_settinginterface.h"
#include "ui_creativestaffinterface.h"
class maininterface : public QWidget
{
    Q_OBJECT
public:
    explicit maininterface(QSoundEffect * player,QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void switchToWidget();

    Game* GameInterface = NULL;
    void switchToMainInterface();

    settinginterface *SettingInterface =NULL;
    goodgame *FinishInterface =NULL;
    void switchToSettingInterface();

    creativestaffinterface *CreativeStaffInterface =NULL;
    void switchToCreativeStaffInterface();

    QSoundEffect * WelcomePlayer;
    QSoundEffect * PressPlayer { new QSoundEffect{this} };
    QMovie *backgroundMovie;
    void setupMainInterfaceMovie();
    void loadCurrentFrame();

    void setupMainInterfaceText();

signals:
    void returnToWidget();
};

#endif // UI_MAININTERFACE_H
