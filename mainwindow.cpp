#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fft.h"


#include <QTimer>
#include <QDebug>
#include <complex>
#include <string>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , time(QTime::currentTime())
{
    ui->setupUi(this);
    this->setWindowTitle("MR-TMD控制器");
//    timeDomainDisplay = new CurveData();

    // x轴以时间形式显示
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->cusplot_3->xAxis->setTicker(timeTicker);
    ui->cusplot_3->axisRect()->setupFullAxesBox();
    ui->cusplot_3->replot();

    ui->radioButton_3->setEnabled(false);
//    ui->cusplot_3 = new QCustomPlot(this);
    ui->cusplot_3->setObjectName(QString::fromUtf8("ui->cusplot_3"));
//    ui->cusplot_3->setGeometry(QRect(300, 40, 470, 520));
    // 图表背景颜色
    ui->cusplot_3->setBackground(Qt::white);
    // 添加一条曲线
    ui->cusplot_3->addGraph();
    // 添加画笔颜色
    ui->cusplot_3->graph(0)->setPen(QPen(Qt::red));
    QTimer *timer = new QTimer;
    timer->start(200);
    connect(timer, &QTimer::timeout, this, &MainWindow::slot_timerout);

    // 滚动条设置
    ui->horizontalScrollBar_3->setRange(0, 0);
    // 拖动水平滚动条，图幅跟随变化
    connect(ui->horizontalScrollBar_3, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));


    // 图表背景颜色
    ui->cusplot_frequent->setBackground(Qt::white);
    // 添加一条曲线
    ui->cusplot_frequent->addGraph();
    // 添加画笔颜色
    ui->cusplot_frequent->graph(0)->setPen(QPen(Qt::blue));





