#ifndef QCUSPOT_H
#define QCUSPOT_H

#include "qcustomplot/qcustomplot.h"
#include "ui_mainwindow.h"

#include <QWidget>

class Qcusplot : public QWidget
{
    Q_OBJECT
public:
    explicit Qcusplot(QWidget *parent = nullptr);

private:
    void guiInit();
    QCustomPlot *cusplot;

signals:

};

#endif // QCUSPOT_H
