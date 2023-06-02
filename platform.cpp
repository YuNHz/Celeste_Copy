#include "Platform.h"

Platform::Platform(int length, float x, float y)
{
    m_x = x;
    m_y = y;
    m_length = length;
    setPos(m_x, m_y);
    QPixmap platformBase = QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Platform.png").scaled(24,24);
    QPixmap result(24 * length,24); // 创建结果图片
    QPainter painter(&result);
    for (int i = 0; i < length; i++) {
        painter.drawPixmap(i * 24, 0, platformBase); // 在结果图片上绘制每一张图片
    }
    painter.end();
    setPixmap(result);
}
