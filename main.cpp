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

    return a.exec();
}
