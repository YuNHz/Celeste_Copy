#include "Platform.h"

Platform::Platform(int length, double x, double y,int tp)
{
    m_x = x;
    m_y = y;
    m_length = length;
    m_type = tp;
    setPos(m_x, m_y);
    switch(m_type){
    case 0:{
        QPixmap platformBase = QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Platform.png").scaled(24,24);
        QPixmap result(24 * length,24); // 创建结果图片
        QPainter painter(&result);
        for (int i = 0; i < length; i++) {
            painter.drawPixmap(i * 24, 0, platformBase); // 在结果图片上绘制每一张图片
        }
        painter.end();
        setPixmap(result);
        break;
    }
    case 1:{
        QPixmap platformBase = QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Platform.png").scaled(24,24);
        QPixmap result(24 * length,24); // 创建结果图片
        QPainter painter(&result);
        for (int i = 0; i < length; i++) {
            painter.drawPixmap(i * 24, 0, platformBase); // 在结果图片上绘制每一张图片
        }
        painter.end();
        setPixmap(result);
        break;
    }
    case 2:{
        QPixmap platformBase = QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Platform.png").scaled(24,24);
        QPixmap result(24,24 * length); // 创建结果图片
        QPainter painter(&result);
        for (int i = 0; i < length; i++) {
            painter.drawPixmap(0 ,i*24, platformBase); // 在结果图片上绘制每一张图片
        }
        painter.end();
        setPixmap(result);
        break;
    }
    case 3:{
        QPixmap platformBase = QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Platform.png").scaled(24,24);
        QPixmap result(24,24 * length); // 创建结果图片
        QPainter painter(&result);
        for (int i = 0; i < length; i++) {
            painter.drawPixmap(0 ,i*24, platformBase); // 在结果图片上绘制每一张图片
        }
        painter.end();
        setPixmap(result);
        break;
    }
    }
}

QRectF Platform::BoundingRect(){
    switch(m_type){
    case 0: return QRectF(m_x,m_y,24*m_length,24);
    case 1: return QRectF(m_x,m_y,24*m_length,24);
    case 2: return QRectF(m_x,m_y,24,24*m_length);
    case 3: return QRectF(m_x,m_y,24,24*m_length);
    }
    return QRectF(0,0,0,0);
}