//    QVBoxLayout *vbox_layout = new QVBoxLayout;
//    vbox_layout->addWidget(ui->cusplot_3);
//    this->setLayout(vbox_layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_timerout()
{
//    cnt++;
//    ui->cusplot_3->graph(0)->addData(cnt,cnt);
//    ui->cusplot_3->xAxis->setRange(cnt,100,Qt::AlignRight);
//    ui->cusplot_3->yAxis->setRange(cnt,100,Qt::AlignRight);
//    ui->cusplot_3->replot();

//    static double degrees = 0;
//    double radians = qDegreesToRadians(degrees);
//    double s = 15.0 * qSin(radians);
////    ui->widgetPlot2D->addData("正弦波", s);
//    degrees += 1.0;
//    if (degrees >= 360.0) degrees = 0;

    static double x = 0;
    const double PI1 = 3.141592653589793238462643383279;
    double s = 7 * qSin(2 * PI1 * 150 * x) + 2.8 * qSin(2 * PI1 * 300 * x) + 5.1 * qSin(2 * PI1 * 550 * x);
    x += 0.001;
    static double start = time.hour()*60*60 + time.minute()*60 + time.second() + time.msec()/1000.0;
    double time_elapsed = time.elapsed()/1000.0;
    double key = start + time_elapsed;
    timeDomainDisplay.keyVec.append(x);
    timeDomainDisplay.valVec.append(0);
    double smaple_time = 10;   // 写入到ui界面中！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
    double temp = time_flag;
    double _sub = time_elapsed - temp;
//    if(time_elapsed  > 40)
//        int t = 1;
    if( _sub> smaple_time)
    {
        time_flag = time_elapsed;
        int temp_i = timeDomainDisplay.keyVec.size();
        _fft.timeDomainToFreDomain(timeDomainDisplay, frequencyDomainData);
        int temp_i1 = frequencyDomainData.keyVec.size();
        for(int i=0; i<frequencyDomainData.keyVec.size(); i++)
        {
            ui->cusplot_frequent->graph(0)->addData(frequencyDomainData.keyVec[i],frequencyDomainData.valVec[i]);
        }
        timeDomainDisplay.keyVec.clear();
        timeDomainDisplay.valVec.clear();
        frequencyDomainData.keyVec.clear();
        frequencyDomainData.valVec.clear();

    }
    if (x >= 1) x = 0;
    ui->cusplot_3->xAxis->setRange(key,10,Qt::AlignRight);
//    ui->cusplot_3->xAxis->setNumberFormat("f");
    // 刷新绘图水平滚动条
    ui->horizontalScrollBar_3->setRange(int(start), int(key));  // 刷新滚动条的范围
    ui->horizontalScrollBar_3->setPageStep(1);                  // 设置翻页步长为 1s 的宽度
    ui->horizontalScrollBar_3->setValue(int(key));              // 调整滑块位置到最右边

//    ui->cusplot_3->rescaleAxes();
    ui->cusplot_3->yAxis->setRange(-15,15);
//    qDebug() << key;
    ui->cusplot_3->graph(0)->addData(key,s);
    ui->cusplot_3->replot(QCustomPlot::rpQueuedReplot);





//    //----------------------------------------------------------------------------------------//
//        // 计算每秒的帧率
//        static double lastFpsKey = key;
//        static int frameCount = 0;
//        frameCount++;
//        // 每2秒显示一次帧率
//        if (key-lastFpsKey > 0.5) {
//            uint64_t sum = 0;
//            for (int i = 0; i < ui->cusplot_3->plottableCount(); i++) {
//                sum += uint64_t(ui->cusplot_3->graph(i)->data()->size());
//            }
//            ui->statusLabel->setText(QString("%1 FPS, Total Data points: %2").arg(frameCount/(key-lastFpsKey), 0, 'f', 0).arg(sum));
//            lastFpsKey = key;
//            frameCount = 0;
//            // 更新数据标签
//            for (int t = 0; t < ui->cusplot_3->plottableCount(); t++) {
//                valueLabelVector[t]->setText(QString::number(valueVector[t]));
//            }
//        }
//    //----------------------------------------------------------------------------------------//



//    static double start = time.hour()*60*60 + time.minute()*60 + time.second() + time.msec()/1000.0;
//    double key = start + time.elapsed()/1000.0;
//    double start = 0;
//    static int key = 0;
//    key++;
//    qDebug()() << "start" << start;
//    qDebug()() << "key" << key;
    // 子网格显示
    /*ui->customPlot->xAxis->grid()->setSubGridVisible(ui->subGridCheck->isChecked());
    ui->customPlot->yAxis->grid()->setSubGridVisible(ui->subGridCheck->isChecked());
    // 自适应量程
    if (ui->autoRangeCheck->isChecked()) {
        ui->customPlot->rescaleAxes();
    }
    // 设置时间轴
    int timeAxis = ui->timeAxisSpin->value();
    ui->customPlot->xAxis->setRange(key, timeAxis, Qt::AlignRight);
    // x轴和y轴全程显示
    if (ui->fullShowCheck->isChecked()) {
        ui->customPlot->rescaleAxes();
    }
    // 刷新绘图水平滚动条
    ui->horizontalScrollBar->setRange(int(start), int(key));  // 刷新滚动条的范围
    ui->horizontalScrollBar->setPageStep(1);                  // 设置翻页步长为 1s 的宽度
    ui->horizontalScrollBar->setValue(int(key));*/              // 调整滑块位置到最右边
    // 更新曲线绘图
    //    ui->customPlot->graph(nameToGraphMap[name])->addData(key, value);
}

void MainWindow::on_pushButton_scanSerial_clicked()
{
    ui->comboBox_serialName_3->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort _com;
        _com.setPort(info);
        if(_com.open(QIODevice::ReadWrite))
        {
            ui->comboBox_serialName_3->addItem(info.portName());
            _com.close();
        }
    }
    ui->textBrowser_operationLogs_3->append(QTime::currentTime().toString()+" 串口扫描成功\n");
}

