#include "View.h"
#include <QPainter>
#include <QIcon>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include "Sprite.h"

View::View(QWidget *parent)
    : QGraphicsView(parent),
    scene(new QGraphicsScene(this)),
    map(new QGraphicsPixmapItem(QPixmap("images/caochang.png")))
{
    // 场景初始化
    int width_view = 1280;
    int height_view = 720;
    setFixedSize(width_view, height_view);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);                  // 抗锯齿

    // 载入光标
    scene->addItem(&cursor);
    setCursor(QCursor(Qt::BlankCursor));

    // 载入地图
    map->setZValue(-0x3ffffff);
    scene->addItem(map);

    // 载入角色
    player = new Sprite("images/temp.png", this);
    player->setParentItem(map);
    scene->addItem(player);

    // 设置场景大小
    scene->setSceneRect(0, 0, width_view, height_view);

    // 设置场景
    setScene(scene);

    // 将角色放置在地图中心
    player->setPos((width() - player->pixmap().width()) / 2, (height()  - player->pixmap().height())/ 2);

    // 游戏计时器循环
    timer = new QTimer(this);
    connect(player, &Sprite::posUpdate, this, &View::mapMove);
    timer->callOnTimeout(this,[=]()
    {
        update_local();
    });
    timer->start(1000/60);   // 60FPS
}

void View::init(QSize size)
{
    resize(size);
}

void View::sizeBy(QSize size)
{
    resize(size);
    scene->setSceneRect(0, 0, size.width(), size.height());
}

void View::mapMove(QPointF delta)
{
    map->moveBy(-delta.x(),-delta.y());
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
    cursor.update_position(mapToScene(ev->pos()));
    QGraphicsView::mouseMoveEvent(ev);
}

void View::mousePressEvent(QMouseEvent *ev)
{

}

void View::mouseReleaseEvent(QMouseEvent *ev)
{

}

void View::resizeEvent(QResizeEvent *ev)
{
    QGraphicsView::resizeEvent(ev);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void View::closeEvent(QCloseEvent *ev)
{
    clean();
}

void View::update_local()
{
    player->advance(0);
    cursor.update_local();
    update();
}

void View::clean()
{

}
