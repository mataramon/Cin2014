#include "texteditor.h"
#include "ui_texteditor.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QSettings>
#include <QList>
#include <QtCore>

TextEditor::TextEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);
    readSettings();
    for(int i = 0; i < MaxRecentFiles; i++){
        recentFilesActs[i] = new QAction(this);
        recentFilesActs[i]->setVisible(false);
        connect(recentFilesActs[i],SIGNAL(triggered()),this,SLOT(openRecentFiles()));
        ui->menu_Recent_files->addAction(recentFilesActs[i]);
    }
    updateRecentFileAction();
}

bool TextEditor::on_action_Save_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
                this,
                "TextEditor - Save as",
                ".",
                "Text files (*.txt);;All files (*.*)");
    if(!fileName.isEmpty()){
        curFile = fileName;
        return saveFile(fileName);
    }
    return false;
}

bool TextEditor::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(file.open(QFile::WriteOnly)){
        file.write(ui->plainTextEdit->toPlainText().toUtf8());
        setCurrentFile(fileName);
        setWindowTitle(tr("TextEditor - %1[*]").arg(QFileInfo(curFile).fileName()));
        ui->plainTextEdit->document()->setModified(false);
        return true;
    }else{
        QMessageBox::warning(
                    this,
                    "TextEditor",
                    tr("Cannot write file %1.\nError: %2")
                    .arg(curFile)
                    .arg(file.errorString()));
        return false;
    }
}

bool TextEditor::maybeSave()
{
    if(ui->plainTextEdit->document()->isModified()){
        QMessageBox::StandardButton ret =
                QMessageBox::warning(
                    this,
                    "TestEditor",
                    tr("The document has been modified.\n"
                    "Do you want to save your changes?"),
                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(ret == QMessageBox::Yes){
            return on_action_Save_triggered();
        }else if(ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void TextEditor::readSettings()
{
    QSettings settings("PADTS","TextEditor");
    QPoint pos = settings.value("pos",QPoint(0,0)).toPoint();
    QSize size = settings.value("size",QSize(400,300)).toSize();
    resize(size);
    move(pos);
}

void TextEditor::writeSettings()
{
    QSettings settings("PADTS","TestEditor");
    settings.setValue("pos",pos());
    settings.setValue("size",size());
}

void TextEditor::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowTitle(tr("TextEditor - %1[*]").arg(QFileInfo(curFile).fileName()));
    QSettings settings;
    QStringList recentFilesList = settings.value("recentFilesList").toStringList();
    recentFilesList.removeAll(fileName);
    recentFilesList.prepend(fileName);
    while(recentFilesList.size() > MaxRecentFiles)
        recentFilesList.removeLast();
    settings.setValue("recentFilesList",recentFilesList);
    updateRecentFileAction();
}

void TextEditor::updateRecentFileAction()
{
    QSettings settings;
    QStringList recentFilesList = settings.value("recentFilesList").toStringList();
    int numRecentFiles = qMin(recentFilesList.size(),int(MaxRecentFiles));
    for(int i = 0; i < numRecentFiles; ++i){
        QString text = tr("&%1 %2")
                .arg(i+1)
                .arg(QFileInfo(recentFilesList[i]).fileName());
        recentFilesActs[i]->setText(text);
        recentFilesActs[i]->setData(recentFilesList[i]);
        recentFilesActs[i]->setVisible(true);
    }
    for(int j = numRecentFiles; j > MaxRecentFiles; j++){
        recentFilesActs[j]->setVisible(false);
    }
}

void TextEditor::loadFile(const QString &fileName)
{
    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(file.open(QFile::ReadOnly)){
            ui->plainTextEdit->setPlainText(file.readAll());
            setCurrentFile(fileName);
        }else{
            QMessageBox::warning(
                        this,
                        "TextEditor",
                        tr("Cannot read file %1.\nError: %2")
                        .arg(fileName)
                        .arg(file.errorString()));
        }
    }
}

bool TextEditor::on_action_Save_triggered()
{
    if(curFile.isEmpty())
        return on_action_Save_as_triggered();
    else
        return saveFile(curFile);
}

void TextEditor::on_action_Open_triggered()
{
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(
                    this,
                    "TextEditor - Open file",
                    ".",
                    "Text files (*.txt);;All files (*.*)");
        loadFile(fileName);
    }
}

void TextEditor::on_action_New_triggered()
{
    if(maybeSave()){
        ui->plainTextEdit->clear();
    }
}

void TextEditor::closeEvent(QCloseEvent *event)
{
    if(maybeSave()){
        writeSettings();
        event->accept();
    }else{
        event->ignore();
    }
}

void TextEditor::openRecentFiles()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if(action){
        loadFile(action->data().toString());
    }
}

void TextEditor::on_action_About_triggered()
{
    QMessageBox::information(
                this,
                "TextEditor - About",
                "TextEditor\n\n"
                "PADTS:\n"
                "\tRaul Calzada\n"
                "\tIsrael Sanchez");
}
