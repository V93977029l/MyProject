#include "AnimatedLogo.h"
#include <QPainter>
#include <QMovie>

AnimatedLogo::AnimatedLogo(const QString &fileName, QGraphicsItem *parent)
    : QGraphicsItem(parent), movie(new QMovie(fileName))
{
    connect(movie, &QMovie::frameChanged, this, [this]() {
        this->update();  // 当 GIF 帧变化时更新图形项
    });
    movie->start();  // 开始播放 GIF
}

AnimatedLogo::~AnimatedLogo()
{
    delete movie;
}

QRectF AnimatedLogo::boundingRect() const
{
    return QRectF(0, 0, movie->currentPixmap().width(), movie->currentPixmap().height());
}

void AnimatedLogo::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, movie->currentPixmap());
}
