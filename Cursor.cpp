#include "Cursor.h"
#include <QPainter>

Cursor::Cursor(QGraphicsItem *parent)
    : QGraphicsItem(parent), movie_("../../images/QAQ.gif")
{
    movie_.start();
}

QRectF Cursor::boundingRect() const
{
    return QRectF(-movie_.currentPixmap().size().width() / 2 + 10,
                  -movie_.currentPixmap().size().height() / 2 + 6.5,
                  movie_.currentPixmap().size().width(),
                  movie_.currentPixmap().size().height());
}

void Cursor::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect().topLeft(), movie_.currentPixmap());
}

void Cursor::update_local()
{
    movie_.jumpToNextFrame();
    update();
}

void Cursor::update_position(const QPointF &pos)
{
    moveBy(pos.x() - scenePos().x(), pos.y() - scenePos().y());
}
