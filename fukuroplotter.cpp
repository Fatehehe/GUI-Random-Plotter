#include "fukuroplotter.h"
#include "ui_fukuroplotter.h"
#define UPPER_RANGE 100

FukuroPlotter::FukuroPlotter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FukuroPlotter)
    ,xAxisVal(0.0)
    ,xAxisVal1(0.0)
    ,xlow(0)
    ,xup(UPPER_RANGE)
    ,xlow1(0)
    ,xup1(UPPER_RANGE)
{
    ui->setupUi(this);
    rand = new QRandomGenerator();

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(0)->setAntialiased(true);

    ui->customPlot->addGraph();
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(254,0,0));
    ui->customPlot->graph(1)->setPen(pen);
    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(1)->setAntialiased(true);

    ui->customPlot->xAxis->setLabel("X");
    ui->customPlot->yAxis->setLabel("Y");

    ui->customPlot->xAxis->setRange(xlow,xup);
    ui->customPlot->yAxis->setRange(-50,50);

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDot);

    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDot);

    connect(&timer, &QTimer::timeout, this, &FukuroPlotter::handleTimeout);
    connect(&timer, &QTimer::timeout, this, &FukuroPlotter::handleTimeoutGraph);
    timer.setInterval(50);

    timer.start();

}

FukuroPlotter::~FukuroPlotter()
{
    delete ui;
}

void FukuroPlotter::handleTimeout()
{
    std::random_device rd;
    std::uniform_real_distribution<double> dist(-50,50);

    double random_double = dist(rd);

    x.append(xAxisVal);
    y.append(random_double);

    std::cout << x.at(int(xAxisVal)) << std::endl;
    //QVector bisa diload pake .at()

    ui->customPlot->graph(0)->setData(x,y);

    if(xAxisVal > UPPER_RANGE){
        ui->customPlot->xAxis->setRange(xlow, xup);
        xup++;
        xlow++;
    }

    ui->customPlot->replot();
    ui->customPlot->update();
    xAxisVal++;
}

void FukuroPlotter::handleTimeoutGraph()
{
    std::random_device rd;
    std::uniform_real_distribution<double> dist(-50,50);

    double random_double = dist(rd);

    x1.append(xAxisVal1);
    y1.append(random_double);

    ui->customPlot->graph(1)->setData(x1,y1);

    if(xAxisVal1 > UPPER_RANGE){
        ui->customPlot->xAxis->setRange(xlow1, xup1);
        xup1++;
        xlow1++;
    }

    ui->customPlot->replot();
    ui->customPlot->update();
    xAxisVal1++;
}
