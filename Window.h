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
    void setPositionLable(QPointF pos_1, QPoint pos_2);     // 右下角信息栏

private:
    MainMenu *main_menu;            // 存储顶部菜单栏
    View *view;                     // 存储中央视图
    QLabel *mousePositionLabel;     // 信息栏分栏

    void init_main_menu();          // 初始化开始菜单
    void start_game();              // 开始游戏
    void createMenus();             // 创建顶部菜单
    void createStatusBar();         // 创建状态栏
    void input_location();          // 调用弹出的传送对话框
};

#endif // WINDOW_H
