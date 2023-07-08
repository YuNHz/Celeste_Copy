#ifndef OBSTACLE_PLATFORM_H
#define OBSTACLE_PLATFORM_H

#include "Obstacle.h"
#include <QPainter>

class Platform : public Obstacle {
    Q_OBJECT
public:
    Platform(QPointF pos, QObject* parent = nullptr);
    virtual ~Platform() = default;
    virtual int get_type() { return 869; } //'p'+'l'+'a'+'t'+'f'+'o'+'r'+'m' = 869
private:
    static constexpr qreal length = 24;
    static constexpr qreal width = 24;
};

#endif // OBSTACLE_PLATFORM_H
