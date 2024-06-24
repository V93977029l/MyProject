#ifndef SPRITE_H
#define SPRITE_H

#include "Entity.hpp"
#include <QPixmap>
#include <QVector2D>

class Sprite : public Entity        // 游戏单位类
{
    Q_OBJECT
public:
    Sprite(const QString &imagePath, QObject *parent = nullptr);

    // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // QRectF boundingRect() const override;       // 碰撞箱
    void advance(int phase) override;           // 单位移动逻辑

    void update_local() override;               // 额外数据更新

public:                     // 单位移动逻辑
    void setVx(float x);
    void setVy(float y);
    float getVx();
    float getVy();

private:
    QVector2D velocity;     // 速度
    int speed = 10;

signals:
    void posUpdate(QPointF delta);
};

#endif // SPRITE_H
