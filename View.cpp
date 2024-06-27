#include "View.h"
#include <QPainter>
#include <QIcon>
#include <QTimer>
#include <QKeyEvent>
#include "Sprite.h"
#include <QDebug>

View::View(QWidget *parent)
    : QGraphicsView(parent),
    scene(new QGraphicsScene(this))
{
    // 场景初始化
    init(1280, 720);

    // 载入光标
    setMouseTracking(true);         // 打开鼠标跟踪
    scene->addItem(&cursor);        // 为场景加入光标
    setCursor(QCursor(Qt::BlankCursor));

    // 载入地图
    map = new QGraphicsPixmapItem(QPixmap("../../images/temp_1.jpg"));
    map->setZValue(-0x3ffffff);
    map->setScale(temp_magnify);
    scene->addItem(map);

    // 放置空气墙
    air_wall();
    set_wall(150, 240, 187, 244);
    set_wall(207, 240, 243, 245);
    set_wall(180, 347, 215, 369);
    set_wall(262, 346, 293, 369);

    // 载入角色
    player = new Sprite("../../images/temp.png", &obstacles, this);
    player->setParentItem(map);
    player->setScale(1/temp_magnify);
    scene->addItem(player);

    // 绘制角色阴影
    QGraphicsEllipseItem *shadow = new QGraphicsEllipseItem(player);
    shadow->setRect(QRectF(0, 120, 80, 20));
    shadow->setBrush(QColor(0, 0, 0, 100));                             // 设置半透明黑色阴影
    shadow->setPen(Qt::NoPen);                                          // 不绘制边框线
    shadow->setZValue(player->zValue() - 1);                            // 确保阴影在角色对象的下方显示
    scene->addItem(shadow);

    // 设置场景
    setScene(scene);

    // 将角色放置在屏幕中心
    player->setPos((width() - player->pixmap().width()) / 2 / temp_magnify, (height()  - player->pixmap().height())/ 2 / temp_magnify);

    // 游戏计时器循环
    timer = new QTimer(this);
    connect(player, &Sprite::posUpdate, this, &View::mapMove);
    timer->callOnTimeout(this,[=]()
                         {
                             update_local();
                         });
    timer->start(1000/120);   // 60FPS
}

void View::set_player_pos(int x, int y)
{
    QPointF temp = QPointF(x, y) - player->pos();
    mapMove(temp);
    player->moveBy(temp.x(),temp.y());
}

void View::mapMove(QPointF delta)
{
    map->moveBy(-delta.x(),-delta.y());
    emit setPositionLable(map->mapFromScene(mouse_position), mouse_position);   // 激活更新状态栏
}

void View::keyPressEvent(QKeyEvent *ev)
{
    pressedKeys.insert(ev->key());  // 添加按键到集合
    switch (ev->key())
    {
    case Qt::Key_Up:
    case Qt::Key_W:
        player->setVy(-1);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        player->setVy(1);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        player->setVx(-1);
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        player->setVx(1);
        break;
    }
}

void View::keyReleaseEvent(QKeyEvent *ev)
{
    pressedKeys.remove(ev->key()); // 从集合中移除按键
    switch (ev->key())
    {
    case Qt::Key_Up:
    case Qt::Key_W:
        if (pressedKeys.contains(Qt::Key_Down | Qt::Key_S)) player->setVy(1);
        else player->setVy(0);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        if (pressedKeys.contains(Qt::Key_Up | Qt::Key_W)) player->setVy(-1);
        else player->setVy(0);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        if (pressedKeys.contains(Qt::Key_Right | Qt::Key_D)) player->setVx(1);
        else player->setVx(0);
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        if (pressedKeys.contains(Qt::Key_Left | Qt::Key_A)) player->setVx(-1);
        else player->setVx(0);
        break;
    }
}

void View::mouseMoveEvent(QMouseEvent *ev)
{
    mouse_position = ev->pos();
    cursor.update_position(mapToScene(mouse_position));
    QGraphicsView::mouseMoveEvent(ev);
    emit setPositionLable(map->mapFromScene(mouse_position), mouse_position);
}

void View::resizeEvent(QResizeEvent *ev)
{
    QGraphicsView::resizeEvent(ev);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void View::init(int width_view,int height_view)
{
    setFixedSize(width_view, height_view);
    scene->setSceneRect(0, 0, width_view, height_view);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);                  // 抗锯齿
}

void View::air_wall()
{
    QPen pen(Qt::NoPen);
    QGraphicsRectItem *obstacle_top = new QGraphicsRectItem;
    obstacle_top->setPen(pen);
    obstacle_top->setParentItem(map);
    obstacle_top->setRect(0, -20, map->pixmap().width(), 20);       // 空气墙的位置和大小
    obstacles.append(obstacle_top);

    QGraphicsRectItem *obstacle_bottom = new QGraphicsRectItem;
    obstacle_bottom->setPen(pen);
    obstacle_bottom->setParentItem(map);
    obstacle_bottom->setRect(0, map->pixmap().height(), map->pixmap().width(), 20);
    obstacles.append(obstacle_bottom);

    QGraphicsRectItem *obstacle_left = new QGraphicsRectItem;
    obstacle_left->setPen(pen);
    obstacle_left->setParentItem(map);
    obstacle_left->setRect(-20, 0, 20, map->pixmap().height());
    obstacles.append(obstacle_left);

    QGraphicsRectItem *obstacle_right = new QGraphicsRectItem;
    obstacle_right->setPen(pen);
    obstacle_right->setParentItem(map);
    obstacle_right->setRect(map->pixmap().width(), 0, 20, map->pixmap().height());
    obstacles.append(obstacle_right);
}

void View::set_wall(qreal x1, qreal y1, qreal x2, qreal y2)
{
    qreal w = x2 - x1;
    qreal h = y2 - y1;
    QGraphicsRectItem *obstacle_top = new QGraphicsRectItem;
    obstacle_top->setPen(QPen(Qt::NoPen));
    obstacle_top->setParentItem(map);
    obstacle_top->setRect(x1, y1, w, h);
    obstacles.append(obstacle_top);
}

void View::update_local()
{
    player->advance(0);
    cursor.update_local();
    scene->update();
    update();
}
