#ifndef CURSOR_H
#define CURSOR_H

#include <QGraphicsItem>
#include <QMovie>

class Cursor : public QGraphicsItem
{
public:
    Cursor(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    void update_local();
    void update_position(const QPointF &pos);

private:
    QMovie movie_;
};

#endif // CURSOR_H
