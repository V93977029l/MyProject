#include "Sprite.h"

Sprite::Sprite(const QString &imagePath, QList<QGraphicsItem *> *obstacles, QObject *parent) : obstacles(obstacles)
{
    QPixmap pixmap(imagePath);
    setPixmap(pixmap);
    qreal imageSize = pixmap.width();
    m_boundingRect = QRectF(0, pixmap.height() - imageSize, imageSize, imageSize);
}

void Sprite::advance(int phase)
{
    QPointF direction = speed * velocity.normalized().toPointF();  // 计算移动方向
    QPointF actualMovement = moveSprite(direction);
    emit posUpdate(actualMovement);
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

    QRectF temp = m_boundingRect.translated(pos());

    for (const QGraphicsItem *obstacle : *obstacles)
    {
        if (newRect.intersects(obstacle->boundingRect()))   // 计算与障碍物碰撞前可以移动的最大距离
        {
            QPointF obstaclePos = obstacle->pos();
            QPointF playerPos = pos();
            qreal dx = direction.x(), dy = direction.y();

            if (dx > 0)
                dx = std::max(0.0, obstaclePos.x() - playerPos.x() - temp.width());
            if (dx < 0)
                dx = std::min(0.0, obstaclePos.x() + obstacle->boundingRect().width() - playerPos.x());
            if (dy > 0)
                dy = std::max(0.0, obstaclePos.y() - playerPos.y() - temp.height());
            if (dy < 0)
                dy = std::min(0.0, obstaclePos.y() + obstacle->boundingRect().height() - playerPos.y());

            actualMovement = QPointF(dx, dy);

            break; // 只处理第一个碰撞障碍物
        }
    }
}
