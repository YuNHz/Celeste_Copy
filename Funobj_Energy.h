#ifndef FUNOBJ_ENERGY_H
#define FUNOBJ_ENERGY_H


#include "Funobj.h"
#include <QPainter>

class Energy : public Funobj {
    Q_OBJECT
public:
    Energy(QPointF pos, QObject* parent = nullptr);
    virtual ~Energy() = default;
private:
    virtual int get_type(){return 650;} //'e'+'n'+'e'+'r'+'g'+'y' = 650
    static constexpr qreal length = 32;
    static constexpr qreal width = 32;
};
#endif // FUNOBJ_ENERGY_H
