#include "startWindow.h"
#include "./ui_startWindow.h"



StartWindow::StartWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::StartWindow) {
    
    Settings::loadSettings();

    
    ui->setupUi(this);
    initTable();
    
    fileFunctions(false);
    bundleFunctions(false);
    undoFunctions(false);

    if(Settings::getOpenOnEnter()) {
        QSettings settings;
        file.setFileName(settings.value("fileName").toString());

        if(file.openFileAndGetDescriptor(false)) {
            PasswordWindow passwordWindow(this, &masterPassword);

            while(true) {
                passwordWindow.exec();
                if(passwordWindow.result() == QDialog::Accepted) {

                    if(!file.validatePassword(masterPassword)) {
                        continue;
                    }

                    bundles = file.readBundles(masterPassword);

                    initTable();
                    file.closeFile();
                    fileFunctions(true);
                    bundleFunctions(true);
                    return;
                } else {
                    break;
                }
            }
        } else {
            QMessageBox::warning(this, "Error", "Can't open last file!");
        }
    }
}

StartWindow::~StartWindow() {
    delete ui;
}



void StartWindow::bundleFunctions(bool temp) {
    ui->actionDelete->setEnabled(temp);
    ui->actionEdit->setEnabled(temp);
}

void StartWindow::undoFunctions(bool temp) {
    ui->actionRedo->setEnabled(temp);
    ui->actionUndo->setEnabled(temp);
}

void StartWindow::fileFunctions(bool temp) {
    bundleFunctions(temp);
    undoFunctions(temp);
    ui->actionClose->setEnabled(temp);
    ui->actionSave->setEnabled(temp);
    ui->actionSave_as->setEnabled(temp);
}

void StartWindow::initTable() {
    QStandardItem *item;
    
    bundlesModel = new QStandardItemModel;
    
    const QStringList bundleTableHeadersList = {"Name", "Username", "Password"};
    bundlesModel->setHorizontalHeaderLabels(bundleTableHeadersList);
    
    bundlesModel->setParent(this);
    for (int i = 0; i < bundles.size(); i++) {
        item = new QStandardItem(QString(bundles[i].getName()));
        bundlesModel->setItem(i, 0, item);
        item = new QStandardItem(QString(bundles[i].getUsername()));
        bundlesModel->setItem(i, 1, item);
        item = new QStandardItem(QString(bundles[i].getPassword()));
        bundlesModel->setItem(i, 2, item);
    }
    
    ui->bundleTable->setModel(bundlesModel);
    ui->bundleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->bundleTable->verticalHeader()->hide();
    
    ui->bundleTable->sortByColumn(0, Qt::SortOrder::AscendingOrder);
}

void StartWindow::updateTable() {
    
    
    
}



void StartWindow::on_actionNew_triggered(){
    if(file.newFile()) {
        fileFunctions(true);
    } else {
        
    }
    
    PasswordWindow passwordWindow(this, &masterPassword);
    
    while(true) {
        passwordWindow.exec();
        if(passwordWindow.result() == QDialog::Rejected) {
            QMessageBox::warning(this, "Error", "You cannot create a file without adding a password!");
        } else {
            bundles.clear();
            file.writeBundles(bundles, masterPassword);
            file.closeFile();
            return;
        }
    }
    QSettings settings;
    settings.setValue("fileName", file.getFileName());
}

void StartWindow::on_actionOpen_triggered() {
    if(file.openFile()) {
        PasswordWindow passwordWindow(this, &masterPassword);
        while(true){
            passwordWindow.exec();
            if(passwordWindow.result() == QDialog::Accepted) {
                
                if(!file.validatePassword(masterPassword)) {
                    continue;
                }
                
                bundles = file.readBundles(masterPassword);
                
                initTable();
                file.closeFile();
                fileFunctions(true);
                bundleFunctions(true);

                QSettings settings;
                settings.setValue("fileName", file.getFileName());

                return;
            } else {
                break;
            }
        }
        
    }
}

