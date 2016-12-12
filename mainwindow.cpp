#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configuration.h"
#include <mikrotik-api.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>

#define SECONDS 5
#define BANDWITH 10000
//#define BANDWITH 100

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();
//In future we will use class to configure these parameters
//    connectionData curConfData;

    char *szIPaddr = (char*)"94.45.71.39";
    int iPort=8728;
//    char *szUsername = (char*)"nazar";
    char szUsername[10] = {'n','a','z','a','r','2','\0'};

    char szPassword[1] = {'\0'};
//    char *szPassword = (char*)"ostware";
//    char szPassword[10] = {'o','s','t','w','a','r','e','\0'};

 //   char cWordInput[256];
 //   strcpy(cWordInput,(char*)"/interface/monitor-traffic");
//    (char*)"/interface/monitor-traffic";
    struct Sentence stSentence;
    struct Block stBlock;
    QVector<double> x(SECONDS+1), y(SECONDS+1), z(SECONDS+1);

    int fdSock = ::apiConnect(szIPaddr, iPort);
    int iLoginResult = ::login(fdSock, szUsername, szPassword);

    if (!iLoginResult)
    {
         ::apiDisconnect(fdSock);
         printf("Invalid username or password.\n");
    }
    else
    for (int k=0; k<=SECONDS; k++)
    {
//        ::addWordToSentence(&stSentence, (char*)"/interface/monitor-traffic");
//        ::addWordToSentence(&stSentence, (char*)"=once=");
//        ::addWordToSentence(&stSentence, (char*)"=interface=ether1");
//        ::addWordToSentence(&stSentence, (char*)"\0");
//               // write sentence to the API
//        if (stSentence.iLength > 0)
//        {
//            writeSentence(fdSock, &stSentence);
////            // receive and print response block from the API
//            stBlock = readBlock(fdSock);

//            for (int i = 0; i < stBlock.iLength; i++)
//            {
//                 for (int j = 0; j < stBlock.stSentence[i]->iLength; j++)
//                 {
//                      if (!strncmp(stBlock.stSentence[i]->szSentence[j],"=tx-bits-per-second",19))
//                      {
//                          printf("\n%s",stBlock.stSentence[i]->szSentence[j]+20);
//                          y[k] = atof(stBlock.stSentence[i]->szSentence[j]+20);
//                      }
//                      else if (!strncmp(stBlock.stSentence[i]->szSentence[j],"=rx-bits-per-second",19))
//                        z[k] = atof(stBlock.stSentence[i]->szSentence[j]+20);
//                  }
//             }
//             clearSentence(&stSentence);
//        }
        sleep(1);
        x[k] = k;
    //     y[k] = 60 + rand()%40;
    //     z[k] = 60 + rand()%40;
    }
    for (int k=0; k<=SECONDS; k++)
    {
        printf("\nx[]:%3d y[]:%3d z[]:%3d",x[k],y[k],z[k]);
    }

    ui->widget_1->addGraph();
    ui->widget_1->xAxis->setLabel("time(in seconds)");
    ui->widget_1->yAxis->setLabel("bandwith(in mb)");
    ui->widget_1->xAxis->setRange(0, SECONDS);
    ui->widget_1->yAxis->setRange(0, BANDWITH);
    ui->widget_1->graph(0)->setData(x, y);

    ui->widget_1->replot();

    ui->widget_2->addGraph();
    ui->widget_2->xAxis->setLabel("time(in seconds)");
    ui->widget_2->yAxis->setLabel("bandwith(in mb)");
    ui->widget_2->xAxis->setRange(0, SECONDS);
    ui->widget_2->yAxis->setRange(0, BANDWITH);
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
