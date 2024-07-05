#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcusplot.h"
#include "fft.h"
//#include "fftw3.h"

#include <QMainWindow>
#include <QTime>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSerialPort serial;

private slots:
    void slot_timerout();
    void on_pushButton_scanSerial_clicked();
    void on_pushButton_openSerial_3_clicked();
    void horzScrollBarChanged(int value);
    void on_pushButton_frequencyDomain_2_clicked();

private:
    Ui::MainWindow *ui;
//    QCustomPlot *cusplot;
    QTime time;
    int cnt = 0;
    CurveData timeDomainDisplay, frequencyDomainData;
    fft _fft;
    double time_flag = 0;
};
#endif // MAINWINDOW_H
