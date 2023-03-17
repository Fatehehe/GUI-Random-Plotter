#include "fukuroplotter.h"
#include "ui_fukuroplotter.h"
#include <QPixmap>
#define UPPER_RANGE 100
#define LOWER_RANGE 0

FukuroPlotter::FukuroPlotter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FukuroPlotter)
    ,xAxisVal(0.0)
    ,xlow(LOWER_RANGE)
    ,xup(UPPER_RANGE)
    ,xlowHW(LOWER_RANGE)
    ,xupHW(UPPER_RANGE)
    ,xAxisValHW(0.0)
{
    ui->setupUi(this);

    QPixmap pixleft("/home/fatih/Learn Qt/0.Project/GUIFukuroPlotter/resource/guicomp2.png");
    QPixmap pixright("/home/fatih/Learn Qt/0.Project/GUIFukuroPlotter/resource/guicomp1.png");
    QPixmap fukuro("/home/fatih/Learn Qt/0.Project/GUIFukuroPlotter/resource/logoFukuro.png");
    ui->leftImage->setPixmap(pixleft.scaled(50, 600, Qt::KeepAspectRatio));
    ui->rightImage->setPixmap(pixright.scaled(50, 600, Qt::KeepAspectRatio));
    ui->fukuro->setPixmap(fukuro.scaled(90, 90, Qt::KeepAspectRatio));

    ui->customPlot->setBackground(QColor(60,60,60));
    ui->hwCustomPlot->setBackground(QColor(60,60,60));

    ui->customPlot->xAxis->setLabel("Time");
    ui->customPlot->xAxis->setBasePen(QPen(QColor(250,250,250)));
    ui->customPlot->xAxis->setLabelColor(QColor(250,250,250));
    ui->customPlot->xAxis->setTickLabelColor(QColor(250,250,250));
    ui->customPlot->yAxis->setLabel("Velocity");
    ui->customPlot->yAxis->setBasePen(QPen(QColor(250,250,250)));
    ui->customPlot->yAxis->setLabelColor(QColor(250,250,250));
    ui->customPlot->yAxis->setTickLabelColor(QColor(250,250,250));

    ui->hwCustomPlot->xAxis->setLabel("Time");
    ui->hwCustomPlot->xAxis->setBasePen(QPen(QColor(250,250,250)));
    ui->hwCustomPlot->xAxis->setLabelColor(QColor(250,250,250));
    ui->hwCustomPlot->xAxis->setTickLabelColor(QColor(250,250,250));
    ui->hwCustomPlot->yAxis->setLabel("Velocity");
    ui->hwCustomPlot->yAxis->setBasePen(QPen(QColor(250,250,250)));
    ui->hwCustomPlot->yAxis->setLabelColor(QColor(250,250,250));
    ui->hwCustomPlot->yAxis->setTickLabelColor(QColor(250,250,250));

    ui->customPlot->xAxis->setRange(xlow,xup);
    ui->customPlot->yAxis->setRange(-50,50);

    ui->hwCustomPlot->xAxis->setRange(xlowHW,xupHW);
    ui->hwCustomPlot->yAxis->setRange(-50,50);

    setGraph();

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->hwCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->startButton->setStyleSheet("background-color:#00e031; border-radius : 10px; color : white;");

    connect(&timer, &QTimer::timeout, this, &FukuroPlotter::handleTimeout);
    connect(&timerHW, &QTimer::timeout, this, &FukuroPlotter::handleTimeoutHW);
    timer.setInterval(50);
    timerHW.setInterval(50);
}

FukuroPlotter::~FukuroPlotter()
{
    delete ui;
}

