#include "Window.h"
#include "View.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>

Window::Window(QWidget *parent)
    : QMainWindow{parent}
{
    // 设置窗口属性
    setMouseTracking(true);
    setWindowTitle("我是一个游戏");
    setWindowIcon(QIcon("path"));
    layout()->setSizeConstraint(QLayout::SetFixedSize); // 自动适应子窗口的大小

    // 创建游戏视图
    view = new View(this);
    setCentralWidget(view);

    // 可以在这里添加菜单和状态栏等
    createMenus();
}

void Window::resizeEvent(QResizeEvent *ev)
{
    QMainWindow::resizeEvent(ev);
    view->sizeBy(centralWidget()->size());  // ?
}

void Window::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("菜单(&C)"));
    QAction *exitAction = fileMenu->addAction(tr("退出游戏(&T)"), this, &QWidget::close);
    statusBar()->showMessage("游戏已就绪");
}
