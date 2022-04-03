#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QCryptographicHash>


#include "PasswordWindow.h"
#include "EditWindow.h"
#include "SettingsWindow.h"


#include "Bundle.h"
#include "File.h"
#include "Settings.h"
#include "BundleUndo.h"




QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QMainWindow {
    Q_OBJECT
    
public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
    
    private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionDelete_triggered();
    void on_actionEdit_triggered();
    void on_bundleTable_doubleClicked(const QModelIndex &index);
    void on_actionSave_as_triggered();
    void on_actionClose_triggered();
    void on_actionNew_triggered();
    void on_actionUndo_triggered();
    void on_actionAdd_triggered();
    void on_actionRedo_triggered();
    
    void on_actionSettings_triggered();
    
private:
    Ui::StartWindow *ui;
    PasswordWindow *passwordWindow;
    EditWindow *editWindow;
    
    QStandardItemModel *bundlesModel;
    
    File file;
    QString masterPassword;
    vector<Bundle> bundles;
    
    void initTable();
    void updateTable();
    void bundleFunctions(bool);
    bool validatePassword();
    void undoFunctions(bool);
    void fileFunctions(bool);
    
};
#endif // STARTWINDOW_H
