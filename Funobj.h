#ifndef FUNOBJ_H
#define FUNOBJ_H

#include "GameRectFItem.h"

class Funobj : public GameRectFItem {
    Q_OBJECT
public:
    Funobj(QPointF pos, const QPixmap& image, QObject* parent = nullptr);
    virtual ~Funobj() = default;
};

#endif // FUNOBJ_H
