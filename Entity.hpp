#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsItem>
#include <QPainter>

class Entity : public QObject, public QGraphicsPixmapItem     // 游戏实体类, 基类
{
    Q_OBJECT
public:
    Entity(QGraphicsItem *parent = nullptr) : QGraphicsPixmapItem(parent) {}

    // virtual void update() = 0;
    // virtual void draw(QPainter *painter) = 0;
    // virtual QRectF boundingRect() const override = 0;
    virtual void update_local() = 0;

    inline bool isActive() const {return active;}
    inline void destory() {active = false;}

    inline int type() {return m_type;}
    inline void setType(int type) {m_type = type;}
private:
    bool active = true; // 实体是否活动
    int m_type = 0;     // 实体的类型
};

#endif // ENTITY_H
