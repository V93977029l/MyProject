#include "Sprite.h"

Sprite::Sprite(const QString &imagePath, QList<QGraphicsItem *> *obstacles, QObject *parent) : obstacles(obstacles)
{
    QPixmap pixmap(imagePath);
    setPixmap(pixmap);
    qreal imageSize = pixmap.width();
    m_boundingRect = QRectF(0, (pixmap.height() - imageSize / 4) / temp_magnify, imageSize / temp_magnify, imageSize / 3 / temp_magnify);
}

void Sprite::advance(int phase)
{
    QPointF direction = speed * velocity.normalized().toPointF() / temp_magnify;  // 计算移动方向
    QPointF actualMovement = moveSprite(direction);
    emit posUpdate(actualMovement * temp_magnify);
}

QRectF Sprite::boundingRect() const
{
    return m_boundingRect;
}

void Sprite::update_local()
{
    update();
}

void Sprite::setVx(float x)
{
    velocity.setX(x);
}

void Sprite::setVy(float y)
{
    velocity.setY(y);
}

float Sprite::getVx()
{
    return velocity.x();
}

float Sprite::getVy()
{
    return velocity.y();
}

QPointF Sprite::moveSprite(const QPointF &direction)
{
    QRectF newRect = m_boundingRect.translated(pos());
    newRect.translate(direction);

    QPointF actualMovement = direction;
    extracted(direction, newRect, actualMovement);
    moveBy(actualMovement.x(),actualMovement.y());
    return actualMovement;                          // 返回实际移动距离
}

void Sprite::extracted(const QPointF &direction, QRectF &newRect, QPointF &actualMovement)
{
    if (!obstacles)
    {
        return;
    }

    QPointF newPosition = pos() + direction; // 计算新的位置
    QRectF proposedRect = m_boundingRect.translated(newPosition);  // 使用 newPosition 更新 proposedRect
    actualMovement = direction;  // 默认实际移动等于预期移动

    for (const QGraphicsItem *obstacle : *obstacles)
    {
        QRectF obstacleRect = obstacle->boundingRect().translated(obstacle->pos());
        if (obstacleRect.intersects(proposedRect))
        {
            QRectF overlap = obstacleRect.intersected(proposedRect);

            if (overlap.width() < overlap.height())
            {
                // 水平移动冲突更小，调整水平方向
                qreal deltaX = (proposedRect.left() < obstacleRect.left()) ?
                                   obstacleRect.left() - proposedRect.right() :
                                   obstacleRect.right() - proposedRect.left();
                actualMovement.setX(deltaX);
            }
            else
            {
                // 垂直移动冲突更小，调整垂直方向
                qreal deltaY = (proposedRect.top() < obstacleRect.top()) ?
                                   obstacleRect.top() - proposedRect.bottom() :
                                   obstacleRect.bottom() - proposedRect.top();
                actualMovement.setY(deltaY);
            }

            // 只更新受影响的方向，避免重复全面更新
            proposedRect = m_boundingRect.translated(pos() + actualMovement);
        }
    }

    newRect = proposedRect;  // 设置最终的移动位置
}