void FukuroPlotter::setGraph()
{
    ui->customPlot->addGraph();
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(0, 255, 42));
    ui->customPlot->graph(0)->setPen(pen);
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(0)->setAntialiased(true);
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDot);

    ui->customPlot->addGraph();
    QPen pen1;
    pen1.setWidth(3);
    pen1.setColor(QColor(255, 47, 0));
    ui->customPlot->graph(1)->setPen(pen1);
    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(1)->setAntialiased(true);
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDot);

    ui->customPlot->addGraph();
    QPen pen2;
    pen2.setWidth(3);
    pen2.setColor(QColor(66, 135, 245));
    ui->customPlot->graph(2)->setPen(pen2);
    ui->customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(2)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(2)->setAntialiased(true);
    ui->customPlot->graph(2)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDot);

    ui->hwCustomPlot->addGraph();
    ui->hwCustomPlot->graph(0)->setPen(pen);
    ui->hwCustomPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->hwCustomPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->hwCustomPlot->graph(0)->setAntialiased(true);
    ui->hwCustomPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->hwCustomPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDot);

    ui->hwCustomPlot->addGraph();
    ui->hwCustomPlot->graph(1)->setPen(pen1);
    ui->hwCustomPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->hwCustomPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->hwCustomPlot->graph(1)->setAntialiased(true);
    ui->hwCustomPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->hwCustomPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDot);

    ui->hwCustomPlot->addGraph();
    ui->hwCustomPlot->graph(2)->setPen(pen2);
    ui->hwCustomPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->hwCustomPlot->graph(2)->setLineStyle(QCPGraph::lsLine);
    ui->hwCustomPlot->graph(2)->setAntialiased(true);
    ui->hwCustomPlot->graph(2)->setLineStyle(QCPGraph::lsLine);
    ui->hwCustomPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDot);

    QPen pen3;
    pen3.setWidth(3);
    pen3.setColor(QColor(241, 115, 255));
    ui->hwCustomPlot->addGraph();
    ui->hwCustomPlot->graph(3)->setPen(pen3);
    ui->hwCustomPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->hwCustomPlot->graph(3)->setLineStyle(QCPGraph::lsLine);
    ui->hwCustomPlot->graph(3)->setAntialiased(true);
    ui->hwCustomPlot->graph(3)->setLineStyle(QCPGraph::lsLine);
    ui->hwCustomPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDot);

    QPen pen4;
    pen4.setWidth(3);
    pen4.setColor(QColor(239, 245, 66));
    ui->hwCustomPlot->addGraph();
    ui->hwCustomPlot->graph(4)->setPen(pen4);
    ui->hwCustomPlot->graph(4)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->hwCustomPlot->graph(4)->setLineStyle(QCPGraph::lsLine);
    ui->hwCustomPlot->graph(4)->setAntialiased(true);
    ui->hwCustomPlot->graph(4)->setLineStyle(QCPGraph::lsLine);
    ui->hwCustomPlot->graph(4)->setScatterStyle(QCPScatterStyle::ssDot);
}

void FukuroPlotter::handleTimeout()
{
    std::random_device rd;
    std::uniform_real_distribution<double> dist(-50,50);

    double random_double = dist(rd);

    x.append(xAxisVal);
    y.append(random_double);

    random_double = dist(rd);
    x1.append(xAxisVal);
    y1.append(random_double);

    random_double = dist(rd);
    x2.append(xAxisVal);
    y2.append(random_double);

    ui->customPlot->graph(0)->setData(x,y);
    ui->customPlot->graph(1)->setData(x1,y1);
    ui->customPlot->graph(2)->setData(x2,y2);

    if(xAxisVal > UPPER_RANGE){
        ui->customPlot->xAxis->setRange(xlow, xup);
        xup++;
        xlow++;
    }
    qDebug() << "thread handle timeout" << QThread::currentThread();
    ui->customPlot->replot();
    ui->customPlot->update();

    xAxisVal++;
}

void FukuroPlotter::handleTimeoutHW()
{
    std::random_device rd;
    std::uniform_real_distribution<double> dist(-50,50);

    double random_double = dist(rd);

    xd1.append(xAxisValHW);
    yd1.append(random_double);

    random_double = dist(rd);
    xd2.append(xAxisValHW);
    yd2.append(random_double);

    random_double = dist(rd);
    xm1.append(xAxisValHW);
    ym1.append(random_double);

    random_double = dist(rd);
    xm2.append(xAxisValHW);
    ym2.append(random_double);

    random_double = dist(rd);
    xm3.append(xAxisValHW);
    ym3.append(random_double);

    ui->hwCustomPlot->graph(0)->setData(xd1,yd1);
    ui->hwCustomPlot->graph(1)->setData(xd2,yd2);
    ui->hwCustomPlot->graph(2)->setData(xm1,ym1);
    ui->hwCustomPlot->graph(3)->setData(xm2,ym2);
    ui->hwCustomPlot->graph(4)->setData(xm3,ym3);

    if(xAxisValHW > UPPER_RANGE){
        ui->hwCustomPlot->xAxis->setRange(xlowHW, xupHW);
        xupHW++;
        xlowHW++;
    }
    qDebug() << "thread handle timeout" << QThread::currentThread();
    ui->hwCustomPlot->replot();
    ui->hwCustomPlot->update();

    xAxisValHW++;
}

