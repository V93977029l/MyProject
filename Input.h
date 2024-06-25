#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>

class Input : public QDialog
{
    Q_OBJECT

public:
    explicit Input(QWidget *parent = nullptr);
    int getX() const;
    int getY() const;

private:
    QLineEdit *xLineEdit;
    QLineEdit *yLineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi();
};

#endif // INPUT_H
