#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void connectToRouter();
    void importConfig();
    void exportConfig();
    void editConDet();
    void about();
//    void aboutQt();

private:
    void createActions();
    void createMenus();

    Ui::MainWindow *ui;

    QMenu *mainMenu;
    QMenu *configMenu;
    QMenu *helpMenu;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
//    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *connectAct;
    QAction *importAct;
    QAction *exportAct;
    QAction *editConDetAct;
    QAction *exitAct;
//    QAction *undoAct;
//    QAction *redoAct;
//    QAction *cutAct;
//    QAction *copyAct;
//    QAction *pasteAct;
//    QAction *boldAct;
//    QAction *italicAct;
//    QAction *leftAlignAct;
//    QAction *rightAlignAct;
//    QAction *justifyAct;
//    QAction *centerAct;
//    QAction *setLineSpacingAct;
//    QAction *setParagraphSpacingAct;
    QAction *aboutAct;
//    QAction *aboutQtAct;
    QLabel *infoLabel;
};

#endif // MAINWINDOW_H
