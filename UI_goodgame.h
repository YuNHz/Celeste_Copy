#ifndef GOODGAME_H
#define GOODGAME_H


#include <QWidget>
#include <QSoundEffect>

class goodgame : public QWidget
{
    Q_OBJECT
public:
    explicit goodgame(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void switchToMainInterface();
    QSoundEffect * PressPlayer { new QSoundEffect{this} };

signals:
    void returnToMainInterface();
};

#endif // GOODGAME_H
