#include "Input.h"

Input::Input(QWidget *parent) : QDialog(parent)
{
    setupUi();
}

void Input::setupUi()
{
    xLineEdit = new QLineEdit(this);
    yLineEdit = new QLineEdit(this);
    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    QFormLayout *layout = new QFormLayout;
    layout->addRow("X:", xLineEdit);
    layout->addRow("Y:", yLineEdit);
    layout->addRow(okButton, cancelButton);

    setLayout(layout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

int Input::getX() const
{
    return xLineEdit->text().toInt();
}

int Input::getY() const
{
    return yLineEdit->text().toInt();
}
