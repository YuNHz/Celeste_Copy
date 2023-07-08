QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Funobj.cpp \
    Funobj_Energy.cpp \
    Funobj_Spring.cpp \
    Funobj_Strawberry.cpp \
    GameFlameItem.cpp \
    GameRectFItem.cpp \
    Madeline.cpp \
    Obstacle.cpp \
    Obstacle_Badeline.cpp \
    Obstacle_Dream.cpp \
    Obstacle_Platform.cpp \
    Obstacle_Spike.cpp \
    UI_goodgame.cpp \
    UI_maininterface.cpp \
    UI_settinginterface.cpp \
    UI_creativestaffinterface.cpp \
    game.cpp \
    main.cpp \
    widget.cpp \

HEADERS += \
    Funobj.h \
    Funobj_Energy.h \
    Funobj_Spring.h \
    Funobj_Strawberry.h \
    GameFlameItem.h \
    GameRectFItem.h \
    Madeline.h \
    Obstacle.h \
    Obstacle_Badeline.h \
    Obstacle_Dream.h \
    Obstacle_Platform.h \
    Obstacle_Spike.h \
    UI_goodgame.h \
    UI_maininterface.h \
    UI_settinginterface.h \
    UI_creativestaffinterface.h \
    game.h \
    widget.h \

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


