#include "qcusplot.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>

Qcusplot::Qcusplot(QWidget *parent) : QWidget(parent)
{
    guiInit();
}

void Qcusplot::guiInit()
{
    cusplot = new QCustomPlot(this);
//    cusplot->setGeometry(QRect(300, 20, 470, 500));
//    QVBoxLayout *vbox_layout = new QVBoxLayout;
//    cusplot->resize(800,500);
//    vbox_layout->addWidget(cusplot);

//    this->setLayout(vbox_layout);
}