void FukuroPlotter::on_startButton_clicked()
{
    if(ui->startButton->text() == "Stop"){
        ui->startButton->setText("Start");
        ui->startButton->setStyleSheet("background-color:#00e031; border-radius : 10px; color : white;");
        timer.stop();
        timerHW.stop();
        return;
    }
    ui->startButton->setText("Stop");
    ui->startButton->setStyleSheet("background-color:#d90000; border-radius : 10px; color : white;");
    timer.start();
    timerHW.start();
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
    x2.clear();
    y2.clear();

    ui->customPlot->xAxis->setRange(xlow, xup);

    ui->customPlot->graph(0)->data()->clear();
    ui->customPlot->graph(1)->data()->clear();
    ui->customPlot->graph(2)->data()->clear();
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
        jsonObject.insert("t3", QJsonValue(x2[k]));
        jsonObject.insert("v3", QJsonValue(y2[k]));
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
    xup = LOWER_RANGE;
    xlow = UPPER_RANGE;
    xAxisVal = 0.0;
    x.clear();
    y.clear();
    x1.clear();
    y1.clear();
    x2.clear();
    y2.clear();

    QString filename = QFileDialog::getOpenFileName(this, "Choose File");

    if(filename.isEmpty()){
        qDebug() << "not opened" ;
        return;
    }else if(!filename.isEmpty()){
        ui->customPlot->xAxis->setRange(xlow, xup);
        ui->customPlot->graph(0)->data()->clear();
        ui->customPlot->graph(1)->data()->clear();
        ui->customPlot->graph(2)->data()->clear();
        ui->customPlot->rescaleAxes();
        ui->customPlot->replot();
        ui->customPlot->update();
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
        x2.push_back(jsonObj.value("t3").toDouble());
        y2.push_back(jsonObj.value("v3").toDouble());

        ui->customPlot->graph(0)->setData(x,y);
        ui->customPlot->graph(1)->setData(x1, y1);
        ui->customPlot->graph(2)->setData(x2, y2);

        if(xAxisVal > UPPER_RANGE){
            ui->customPlot->xAxis->setRange(xlow, xup);
            xup++;
            xlow++;
        }

        ui->customPlot->replot();
        ui->customPlot->update();
        xAxisVal++;
    }

}

void FukuroPlotter::on_loadButtonHW_clicked()
{
    xupHW = LOWER_RANGE;
    xlowHW = UPPER_RANGE;
    xAxisValHW = 0.0;
    xd1.clear();
    yd1.clear();
    xd2.clear();
    yd2.clear();
    xm1.clear();
    ym1.clear();
    xm2.clear();
    ym2.clear();
    xm3.clear();
    ym3.clear();

    QString filename = QFileDialog::getOpenFileName(this, "Choose File");

    if(filename.isEmpty()){
        qDebug() << "not opened" ;
        return;
    }else if(!filename.isEmpty()){
        ui->hwCustomPlot->xAxis->setRange(xlowHW, xupHW);
        ui->hwCustomPlot->graph(0)->data()->clear();
        ui->hwCustomPlot->graph(1)->data()->clear();
        ui->hwCustomPlot->graph(2)->data()->clear();
        ui->hwCustomPlot->graph(3)->data()->clear();
        ui->hwCustomPlot->graph(4)->data()->clear();
        ui->hwCustomPlot->rescaleAxes();
        ui->hwCustomPlot->replot();
        ui->hwCustomPlot->update();
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
        xd1.push_back(jsonObj.value("t1").toDouble());
        yd1.push_back(jsonObj.value("v1").toDouble());
        xd2.push_back(jsonObj.value("t2").toDouble());
        yd2.push_back(jsonObj.value("v2").toDouble());
        xm1.push_back(jsonObj.value("t3").toDouble());
        ym1.push_back(jsonObj.value("v3").toDouble());
        xm2.push_back(jsonObj.value("t4").toDouble());
        ym2.push_back(jsonObj.value("v4").toDouble());
        xm3.push_back(jsonObj.value("t5").toDouble());
        ym3.push_back(jsonObj.value("v5").toDouble());

        ui->hwCustomPlot->graph(0)->setData(xd1,yd1);
        ui->hwCustomPlot->graph(1)->setData(xd2, yd2);
        ui->hwCustomPlot->graph(2)->setData(xm1, ym1);
        ui->hwCustomPlot->graph(3)->setData(xm2, ym2);
        ui->hwCustomPlot->graph(4)->setData(xm3, ym3);



        if(xAxisValHW > UPPER_RANGE){
            ui->hwCustomPlot->xAxis->setRange(xlowHW, xupHW);
            xupHW++;
            xlowHW++;
        }

        ui->hwCustomPlot->replot();
        ui->hwCustomPlot->update();
        xAxisValHW++;
    }

}


