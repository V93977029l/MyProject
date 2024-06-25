#include "Window.h"
#include "View.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include "Input.h"

Window::Window(QWidget *parent)
    : QMainWindow{parent}
{
    // 设置窗口属性
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
    fileMenu->addAction(tr("退出游戏(&T)"), this, &QWidget::close);

    QMenu *testMenu = menuBar()->addMenu(tr("调试(&T)"));
    testMenu->addAction(tr("位置传送(&W)"), this, &Window::input_location);

    statusBar()->showMessage("游戏已就绪");
}

void Window::input_location()
{
    Input dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        int x = dialog.getX();
        int y = dialog.getY();
        view->set_Pos(x, y);
    }

    statusBar()->showMessage("传送成功");
}
