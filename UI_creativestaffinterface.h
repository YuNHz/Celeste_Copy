#ifndef UI_CREATIVESTAFFINTERFACE_H
#define UI_CREATIVESTAFFINTERFACE_H

#include <QMainWindow>
#include <QSoundEffect>

class creativestaffinterface : public QMainWindow
{
    Q_OBJECT
public:
    explicit creativestaffinterface(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void switchToMainInterface();
    void setupCreativeStaffInterfaceText();
    QSoundEffect * PressPlayer { new QSoundEffect{this} };

signals:
    void returnToMainInterface();
};

#endif // UI_CREATIVESTAFFINTERFACE_H
