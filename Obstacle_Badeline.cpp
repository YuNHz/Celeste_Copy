#include "Obstacle_Badeline.h"

Badeline::Badeline(int Time, QObject* parent)
    : Obstacle { {-1000,-1000}, QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Badeline.png").scaled(length, width), parent },time(Time)
{
    for(int i=0;i<Time;++i){
        BadelineVector.push_back({{-100,-100},1});
    }
}
