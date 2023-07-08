#ifndef UI_SETTINGINTERFACE_H
#define UI_SETTINGINTERFACE_H

#include <QWidget>
#include <QSoundEffect>

class settinginterface : public QWidget
{
    Q_OBJECT
public:
    explicit settinginterface(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void switchToMainInterface();
    void setupSettingInterfaceText();
    QSoundEffect * PressPlayer { new QSoundEffect{this} };

signals:
    void returnToMainInterface();
};

#endif // UI_SETTINGINTERFACE_H