void MainWindow::on_pushButton_openSerial_3_clicked()
{
   if(!serial.isOpen())
   {      serial.setPortName(ui->comboBox_serialName_3->currentText());
       serial.open(QIODevice::ReadWrite);
       ui->radioButton_3->setChecked(true);
       ui->pushButton_openSerial_3->setText("关闭串口");
       ui->textBrowser_operationLogs_3->append(QTime::currentTime().toString()+" 串口打开成功\n");
   }
   else{
       serial.close();
       ui->radioButton_3->setChecked(false);
       ui->pushButton_openSerial_3->setText("打开串口");
       ui->textBrowser_operationLogs_3->append(QTime::currentTime().toString()+" 串口关闭成功\n");
   }

}

void MainWindow::horzScrollBarChanged(int value)
{
//    int timeAxis = ui->timeAxisSpin->value();
    ui->cusplot_3->xAxis->setRange(value, 10, Qt::AlignRight);
    ui->cusplot_3->replot();
}

void MainWindow::on_pushButton_frequencyDomain_2_clicked()
{
//    qint16 PW[490]; //定义需要变换的数据容器，我的数据读取取消掉了
//    float Time[1];
//    QFile file("D:\\ProgramSpace\\Qt\\MR_TMD_controller\\data_temp\\noise.txt");  //保存原始数据用于画图
//    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
//    {
//        qDebug() << "Open failed.";
//    }
//    for(int i = 0;i<490;i++)
//    {
//        QTextStream txtOutput(&file);
//        txtOutput << PW[i]<<endl ;
//    }
//    file.close();


//    std::complex<double> test[980] = {};  //定义复数矩阵
//    double a[490];
//    for (int j = 0; j < 490; j++)
//    {
//        test[j].real(PW[j]);    //将需要变换的采样点放到矩阵实部
//        test[j].imag(0);
//    }
//    unsigned int N = 490, k = N, n;
//    double thetaT = 3.14159265358979323846264338328L / N;    //定义pie/N
//    std::complex<double> phiT = std::complex<double>(cos(thetaT), -sin(thetaT)), T;

//    while (k > 1)
//    {
//        n = k;
//        k >>= 1;	//补0,除以2
//        phiT = phiT * phiT;
//        T = Time[0];
//        for (unsigned int l = 0; l < k; l++)
//        {
//            for (unsigned int a = l; a < N; a += n)
//            {
//                unsigned int b = a + k;
//                std::complex<double> t = test[a] - test[b];
//                test[a] += test[b];
//                test[b] = t * T;
//            }
//            T *= phiT;
//        }
//    }
//    // 消项
//    unsigned int m = (unsigned int)log2(N);
//    for (unsigned int a = 0; a < N; a++)
//    {
//        unsigned int b = a;
//        // 反转位
//        b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
//        b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
//        b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
//        b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
//        b = ((b >> 16) | (b << 16)) >> (32 - m);
//        if (b > a)
//        {
//            std::complex<double> t = test[a];
//            test[a] = test[b];
//            test[b] = t;
//        }
//    }
//        std::complex<double> f = 1.0 / Time[0];
//        for (unsigned int i = 0; i < N; i++)
//            test[i] *= f;

//    //dft(data);
//    //std::qDebug() << "dft" << std::endl;
//    for (int i = 0; i < 490; ++i)
//    {
//       qDebug()<<"dft" << test[i].imag()<<" "<<test[i].real();
////       qDebug()<<to_string(test[i]);
//    }


//    QFile file1("D:\\ProgramSpace\\Qt\\MR_TMD_controller\\data_temp\\noise1.txt");   //保存变换后的FFT数据用于画图
//    if(!file1.open(QIODevice::WriteOnly | QIODevice::Text))
//    {
//        qDebug() << "Open failed." << endl;
//    }

//    for(int i = 0;i<490;i++)
//    {
//        QTextStream txtOutput(&file1);
//        txtOutput << test[i].imag()<<" "<<test[i].real()<<endl ;
//    }
//    file1.close();
}


