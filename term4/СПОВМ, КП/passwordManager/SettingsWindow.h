#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "Settings.h"


namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog {
    Q_OBJECT
    
public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
    
    private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    
    void on_restoreButton_clicked();
    
private:
    Ui::SettingsWindow *ui;
    void setData();
};

#endif // SETTINGSWINDOW_H
