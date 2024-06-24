#include "Sprite.h"

Sprite::Sprite(const QString &imagePath, QObject *parent)
{
    setPixmap(QPixmap(imagePath));
}

void Sprite::advance(int phase)
{
    QPointF delta = speed * velocity.normalized().toPointF();
    moveBy(delta.x(), delta.y());
    emit posUpdate(delta);
}

void Sprite::update_local()
{
    // position += QVector2D(1, 1);
    //collider = QRect(position.toPoint(), pixmap.size());
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
