#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QProcess"

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
    void on_actionRun_triggered();

    void on_actionRetart_GDL_triggered();

    void readGdlOutput();

    void readGdlError();

    void on_actionClear_Program_triggered();

    void on_actionClear_Output_triggered();

    void on_actionClear_Error_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_gdlPromt_returnPressed();

    void on_actionExecute_script_triggered();

    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;

    QProcess gdl;

protected:
    void resizeEvent(QResizeEvent * event);
};

#endif // MAINWINDOW_H
