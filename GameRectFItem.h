#ifndef GAMERECTFITEM_H
#define GAMERECTFITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>

class GameRectFItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    GameRectFItem(QPointF pos, const QPixmap& pixmap, QObject* parent = nullptr);
    virtual ~GameRectFItem() = default;
    virtual int get_type() = 0;
};

#endif // GAMERECTFITEM_H
