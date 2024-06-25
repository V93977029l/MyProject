#ifndef _VIEW_H_
#define _VIEW_H_

#include "Cursor.h"
#include <QGraphicsView>

class Sprite;
class View : public QGraphicsView       // 窗口视图类
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
    void init(QSize size);          // 画面初始化
    void sizeBy(QSize size);        // 重新设置画面大小

    void set_Pos(int x, int y);

public slots:
    void mapMove(QPointF delta);

protected:
    void keyPressEvent(QKeyEvent *ev) override;
    void keyReleaseEvent(QKeyEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void resizeEvent(QResizeEvent *ev) override;
    void closeEvent(QCloseEvent *ev) override;

private:
    QSet<int> pressedKeys;              // 记录正在被按下的按键

    // 资产存储
    QGraphicsScene *scene;              // 存放场景
    Sprite *player;                     // 存放玩家单位
    QGraphicsPixmapItem *map;           // 存放地图
    QList<QGraphicsItem *> obstacles;   // 存放障碍物
    Cursor cursor;

    QTimer *timer;

    void air_wall();
    void update_local();                // 将本地数据更新全部封装
    void clean();                       // 用于游戏主界面关闭时的内存清理
};

#endif // !_View _H_
