#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configuration.h"
#include <mikrotikapi.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<iostream>

#define SECONDS 30
//#define BANDWITH 100000


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();
//In future we will use class to configure these parameters
//    connectionData curConfData;

    MikrotikAPI mt("94.45.71.39","nazar","ostware",8728);

    QVector<double> x(SECONDS+1), y(SECONDS+1), z(SECONDS+1);

    Sentence getIfaceStat;

    Block ifaceStatus;

//    if (!mt.Login("nazar","ostware"))
//        printf("Logged in unsuccessfully");
//    else
    for (int k=0; k<=SECONDS; k++)
    {
        printf("\n***Inside for*** \n");

        getIfaceStat.AddWord("/interface/monitor-traffic");
        getIfaceStat.AddWord("=once=");
        getIfaceStat.AddWord("=interface=ether1");
        getIfaceStat.AddWord("\0");

        mt.WriteSentence(getIfaceStat);
        mt.ReadBlock(ifaceStatus);
        for (int i = 0; i < ifaceStatus.Length(); i++)
            {
                for (int j = 0; j < ifaceStatus[i].Length() ; j++)
                {
//                    std::cout <<  ifaceStatus[i][j];
                    if (ifaceStatus[i][j].compare(0,19,"=tx-bits-per-second") == 0)
                    {
 //                       std::cout << '\n' << ifaceStatus[i][j] << endl;
                        y[k] = atof(ifaceStatus[i][j].c_str()+20);
 //                       std::cout << '\n' << y[k];
                    }
                    else if (ifaceStatus[i][j].compare(0,19,"=rx-bits-per-second") == 0)
                    {
//                        std::cout <<'\n' << ifaceStatus[i][j] << endl;
                        z[k] = atof(ifaceStatus[i][j].c_str()+20);
                    }
                }
            }
        x[k] = k;
        sleep(1);
    }

    ui->widget_1->addGraph();
    ui->widget_1->xAxis->setLabel("time(in seconds)");
    ui->widget_1->yAxis->setLabel("bandwith(in bytes)");
    ui->widget_1->xAxis->setRange(0, x.length());
    ui->widget_1->yAxis->setRange(0, *std::max_element(y.begin(),y.end()));
    ui->widget_1->graph(0)->setData(x, y);

    ui->widget_1->replot();

    ui->widget_2->addGraph();
    ui->widget_2->xAxis->setLabel("time(in seconds)");
    ui->widget_2->yAxis->setLabel("bandwith(in bytes)");
    ui->widget_2->xAxis->setRange(0, x.length());
    ui->widget_2->yAxis->setRange(0, *std::max_element(z.begin(),z.end()));
    ui->widget_2->graph(0)->setData(x, z);

    ui->widget_1->replot();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToRouter()
{
    infoLabel->setText(tr("Invoked <b>|New</b>"));
}

void MainWindow::importConfig()
{
    infoLabel->setText(tr("Invoked <b>File|Open</b>"));
}

void MainWindow::exportConfig()
{
    infoLabel->setText(tr("Invoked <b>File|Save</b>"));
}

void MainWindow::editConDet()
{
    infoLabel->setText(tr("Invoked <b>File|Print</b>"));
}

void MainWindow::about()
{
    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About MTGUI"),
            tr("This program used to monitor and control MT devices "));
}

void MainWindow::createActions()
{
    connectAct = new QAction(tr("&Connect to router"), this);
    connectAct->setStatusTip(tr("Connect to router"));
    connect(connectAct, &QAction::triggered, this, &MainWindow::connectToRouter);

    importAct = new QAction(tr("&Import config from file"), this);
    importAct->setStatusTip(tr("Import config from file"));
    connect(importAct, &QAction::triggered, this, &MainWindow::importConfig);

    exportAct = new QAction(tr("&Export config to file"), this);
    exportAct->setStatusTip(tr("Export config to file"));
    connect(exportAct, &QAction::triggered, this, &MainWindow::exportConfig);

    editConDetAct = new QAction(tr("&Edit connection detail"), this);
    editConDetAct->setStatusTip(tr("Edit connection detail"));
    connect(editConDetAct, &QAction::triggered, this, &MainWindow::editConDet);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Main"));
    fileMenu->addAction(connectAct);
    fileMenu->addAction(importAct);
    fileMenu->addAction(exportAct);
    fileMenu->addAction(editConDetAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}
