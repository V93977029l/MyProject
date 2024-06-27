#ifndef ANIMATEDLOGO_H
#define ANIMATEDLOGO_H

#include <QGraphicsItem>

class AnimatedLogo : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    AnimatedLogo(const QString &fileName, QGraphicsItem *parent = nullptr);
    ~AnimatedLogo();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    QMovie *movie;
};

#endif // ANIMATEDLOGO_H
