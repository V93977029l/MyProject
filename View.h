#ifndef _VIEW_H_
#define _VIEW_H_

#include "Cursor.h"
#include <QGraphicsView>

class Sprite;
class View : public QGraphicsView               // 窗口视图类
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
    void init(int width_view,int height_view);  // 画面初始化

    void set_player_pos(int x, int y);

public slots:
    void mapMove(QPointF delta);                // 移动地图

protected:
    void keyPressEvent(QKeyEvent *ev) override;
    void keyReleaseEvent(QKeyEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void resizeEvent(QResizeEvent *ev) override;

private:
    QSet<int> pressedKeys;                      // 记录正在被按下的按键

    // 资产存储
    QGraphicsScene *scene;                      // 存放场景
    Sprite *player;                             // 存放玩家单位
    QGraphicsPixmapItem *map;                   // 存放地图
    QList<QGraphicsItem *> obstacles;           // 存放障碍物

    Cursor cursor;                              // 光标
    QPoint mouse_position;                      // 鼠标位置

    QTimer *timer;                              // 计时器

    void air_wall();
    void set_wall(qreal x, qreal y, qreal w, qreal h);
    void update_local();                        // 将本地数据更新全部封装

signals:
    void setPositionLable(QPointF pos_1, QPoint pos_2);     // 给主窗口状态栏发送鼠标位置
};

#endif // !_View _H_
