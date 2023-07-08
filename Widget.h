#ifndef WIDGET_H
#define WIDGET_H

#include "UI_maininterface.h"
#include <QSoundEffect>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QSoundEffect * WelcomePlayer { new QSoundEffect{this} };
    QSoundEffect * PressPlayer { new QSoundEffect{this} };
    QMovie * BackgroundMovie;
    QMovie * WelcomeMovie;

    maininterface* MainInterface = NULL;

    void setupWelcomeMovie();
    void switchToMainInterface();
    void switchToWidget();
    void keyPressEvent(QKeyEvent *event) override;
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
