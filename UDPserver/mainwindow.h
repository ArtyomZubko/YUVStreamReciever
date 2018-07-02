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
    const qint64 FRAME_HEIGHT = 480;//320;
    const qint64 FRAME_WIDTH = 640;//560;
    qint64 SIZE_OF_YUV420p_FRAME = ((FRAME_HEIGHT * FRAME_WIDTH)/8)*12 ;
    QByteArray datagramBuffer;
};

#endif // MAINWINDOW_H
