#include "GameView.h"
#include <QGraphicsScene>
#include <QKeyEvent>

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent)
{
    // 创建并设置场景
    scene = new QGraphicsScene(this);
    setScene(scene);
    scene->setSceneRect(0, 0, 800, 600);

    // 视图设置
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void GameView::keyPressEvent(QKeyEvent *event)
{

}
