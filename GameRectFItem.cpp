#include "GameRectFItem.h"

GameRectFItem::GameRectFItem(QPointF pos, const QPixmap& pixmap, QObject* parent)
    : QObject { parent }
    , QGraphicsPixmapItem { pixmap }
{
    setPos(pos);
}
