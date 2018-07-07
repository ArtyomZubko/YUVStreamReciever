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
    connect(socket,SIGNAL(disconnected()),this,SLOT(clientDisconnected()));
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
    if (isButtonClicked == true) {
        current_pthread->terminate();
        server->close();
    }

    server = new QTcpServer(this);
    pthread = new paintThread(); //создание потока
    current_pthread = pthread; // запоминаем текущий поток

    connect(this, SIGNAL(payloadArrived(QByteArray*)),pthread, SLOT(paintFrame(QByteArray*)));//сигнал буффер пополнен к слоту потока
    connect(pthread, SIGNAL(matReady(cv::Mat*)),this, SLOT(readyPaint(cv::Mat*)));//сигнал о том, что матрица готова в потоке к текущему слоту отрисовки
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));

    pthread->start();

    if(server->listen(QHostAddress::Any,ui->portNum->text().toInt())){
        qDebug() << "Видеосервер запущен";
        ui->statusabel->setText("Видеосервер запущен");
    } else {
        qDebug() << "Видеосервер не смог стартовать";
        ui->statusabel->setText("Видеосервер не смог стартовать");
    }

    isButtonClicked = true;
    ui->startServerButton->setEnabled(false);
}

void MainWindow::clientDisconnected()
{
    ui->startServerButton->setEnabled(true);
    ui->label->setText("СВЯЗЬ С КЛИЕНТОМ ПРЕРВАНА! ПЕРЕЗАПУСТИТЕ СЕРВЕР, ПОВТОРНО НАЖАВ НА \nКНОПКУ ЗАПУСКА");
}

void MainWindow::on_gmpdconnButton_clicked()
{
    gpthread = new GamepadThread(ui->gmpdAdress->text(),ui->gmpdPort->text().toInt());
    gpthread->start();
}
