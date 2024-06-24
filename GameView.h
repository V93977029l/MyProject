#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>

class GameView : public QGraphicsView {
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = nullptr);

protected:
    // 处理键盘事件，可以在这里添加玩家控制逻辑
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsScene *scene;
};


#endif // GAMEVIEW_H
