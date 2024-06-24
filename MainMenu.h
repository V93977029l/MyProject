#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsView>

class MainMenu : public QGraphicsView
{
    Q_OBJECT
public:
    MainMenu();

    void open_prepare();
    void open_main();

signals:
    void startGame();
    void weaponSelect(QString weapon);
    void loadArchive(QString archive);

protected:

private:
    QGraphicsScene *s_main;
    QGraphicsScene *s_prepare;
    QGraphicsScene *s_shop;
    QGraphicsScene *s_archive;

    QSettings *settings;
    int data_amount;


};

#endif // MAINMENU_H
