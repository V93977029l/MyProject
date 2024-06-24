#ifndef MAP_H
#define MAP_H

#include <QGraphicsItem>

class Map : public QGraphicsPixmapItem        // 游戏地图类
{
public:
    Map();
    Map(int x, int y, const QString &imagePath);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override;

    QSize size();
};

#endif // MAP_H
