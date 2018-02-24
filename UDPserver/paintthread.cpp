#include "paintthread.h"


void paintThread::paintFrame(QByteArray *buffer)
{
   while (buffer->size() >= SIZE_OF_YUV420p_FRAME)
    {
       qDebug() << buffer->size();
        buff_mutex.lock();

//        for (int i=0; i < buffer->size(); i++){
//            if ((buffer->at(i) == 'A') && (buffer->at(i + SIZE_OF_YUV420p_FRAME + 1) == 'B')){
//                for (int a=i+1; a < SIZE_OF_YUV420p_FRAME; a++){
//                    imageBuffer.append(buffer->at(a));
//                }

//                buffer->remove(i,SIZE_OF_YUV420p_FRAME + 1);
//                break;
//            }

//        }

        //imageBuffer = buffer->left(SIZE_OF_YUV420p_FRAME);
        imageBuffer = buffer->left(SIZE_OF_YUV420p_FRAME);
        buffer->remove(0,SIZE_OF_YUV420p_FRAME);
        framecount++;
        buff_mutex.unlock();

        cv::Mat yuvImg = cv::Mat(FRAME_HEIGHT+FRAME_HEIGHT/2,FRAME_WIDTH,CV_8UC1,imageBuffer.data());
        cv::Mat * img = new cv::Mat();
        cv::cvtColor(yuvImg,*img,cv::COLOR_YUV420p2BGR);

        qDebug() << "Frames:" << framecount;

        emit matReady(img);
    }
}
