#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsPixmapItem>
#include <QPainter>

class Platform : public QGraphicsPixmapItem
{
public:
    Platform(int length, float x, float y);

private:
    int m_length;
    float m_x,m_y;
};
#endif // PLATFORM_H
