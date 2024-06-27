#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsView>

class MainMenu : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);

private:
    QGraphicsScene *m_main;

    void init(int width_view,int height_view);

signals:
    void start_game();
};

#endif // MAINMENU_H
