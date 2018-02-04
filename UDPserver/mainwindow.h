#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QBuffer>
#include <QFile>
#include <QDataStream>
#include <QGraphicsScene>
#include <QMutex>
#include "paintthread.h"
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
    void readyRead();
    void readyPaint(cv::Mat*img);

signals:
    void payloadArrived(QByteArray *receive_buffer);


private:
    Ui::MainWindow *ui;
    QUdpSocket *socket;
    QMutex buffer_mutex;
    paintThread *pthread;
    qint64 total_filesize = 0;
    QByteArray buffer;
};

#endif // MAINWINDOW_H
