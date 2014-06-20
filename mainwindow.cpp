#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include<iostream>
#include<fstream>

#include <sys/types.h>
#include <signal.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gdl.start("gdl", QStringList());
    connect(&gdl, SIGNAL(readyReadStandardOutput()), this, SLOT(readGdlOutput()));
    connect(&gdl, SIGNAL(readyReadStandardError()), this, SLOT(readGdlError()));

    QPalette p = ui->errorTBox->palette();
    //p.setColor(QPalette::Base, Qt::red);
    p.setColor(QPalette::Text, Qt::red);
    ui->errorTBox->setPalette(p);
}

MainWindow::~MainWindow()
{
    delete ui;
    gdl.close();
}

void MainWindow::on_actionRun_triggered()
{
    gdl.write(QByteArray(ui->programTBox->toPlainText().toAscii()));
}

void MainWindow::on_actionRetart_GDL_triggered()
{
    gdl.kill();
    gdl.waitForFinished();
    gdl.close();

    gdl.start("gdl", QStringList());
}

void MainWindow::readGdlOutput()
{
    ui->outputTBox->setPlainText(gdl.readAllStandardOutput());
    ui->tabWidget->notifyOn(0);
}

void MainWindow::readGdlError()
{
    ui->errorTBox->setPlainText(gdl.readAllStandardError());
    ui->tabWidget->notifyOn(1);
}

void MainWindow::on_actionClear_Program_triggered()
{
    ui->programTBox->clear();
}

void MainWindow::on_actionClear_Output_triggered()
{
    ui->outputTBox->clear();
}

void MainWindow::on_actionClear_Error_triggered()
{
    ui->errorTBox->clear();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->tabWidget->notifyOff(0);
    ui->tabWidget->notifyOff(1);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->outputTBox->setMinimumWidth(event->size().width() - 26);
    ui->outputTBox->setMinimumHeight(ui->tabWidget->height() - 26);
    ui->errorTBox->setMinimumWidth(event->size().width() - 26);
    ui->errorTBox->setMinimumHeight(ui->tabWidget->height() - 20);
}

/*{
    cout << "sairam sairam! " << gdl.pid() << endl;
    if(gdl.pid() > 0)
        kill(gdl.pid(), SIGTERM);
}*/

void MainWindow::on_gdlPromt_returnPressed()
{
    QByteArray cmd(ui->gdlPromt->text().toAscii());
    cmd.append("\n");
    gdl.write(cmd);
    ui->gdlPromt->setText("");
}

void MainWindow::on_actionExecute_script_triggered()
{
    QString filename = QFileDialog::getOpenFileName( this, tr("Open .pro script"), QDir::homePath(), tr("Document files (*.pro);;All files (*.*)"), 0, QFileDialog::DontUseNativeDialog );

    if( !filename.isNull() )
    {
        //qDebug( filename.toAscii() );
        ifstream script_file(filename.toLocal8Bit().data());
        if (script_file.is_open())
        {
            string line;
            while (script_file.good() )
            {
                getline(script_file, line);
                line.append("\n");
                gdl.write(line.c_str());
            }
            script_file.close();
        }
    }
}

void MainWindow::on_actionExit_triggered()
{
    exit(1);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName( this, tr("Open .pro script"), QDir::homePath(), tr("Script files (*.pro);;All files (*.*)"), 0, QFileDialog::DontUseNativeDialog );

    if( !filename.isNull() )
    {
        ui->programTBox->setPlainText("");
        ifstream script_file(filename.toLocal8Bit().data());
        if (script_file.is_open())
        {
            string line;
            while (script_file.good() )
            {
                getline(script_file, line);
                ui->programTBox->appendPlainText(QString(line.c_str()));
            }
            script_file.close();
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(
                this,
                tr("Save Script"),
                QDir::homePath(),
                tr("Script files (*.pro)") );
    if( !filename.isNull() )
    {
        ofstream save_script(filename.toLocal8Bit().data());
        if (save_script.is_open())
        {
            save_script << ui->programTBox->toPlainText().toLocal8Bit().data() << endl;
        }
        save_script.close();
    }
}
