#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QLabel>

class MainMenu;
class View;
class Window : public QMainWindow       // 主窗口菜单类
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

public slots:
    void setPositionLable(QPointF pos_1, QPoint pos_2);

protected:
    void resizeEvent(QResizeEvent *ev) override;

private:
    MainMenu *main_menu;
    View *view;
    QLabel *mousePositionLabel;

    void createMenus();
    void input_location();
};

#endif // WINDOW_H
