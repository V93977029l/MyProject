#include "MainMenu.h"
#include <QFontDatabase>
#include <QUrl>
#include <QGraphicsItem>
#include "AnimatedLogo.h"
#include <QPushButton>

MainMenu::MainMenu(QWidget *parent)
    : QGraphicsView(parent),
    m_main(new QGraphicsScene(this))
{
    // 加载字体
    int fontId = QFontDatabase::addApplicationFont("fusion-pixel-proportional.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily, 20);

    // 初始化
    init(1280, 720);

    // 设置背景
    m_main->setBackgroundBrush(QPixmap("../../images/Background.png"));

    // 设置音乐
    // QSoundEffect *bgm = new QSoundEffect(this);
    // bgm->setSource(QUrl::fromLocalFile("path"));
    // bgm->setVolume(0.1);
    // bgm->play();

    // 设置Logo
    AnimatedLogo *logo = new AnimatedLogo("../../images/ic_logo.gif");
    m_main->addItem(logo);
    logo->setPos(480, 120);

    // 创建开始按钮
    QPushButton *main_start_button = new QPushButton("开始游戏");
    main_start_button->move(530, 480);
    main_start_button->resize(220, 110);

    // 设置按钮透明背景和自定义字体
    main_start_button->setFont(customFont);
    main_start_button->setStyleSheet("QPushButton { background-color: transparent; color: white; border: none; }");

    connect(main_start_button, &QPushButton::clicked, this, &MainMenu::start_game);
    m_main->addWidget(main_start_button);
}

void MainMenu::init(int width_view,int height_view)
{
    setFixedSize(width_view, height_view);
    setScene(m_main);
    m_main->setSceneRect(0, 0, width_view, height_view);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);                  // 抗锯齿
}
