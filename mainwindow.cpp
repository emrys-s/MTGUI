#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();

    QVector<double> x(101), y(101); // initialize with entries 0..100

    int n = 10;

    ui->widget_1->addGraph();
    ui->widget_1->xAxis->setLabel("time(in seconds)");
    ui->widget_1->yAxis->setLabel("bandwith(in mb)");
    ui->widget_1->xAxis->setRange(1, 30);
    ui->widget_1->yAxis->setRange(0, 100);

    char *szIPaddr;
    char *szPort = "8728"; // default port string
    int iPort=8728;             // default port int
    char *szUsername = "admin";  // default username
    char *szPassword = "";       // default password

    for (int i=0; i<101; ++i)
    {
              x[i] = i; // x goes from -1 to 1
              y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:

    ui->widget_1->graph(0)->setData(x, y);

    // give the axes some labels:
    // set axes ranges, so we see all data:

    ui->widget_1->replot();

      //  sleep(10);

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
