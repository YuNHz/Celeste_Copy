#ifndef SPIKE_H
#define SPIKE_H

#include <QGraphicsPixmapItem>
#include <QPainter>

class Spike : public QGraphicsPixmapItem
{
public:
    Spike(int length, double x, double y, int tp);
    QRectF BoundingRect();
    inline static int type = 0;
private:
    int m_length,m_type;
    double m_x,m_y;
};
#endif // SPIKE_H