void FukuroPlotter::on_clearButtonHW_clicked()
{
    xupHW = LOWER_RANGE;
    xlowHW = UPPER_RANGE;
    xd1.clear();
    yd1.clear();
    xAxisValHW = 0.0;
    xd2.clear();
    yd2.clear();
    xm1.clear();
    ym1.clear();
    xm2.clear();
    ym2.clear();
    xm3.clear();
    ym3.clear();

    ui->hwCustomPlot->xAxis->setRange(xlowHW, xupHW);

    ui->hwCustomPlot->graph(0)->data()->clear();
    ui->hwCustomPlot->graph(1)->data()->clear();
    ui->hwCustomPlot->graph(2)->data()->clear();
    ui->hwCustomPlot->graph(3)->data()->clear();
    ui->hwCustomPlot->graph(4)->data()->clear();

    ui->hwCustomPlot->rescaleAxes();
    ui->hwCustomPlot->replot();
    ui->hwCustomPlot->update();
}


void FukuroPlotter::on_saveButtonHW_clicked()
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

    foreach(const int k, xd1){
        QJsonObject jsonObject;
        jsonObject.insert("t1", QJsonValue(xd1[k]));
        jsonObject.insert("v1", QJsonValue(yd1[k]));
        jsonObject.insert("t2", QJsonValue(xd2[k]));
        jsonObject.insert("v2", QJsonValue(yd2[k]));
        jsonObject.insert("t3", QJsonValue(xm1[k]));
        jsonObject.insert("v3", QJsonValue(ym1[k]));
        jsonObject.insert("t4", QJsonValue(xm2[k]));
        jsonObject.insert("v4", QJsonValue(ym2[k]));
        jsonObject.insert("t5", QJsonValue(xm3[k]));
        jsonObject.insert("v5", QJsonValue(ym3[k]));
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


void FukuroPlotter::on_xCheckBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->customPlot->graph(0)->setVisible(false);
    }else{
        ui->customPlot->graph(0)->setVisible(true);
    }
}


void FukuroPlotter::on_yCheckBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->customPlot->graph(1)->setVisible(false);
    }else{
        ui->customPlot->graph(1)->setVisible(true);
    }
}


void FukuroPlotter::on_zCheckBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->customPlot->graph(2)->setVisible(false);
    }else{
        ui->customPlot->graph(2)->setVisible(true);
    }
}


void FukuroPlotter::on_d1CheckBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->hwCustomPlot->graph(0)->setVisible(false);
    }else{
        ui->hwCustomPlot->graph(0)->setVisible(true);
    }
}


void FukuroPlotter::on_d2CheckBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->hwCustomPlot->graph(1)->setVisible(false);
    }else{
        ui->hwCustomPlot->graph(1)->setVisible(true);
    }
}


void FukuroPlotter::on_m1CheckBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->hwCustomPlot->graph(2)->setVisible(false);
    }else{
        ui->hwCustomPlot->graph(2)->setVisible(true);
    }
}


void FukuroPlotter::on_m2CheckBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->hwCustomPlot->graph(3)->setVisible(false);
    }else{
        ui->hwCustomPlot->graph(3)->setVisible(true);
    }
}


void FukuroPlotter::on_m3CheckBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->hwCustomPlot->graph(4)->setVisible(false);
    }else{
        ui->hwCustomPlot->graph(4)->setVisible(true);
    }
}

