#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    qDebug() << "New connection available";

}

void MainWindow::readyRead()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    buffer_mutex.lock();
    buffer.append(clientSocket->readAll());
    buffer_mutex.unlock();

    emit payloadArrived(&buffer); //сигнал в поток о том, что буффер пополнен
}


//отрисовка
void MainWindow::readyPaint(cv::Mat *img)
{
    ui->label->setPixmap(QPixmap::fromImage(QImage(img->data, img->cols, img->rows, img->step, QImage::Format_RGB888)));
    delete img;
}


void MainWindow::on_startServerButton_clicked()
{
    server = new QTcpServer(this);
    pthread = new paintThread(); //создание потока

    connect(this, SIGNAL(payloadArrived(QByteArray*)),pthread, SLOT(paintFrame(QByteArray*)));//сигнал буффер пополнен к слоту потока
    connect(pthread, SIGNAL(matReady(cv::Mat*)),this, SLOT(readyPaint(cv::Mat*)));//сигнал о том, что матрица готова в потоке к текущему слоту отрисовки
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));

    pthread->start();

    if(server->listen(QHostAddress::Any,ui->portNum->text().toInt())){
        qDebug() << "Server started!";
    } else {
        qDebug() << "Server could not start";
    }
}
