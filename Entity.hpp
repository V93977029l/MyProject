#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsItem>
#include <QPainter>

class Entity : public QObject, public QGraphicsPixmapItem     // 游戏实体类, 基类
{
    Q_OBJECT
public:
    Entity(QGraphicsItem *parent = nullptr) : QGraphicsPixmapItem(parent) {}

    inline int type() {return m_type;}
    inline void setType(int type) {m_type = type;}
private:
    int m_type = 0;     // 实体的类型
};

#endif // ENTITY_H
