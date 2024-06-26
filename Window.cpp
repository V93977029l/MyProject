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
    move(50, 50);

    // 创建游戏视图
    view = new View(this);
    setCentralWidget(view);
    connect(view, &View::setPositionLable, this, &Window::setPositionLable);

    // 可以在这里添加菜单和状态栏等
    createMenus();
}

void Window::setPositionLable(QPointF pos_1, QPoint pos_2)
{
    mousePositionLabel->setText(QString("世界坐标: %1, %2;屏幕坐标: %3, %4;")
                                    .arg(pos_1.x(), 0, 'f', 0)
                                    .arg(pos_1.y(), 0, 'f', 0)
                                    .arg(pos_2.x())
                                    .arg(pos_2.y()));
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

    statusBar()->setStyleSheet("QStatusBar::item {border: none;}");
    mousePositionLabel = new QLabel("世界坐标: 0, 0;屏幕坐标: 0, 0;");
    statusBar()->addPermanentWidget(mousePositionLabel);
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
