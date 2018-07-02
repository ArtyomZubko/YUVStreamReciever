#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 1234);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    pthread = new paintThread(); //создание потока

    connect(this, SIGNAL(payloadArrived(QByteArray*)),pthread, SLOT(paintFrame(QByteArray*)));//сигнал буффер пополнен к слоту потока
    connect(pthread, SIGNAL(matReady(cv::Mat*)),this, SLOT(readyPaint(cv::Mat*)));//сигнал о том, что матрица готова в потоке к текущему слоту отрисовки
    pthread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::readyRead(){
    QHostAddress sender;
    quint16 senderPort;
    //qDebug() << "ready read recieved";
    buffer_mutex.lock();
    datagramBuffer.resize(socket->pendingDatagramSize());
    socket->readDatagram(datagramBuffer.data(), datagramBuffer.size(), &sender, &senderPort);
    buffer.append(datagramBuffer);
    buffer_mutex.unlock();

    if (buffer.size() > SIZE_OF_YUV420p_FRAME+2)
        emit payloadArrived(&buffer); //сигнал в поток о том, что буффер пополнен
}

//отрисовка
void MainWindow::readyPaint(cv::Mat *img)
{
    qDebug() << "painting";
    ui->label->setPixmap(QPixmap::fromImage(QImage(img->data, img->cols, img->rows, img->step, QImage::Format_RGB888)));
    delete img;
}
