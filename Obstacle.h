#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameRectFItem.h"

class Obstacle : public GameRectFItem {
    Q_OBJECT
public:
    Obstacle(QPointF pos, const QPixmap& image, QObject* parent = nullptr);
    virtual ~Obstacle() = default;
    static constexpr qreal length = 24;
};

#endif // OBSTACLE_H
