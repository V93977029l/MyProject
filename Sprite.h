#ifndef SPRITE_H
#define SPRITE_H

#include "Entity.hpp"
#include <QPixmap>
#include <QVector2D>

class Sprite : public Entity        // 游戏单位类
{
    Q_OBJECT
public:
    Sprite(const QString &imagePath, QList<QGraphicsItem *> *obstacles, QObject *parent = nullptr);

    void advance(int phase) override;           // 单位移动逻辑
    QRectF boundingRect() const override;       // 碰撞箱

    void update_local();                        // 额外数据更新

public:                                         // 单位移动逻辑
    void setVx(float x);
    void setVy(float y);
    float getVx();
    float getVy();

private:
    QVector2D velocity;
    int speed = 5;
    QList<QGraphicsItem *> *obstacles = nullptr;
    QRectF m_boundingRect;

    QPointF moveSprite(const QPointF &direction);
    void extracted(const QPointF &direction, QRectF &newRect, QPointF &actualMovement);

signals:
    void posUpdate(QPointF delta);
};

#endif // SPRITE_H