void StartWindow::on_actionSave_triggered() {
    if(file.saveFile()) {
        
        int rows = bundlesModel->rowCount();
        
        bundles.clear();
        
        for (int i = 0; i < rows; i++) {
            bundles.push_back(Bundle(bundlesModel->item(i, 0)->text().toStdString(), bundlesModel->item(i, 1)->text().toStdString(), bundlesModel->item(i, 2)->text().toStdString()));
        }

        file.writeBundles(bundles, masterPassword);
        
        file.closeFile();
    }
}

void StartWindow::on_actionSave_as_triggered() {
    file.saveFileAs();
    
    int rows = bundlesModel->rowCount();
    
    file.write(&rows, sizeof(int), 0);
    
    for (int i = 0; i < rows; i++) {
        Bundle* bundle = new Bundle(bundlesModel->item(i, 0)->text().toStdString(), bundlesModel->item(i, 1)->text().toStdString(), bundlesModel->item(i, 2)->text().toStdString());
        file.write(bundle, sizeof(Bundle), sizeof(int) + sizeof(Bundle) * i);
    }
    file.closeFile();
}

void StartWindow::on_actionClose_triggered() {
    file.closeFile();
    fileFunctions(false);
    bundles.clear();
    bundlesModel->clear();
    initTable();
}



void StartWindow::on_actionUndo_triggered(){
    //bundles[0].encrypt(tr(""));
}

void StartWindow::on_actionRedo_triggered() {
    //bundles[0].decrypt(tr(""));
}



void StartWindow::on_actionAdd_triggered(){
    QModelIndexList selection = ui->bundleTable->selectionModel()->selectedRows();
    
    int pasteRow = 0;
    
    if(selection.size() >= 1){
        pasteRow = selection.last().row() + 1;
    } else {
        pasteRow = 0;
    }
    
    QString name;
    QString username;
    QString password;
    
    editWindow = new EditWindow(&name, &username, &password, this);
    if(editWindow->exec()) {
        QStandardItem *item;
        bundlesModel->insertRow(pasteRow);
        item = new QStandardItem(name);
        bundlesModel->setItem(pasteRow, 0, item);
        item = new QStandardItem(username);
        bundlesModel->setItem(pasteRow, 1, item);
        item = new QStandardItem(password);
        bundlesModel->setItem(pasteRow, 2, item);
    }
}

void StartWindow::on_actionDelete_triggered() {
    QModelIndexList selection = ui->bundleTable->selectionModel()->selectedRows();
    if(selection.empty()) {
        return;
    }
    int i = 0;
    for (; i < selection.size(); i++) {
        bundlesModel->removeRow(selection[i].row() - i);
    }
    
    if(bundlesModel->rowCount() != 0) {     //set selection on item that now on delelted item place
        i = selection.last().row() - i + 1; //deleted row index
        if(i > bundlesModel->rowCount() - 1) {
            i--;
        }
        ui->bundleTable->selectRow(i);
    }
}



void StartWindow::on_actionEdit_triggered() {
    QItemSelectionModel* selection = ui->bundleTable->selectionModel();
    if(selection->selectedRows().size() > 1) {
        QMessageBox::warning(this, "Error", "You cannot edit more than one item at a time!");
        return;
    }
    
    QModelIndexList indexes = selection->selectedIndexes();
    
    QString name = indexes[0].data().toString();
    QString username = indexes[1].data().toString();
    QString password = indexes[2].data().toString();
    
    editWindow = new EditWindow(&name, &username, &password, this);
    editWindow->exec();
    
    bundlesModel->itemFromIndex(indexes[0])->setText(name);
    bundlesModel->itemFromIndex(indexes[1])->setText(username);
    bundlesModel->itemFromIndex(indexes[2])->setText(password);
}



void StartWindow::on_bundleTable_doubleClicked(const QModelIndex &index) {
    on_actionEdit_triggered();
}

void StartWindow::on_actionSettings_triggered() {
    SettingsWindow settingsWindow(this);
    settingsWindow.exec();
}

