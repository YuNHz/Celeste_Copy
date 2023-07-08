#ifndef GAMEFLAMEITEM_H
#define GAMEFLAMEITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>

class GameFlameItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    GameFlameItem(QObject* parent = nullptr);
    virtual ~GameFlameItem() = default;
};

#endif // GAMEFLAMEITEM_H
