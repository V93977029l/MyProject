#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

class MainMenu;
class View;
class Window : public QMainWindow       // 主窗口菜单类
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *ev) override;

private:
    MainMenu *main_menu;
    View *view;

    void createMenus();
};

#endif // WINDOW_H
