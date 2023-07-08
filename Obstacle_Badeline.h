#ifndef BADELINE_H
#define BADELINE_H

#include "Obstacle.h"
#include <QPainter>

class Badeline : public Obstacle {
    Q_OBJECT
public:
    Badeline(int time, QObject* parent = nullptr);
    virtual ~Badeline() = default;
    virtual int get_type() { return 820; } //'p'+'l'+'a'+'t'+'f'+'o'+'r'+'m' = 869
private:
    QVector<std::pair<QPointF,bool>> BadelineVector;
    int time;
    static constexpr qreal length =30;
    static constexpr qreal width = 36;
    friend class Game;
};

#endif // BADELINE_H
