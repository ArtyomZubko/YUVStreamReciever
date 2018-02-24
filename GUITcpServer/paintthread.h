#ifndef PAINTTHREAD_H
#define PAINTTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include <opencv2/opencv.hpp>

class paintThread : public QThread
{
    Q_OBJECT
public:
    void run()
    {
        exec();
    }


public slots:
    void paintFrame(QByteArray *buffer);

signals:
    void matReady(cv::Mat*);

private:
    QMutex buff_mutex;
    const qint64 FRAME_HEIGHT = 480;//320;
    const qint64 FRAME_WIDTH = 640;//560;
    qint64 SIZE_OF_YUV420p_FRAME = ((FRAME_HEIGHT * FRAME_WIDTH)/8)*12 ;
    QByteArray imageBuffer;
    qint64 *framecount = 0;

};

#endif // PAINTTHREAD_H
