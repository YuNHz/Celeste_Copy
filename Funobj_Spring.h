#ifndef SPRING_H
#define SPRING_H


#include "Funobj.h"
#include <QPainter>

class Spring : public Funobj {
    Q_OBJECT
public:
    Spring(QPointF pos, QObject* parent = nullptr);
    virtual ~Spring() = default;
private:
    virtual int get_type(){return 659;} //'s'+'p'+'r'+'i'+'n'+'g' = 659
    static constexpr qreal length = 24;
    static constexpr qreal width = 9;
};

#endif // SPRING_H
