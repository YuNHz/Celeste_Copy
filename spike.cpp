#include "Spike.h"

Spike::Spike(int length, double x, double y,int tp)
{
    m_x = x;
    m_y = y;
    m_length = length;
    m_type = tp;
    setPos(m_x, m_y);
    switch(m_type){
    case 0:{
        QPixmap SpikeBase = QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Spike0.png").scaled(24,21);
        QPixmap result(24 * length,21); // 创建结果图片
        QPainter painter(&result);
        for (int i = 0; i < length; i++) {
            painter.drawPixmap(i * 24, 0, SpikeBase); // 在结果图片上绘制每一张图片
        }
        painter.end();
        setPixmap(result);
        break;
    }
    case 1:{
        QPixmap SpikeBase = QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Spike1.png").scaled(24,21);
        QPixmap result(24 * length,21); // 创建结果图片
        QPainter painter(&result);
        for (int i = 0; i < length; i++) {
            painter.drawPixmap(i * 24, 0, SpikeBase); // 在结果图片上绘制每一张图片
        }
        painter.end();
        setPixmap(result);
        break;
    }
    case 2:{
        QPixmap SpikeBase = QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Spike2.png").scaled(21,24);
        QPixmap result(21,24 * length); // 创建结果图片
        QPainter painter(&result);
        for (int i = 0; i < length; i++) {
            painter.drawPixmap(0 ,i*24, SpikeBase); // 在结果图片上绘制每一张图片
        }
        painter.end();
        setPixmap(result);
        break;
    }
    case 3:{
        QPixmap SpikeBase = QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Spike3.png").scaled(21,24);
        QPixmap result(21,24 * length); // 创建结果图片
        QPainter painter(&result);
        for (int i = 0; i < length; i++) {
            painter.drawPixmap(0 ,i*24, SpikeBase); // 在结果图片上绘制每一张图片
        }
        painter.end();
        setPixmap(result);
        break;
    }
    }
}

QRectF Spike::BoundingRect(){
    switch(m_type){
    case 0: return QRectF(m_x,m_y,24*m_length,24);
    case 1: return QRectF(m_x,m_y,24*m_length,24);
    case 2: return QRectF(m_x,m_y,24,24*m_length);
    case 3: return QRectF(m_x,m_y,24,24*m_length);
    }
    return QRectF(0,0,0,0);
}
