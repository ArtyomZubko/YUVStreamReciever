#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QBuffer>
#include <QFile>
#include <QDataStream>
#include <QGraphicsScene>
#include <QMutex>
#include "paintthread.h"
#include "gamepadthread.h"
#include <opencv2/opencv.hpp>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void newConnection();
    void readyRead();
    void readyPaint(cv::Mat*img);


signals:
    void payloadArrived(QByteArray *receive_buffer);
    void connectToHost(QString ip, QString port);

private slots:
    void on_startServerButton_clicked();
    void clientDisconnected();
    void on_gmpdconnButton_clicked();

private:
    QMutex buffer_mutex;
    Ui::MainWindow *ui;
    QTcpServer *server;
    GamepadThread *gpthread;
    paintThread *pthread;
    paintThread *current_pthread;
    qint64 total_filesize = 0;
    QByteArray buffer;
    bool isButtonClicked = false, isgmpdconnButtonClicked = false;

};

#endif // MAINWINDOW_H
