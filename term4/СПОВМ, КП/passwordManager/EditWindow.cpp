#include "EditWindow.h"
#include "ui_EditWindow.h"

EditWindow::EditWindow(QString *name, QString *username, QString *password, QWidget *parent) :QDialog(parent), ui(new Ui::EditWindow) {
    this->name = name;
    this->username = username;
    this->password = password;
    
    ui->setupUi(this);
    
    if(name->size()){
        setWindowTitle(*name);
    } else {
        setWindowTitle(tr("Create new bundle"));
    }
    
    
    
    ui->usernameLine->setValidator(new QRegularExpressionValidator( QRegularExpression("[^ ]{1,128}"), this));
    ui->passwordLine->setValidator(new QRegularExpressionValidator( QRegularExpression("[^ ]{1,128}"), this));
    
    ui->nameLine->setText(*name);
    ui->usernameLine->setText(*username);
    ui->passwordLine->setText(*password);
}

EditWindow::~EditWindow() {
    delete ui;
}

void EditWindow::on_buttonBox_accepted() {
    if(!ui->nameLine->text().size()) {
        QMessageBox::warning(this, "Error", "Name cannot be empty!");
        return;
    }
    if(!ui->usernameLine->text().size()) {
        QMessageBox::warning(this, "Error", "Username cannot be empty!");
        return;
    }
    if(!ui->passwordLine->text().size()) {
        QMessageBox::warning(this, "Error", "Password cannot be empty!");
        return;
    }
    
    
    *name = ui->nameLine->text();
    *username = ui->usernameLine->text();
    *password = ui->passwordLine->text();
    
    accept();
}

