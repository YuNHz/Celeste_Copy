#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsPixmapItem>
#include <QPainter>

class Platform : public QGraphicsPixmapItem
{
public:
    Platform(int length, double x, double y, int tp);
    QRectF BoundingRect();
    inline static int type = 1;
private:
    int m_length,m_type;
    double m_x,m_y;
};
#endif // PLATFORM_H
