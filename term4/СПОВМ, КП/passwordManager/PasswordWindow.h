#ifndef PASSWORDWINDOW_H
#define PASSWORDWINDOW_H

#include <QDialog>
#include <QRegularExpressionValidator>

namespace Ui {
class PasswordWindow;
}

class PasswordWindow : public QDialog {
    Q_OBJECT
    
public:
    explicit PasswordWindow(QWidget *parent = nullptr, QString* masterPassword = NULL);
    ~PasswordWindow();
    
    private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    
private:
    Ui::PasswordWindow *ui;
    QString *masterPassword;
    
};

#endif // PASSWORDWINDOW_H
