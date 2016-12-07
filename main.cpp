#include "mainwindow.h"
#include <QApplication>

#define N 5

typedef struct
{
    int Arr[N];
    int pointer;
}brData;

int printData(brData curData)
{
    for (int i = 0; i < N; i++)
       printf("%3d",curData.Arr[(i+curData.pointer+1)%N]);

    return 0;
}

int addData(brData *pCurData, int data)
{
    if (pCurData->pointer == N-1)
        pCurData->pointer = 0;
    else
        (pCurData->pointer)++;

    pCurData->Arr[pCurData->pointer] = data;

    return 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

/*
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();
    w.show();
*/


    return a.exec();
}
