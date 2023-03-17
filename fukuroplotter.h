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
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class FukuroPlotter; }
QT_END_NAMESPACE

class FukuroPlotter : public QMainWindow
{
    Q_OBJECT

public:
    FukuroPlotter(QWidget *parent = nullptr);
    ~FukuroPlotter();

    void setGraph();

private:
    Ui::FukuroPlotter *ui;
    QThread thread;
    QTimer timer;
    QTimer timerHW;
    QRandomGenerator *rand;
    QVector<double> x, y;
    QVector<double> x1, y1;
    QVector<double> x2, y2;

    QVector<double> xd1, yd1;
    QVector<double> xd2, yd2;
    QVector<double> xm1, ym1;
    QVector<double> xm2, ym2;
    QVector<double> xm3, ym3;
    double xAxisVal, xAxisValHW;
    int xlow, xup, xlowHW, xupHW;

private slots:
    void handleTimeout();
    void handleTimeoutHW();
    void on_startButton_clicked();
    void on_clearButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();
    void on_loadButtonHW_clicked();
    void on_clearButtonHW_clicked();
    void on_saveButtonHW_clicked();
    void on_xCheckBox_stateChanged(int arg1);
    void on_yCheckBox_stateChanged(int arg1);
    void on_zCheckBox_stateChanged(int arg1);
    void on_d1CheckBox_stateChanged(int arg1);
    void on_d2CheckBox_stateChanged(int arg1);
    void on_m1CheckBox_stateChanged(int arg1);
    void on_m2CheckBox_stateChanged(int arg1);
    void on_m3CheckBox_stateChanged(int arg1);
};
#endif // FUKUROPLOTTER_H
