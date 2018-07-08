#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define USE_OPENCV

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QBuffer>
#include <QFile>
#include <QDataStream>
#include <QGraphicsScene>
#include <QMutex>
#include "gamepadthread.h"

#ifdef USE_OPENCV
#include <opencv2/opencv.hpp>
#include "paintthread.h"
#endif

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
    #ifdef USE_OPENCV
    void readyPaint(cv::Mat*img);
    #endif

signals:
    void payloadArrived(QByteArray *receive_buffer);
    void connectToHost(QString ip, QString port);

private slots:
    void on_startServerButton_clicked();
    void clientDisconnected();
    void on_gmpdconnButton_clicked();

private:
#ifdef USE_OPENCV
    paintThread *pthread;
    paintThread *current_pthread;
#endif
    QMutex buffer_mutex;
    Ui::MainWindow *ui;
    QTcpServer *server;
    GamepadThread *gpthread;
    qint64 total_filesize = 0;
    QByteArray buffer;
    bool isButtonClicked = false, isgmpdconnButtonClicked = false;

};

#endif // MAINWINDOW_H
