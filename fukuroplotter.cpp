#include "fukuroplotter.h"
#include "ui_fukuroplotter.h"
#define UPPER_RANGE 100
#define LOWER_RANGE 0

FukuroPlotter::FukuroPlotter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FukuroPlotter)
    ,xAxisVal(0.0)
    ,xlow(LOWER_RANGE)
    ,xup(UPPER_RANGE)
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

    ui->customPlot->graph(0)->setData(x,y);

    if(xAxisVal > UPPER_RANGE){
        ui->customPlot->xAxis->setRange(xlow, xup);
        xup++;
        xlow++;
    }

    ui->customPlot->replot();
    ui->customPlot->update();
}

void FukuroPlotter::handleTimeoutGraph()
{
    std::random_device rd;
    std::uniform_real_distribution<double> dist(-50,50);

    double random_double = dist(rd);

    x1.append(xAxisVal);
    y1.append(random_double);

    ui->customPlot->graph(1)->setData(x1,y1);

    ui->customPlot->replot();
    ui->customPlot->update();
    xAxisVal++;
}

void FukuroPlotter::on_startButton_clicked()
{
    if(ui->startButton->text() == "Stop"){
        ui->startButton->setText("Start");
        timer.stop();
        return;
    }
    ui->startButton->setText("Stop");
    timer.start();
}


void FukuroPlotter::on_clearButton_clicked()
{
    xup = LOWER_RANGE;
    xlow = UPPER_RANGE;
    x.clear();
    y.clear();
    xAxisVal = 0.0;
    x1.clear();
    y1.clear();

    ui->customPlot->xAxis->setRange(xlow, xup);

    ui->customPlot->graph(0)->data()->clear();
    ui->customPlot->graph(1)->data()->clear();
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
    ui->customPlot->update();
}


void FukuroPlotter::on_saveButton_clicked()
{
    if(ui->startButton->text() == "Stop"){
        ui->startButton->setText("Start");
        timer.stop();
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this, "Save As");
    if( filename.isEmpty()){
        return;
    }

    QFile file(filename);

    //Open the file
    if( !file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return;
    }

    QJsonArray jsonArray;

    foreach(const int k, x){
        QJsonObject jsonObject;
        jsonObject.insert("t1",QJsonValue(x[k]));
        jsonObject.insert("v1", QJsonValue(y[k]));
        jsonObject.insert("t2", QJsonValue(x1[k]));
        jsonObject.insert("v2", QJsonValue(y1[k]));
        jsonArray.append(jsonObject);
    }

    QJsonObject jsonObject;
    jsonObject.insert("point", jsonArray.size());
    jsonArray.append(jsonArray);

    QJsonDocument jsonDoc;
    jsonDoc.setArray(jsonArray);
    file.write(jsonDoc.toJson());
    file.close();

}


void FukuroPlotter::on_loadButton_clicked()
{
    connect(ui->loadButton, &QPushButton::clicked, this, &FukuroPlotter::on_clearButton_clicked);

    QString filename = QFileDialog::getOpenFileName(this, "Choose File");

    if(filename.isEmpty()){
        qDebug() << "not opened" ;
        return;
    }

    qDebug() << filename;

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Failed to open!" << filename;
        return;
    }

    QByteArray bytes = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );
    if( jsonError.error != QJsonParseError::NoError )
    {
        std::cout << "fromJson failed: " << jsonError.errorString().toStdString() << std::endl;
        return ;
    }

    QJsonArray jsonArray = document.array();

    for(int i = 0; i < jsonArray.size(); i++){
        QJsonObject jsonObj = jsonArray.at(i).toObject();
        x.push_back(jsonObj.value("t1").toDouble());
        y.push_back(jsonObj.value("v1").toDouble());
        x1.push_back(jsonObj.value("t2").toDouble());
        y1.push_back(jsonObj.value("v2").toDouble());
    }

    ui->customPlot->graph(0)->setData(x,y);
    ui->customPlot->graph(1)->setData(x1, y1);
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
    ui->customPlot->update();

}
