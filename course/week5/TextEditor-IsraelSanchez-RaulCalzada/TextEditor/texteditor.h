#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>

namespace Ui {
class TextEditor;
}

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = 0);

private slots:
    bool on_action_Save_as_triggered();

    bool on_action_Save_triggered();

    void on_action_Open_triggered();

    void on_action_New_triggered();

    void closeEvent(QCloseEvent *event);

    void openRecentFiles();

    void on_action_About_triggered();

private:
    Ui::TextEditor *ui;
    //bool saveFile();
    bool saveFile(const QString &fileName);
    bool maybeSave();
    void readSettings();
    void writeSettings();
    void setCurrentFile(const QString &fileName);
    void updateRecentFileAction();
    void loadFile(const QString &fileName);
    QString curFile;
    enum {MaxRecentFiles = 5};
    QAction *recentFilesActs[MaxRecentFiles];
};

#endif // TEXTEDITOR_H
