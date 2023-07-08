#ifndef OBSTACLE_SPIKE_H
#define OBSTACLE_SPIKE_H

#include "Obstacle.h"
#include <QPainter>

class Spike : public Obstacle {
    Q_OBJECT
public:
    Spike(QPointF pos, int direct = 1, QObject* parent = nullptr);
    virtual ~Spike() = default;
    virtual int get_type() { return 540; } //'s'+'p'+'i'+'k'+'e' = 869
    int get_direct() { return direct; }
private:
    int direct;
    static constexpr qreal length = 24;
    static constexpr qreal width = 15;
};

#endif // OBSTACLE_SPIKE_H
