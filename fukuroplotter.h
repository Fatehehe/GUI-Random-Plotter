#ifndef FUKUROPLOTTER_H
#define FUKUROPLOTTER_H

#include <QMainWindow>
#include <QVector>
#include <QDebug>
#include <QTimer>
#include <QRandomGenerator>
#include "qcustomplot.h"
#include <random>
#include <QVector>
#include <iostream>
#include <QPen>
#include <QFileDialog>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class FukuroPlotter; }
QT_END_NAMESPACE

class FukuroPlotter : public QMainWindow
{
    Q_OBJECT

public:
    FukuroPlotter(QWidget *parent = nullptr);
    ~FukuroPlotter();

private:
    Ui::FukuroPlotter *ui;
    QTimer timer;
    QRandomGenerator *rand;
    QVector<double> x, y;
    QVector<double> x1, y1;
    double xAxisVal;
    double xAxisVal1;
    int xlow, xup;
//    int xlow1, xup1;

private slots:
    void handleTimeout();
    void handleTimeoutGraph();
    void on_startButton_clicked();
    void on_clearButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();
};
#endif // FUKUROPLOTTER_H
