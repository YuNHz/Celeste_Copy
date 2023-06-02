#include "madeline.h"

Madeline::Madeline(int startX,int startY){
    setPos(startX,startY);
    setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Madeline.png").scaled(45,54));
}
