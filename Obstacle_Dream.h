#ifndef DREAM_H
#define DREAM_H

#include "Obstacle.h"
#include <QPainter>

class Dream : public Obstacle {
    Q_OBJECT
public:
    Dream(QPointF pos, QObject* parent = nullptr);
    virtual ~Dream() = default;
    virtual int get_type() { return 521; } //'d'+'r'+'e'+'a'+'m' = 521
private:
    static constexpr qreal length = 24;
    static constexpr qreal width = 24;
};

#endif // DREAM_H
