#ifndef FUNOBJ_STRAWBERRY_H
#define FUNOBJ_STRAWBERRY_H

#include "Funobj.h"
#include <QPainter>
#include <QTimer>

class Strawberry : public Funobj {
    Q_OBJECT
public:
    Strawberry(QPointF pos, QObject* parent = nullptr);
    virtual ~Strawberry() = default;
    QTimer* StrawberryTimer = new QTimer();
private:
    int graphicCnt = 1;
    static constexpr qreal length = 30;
    static constexpr qreal width = 39;

    virtual int get_type(){return 1109;} //'s'+'t'+'r'+'a'+'w'+'b'+'e'+'r'+'r'+'y'=1109
    void graphic();
};


#endif // FUNOBJ_STRAWBERRY_H
