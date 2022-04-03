#include "PasswordWindow.h"
#include "ui_passwordWindow.h"

PasswordWindow::PasswordWindow(QWidget *parent, QString* masterPassword) : QDialog(parent), ui(new Ui::PasswordWindow) {
    this->masterPassword = masterPassword;
    ui->setupUi(this);
    
    ui->passwordLine->setValidator(new QRegularExpressionValidator( QRegularExpression("[^ ]{1,128}"), this));
}

PasswordWindow::~PasswordWindow() {
    delete ui;
}

void PasswordWindow::on_buttonBox_accepted() {
    *masterPassword = ui->passwordLine->text();
    accept();
}


void PasswordWindow::on_buttonBox_rejected() {
    reject();
}
