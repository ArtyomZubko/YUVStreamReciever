#include "paintthread.h"


paintThread::paintThread()
{
    connect(this, SIGNAL(finished()),this, SLOT(threadFinished()));
}

void paintThread::paintFrame(QByteArray *buffer)
{
   tcp_buffer = buffer;
   while (buffer->size() >= SIZE_OF_YUV420p_FRAME)
    {
       //qDebug() << "start to calc";
        buff_mutex.lock();
        imageBuffer = buffer->left(SIZE_OF_YUV420p_FRAME);
        buffer->remove(0,SIZE_OF_YUV420p_FRAME);
        //framecount++;
        buff_mutex.unlock();

        cv::Mat yuvImg = cv::Mat(FRAME_HEIGHT + FRAME_HEIGHT/2,FRAME_WIDTH,CV_8UC1,imageBuffer.data());
        cv::Mat * img = new cv::Mat();
        cv::cvtColor(yuvImg,*img,cv::COLOR_YUV420p2BGR);

        //qDebug() << "Frames:" << framecount;

        emit matReady(img);
   }
}

void paintThread::threadFinished()
{
    buff_mutex.unlock();
    tcp_buffer->clear();
}
