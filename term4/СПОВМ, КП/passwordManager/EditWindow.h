#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QDialog>
#include <QRegularExpressionValidator>
#include <QMessageBox>

namespace Ui {
class EditWindow;
}

class EditWindow : public QDialog {
    Q_OBJECT
    
public:
    explicit EditWindow(QString *name = NULL, QString *username = NULL, QString *password = NULL, QWidget *parent = nullptr);
    ~EditWindow();
    
    private slots:
    void on_buttonBox_accepted();
    
private:
    Ui::EditWindow *ui;
    QString *name;
    QString *username;
    QString *password;
};

#endif // EDITWINDOW_H
