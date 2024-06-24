#include "Map.h"
#include <QPainter>

Map::Map(int x, int y, const QString &imagePath)
{
    setPos(x, y);
    pixmap.load(imagePath);
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(pos().toPoint(), pixmap);
}

QRectF Map::boundingRect() const
{
    return QRectF(0, 0, pixmap.width(), pixmap.height());
}

QSize Map::size()
{
    return QSize(pixmap.width(),pixmap.height());
}
