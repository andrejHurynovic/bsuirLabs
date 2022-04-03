#include "SettingsWindow.h"
#include "ui_SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsWindow){
    ui->setupUi(this);
    setData();
}

SettingsWindow::~SettingsWindow(){
    delete ui;
}



void SettingsWindow::on_buttonBox_accepted(){
    if(ui->bits128Button->isChecked()){
        Settings::setKeySize(bits128);
    }
    if(ui->bits192Button->isChecked()){
        Settings::setKeySize(bits192);
    }
    if(ui->bits256Button->isChecked()){
        Settings::setKeySize(bits256);
    }
    
    Settings::setOpenOnEnter(ui->openLastFileCheck->isChecked());
    
    Settings::saveSettings();
    
}

void SettingsWindow::on_buttonBox_rejected(){
    return;
}

void SettingsWindow::on_restoreButton_clicked(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Are you sure?", "Are you sure?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        Settings::setTheDefaultSettings();
        setData();
        reject();
    }
}




void SettingsWindow::setData() {
    switch (Settings::getKeySize()) {
        case bits128:
            ui->bits128Button->setChecked(true);
            break;
        case bits192:
            ui->bits192Button->setChecked(true);
            break;
        case bits256:
            ui->bits256Button->setChecked(true);
            break;
    }
    
    ui->openLastFileCheck->setChecked(Settings::getOpenOnEnter());
}


