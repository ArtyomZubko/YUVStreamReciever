#include "paintthread.h"


void paintThread::paintFrame(QByteArray *buffer)
{

        buff_mutex.lock();
        while (buffer->size() >= SIZE_OF_YUV420p_FRAME+2)
         {
            if((buffer->at(0)==0x01) && (buffer->at(SIZE_OF_YUV420p_FRAME + 1) == 0x02)){
                for (int a=1; a < SIZE_OF_YUV420p_FRAME+1; a++){
                    imageBuffer.append(buffer->at(a));
                }
                buffer->remove(0,SIZE_OF_YUV420p_FRAME+2);
                buff_mutex.unlock();
                framecount++;
                cv::Mat yuvImg = cv::Mat(FRAME_HEIGHT+FRAME_HEIGHT/2,FRAME_WIDTH,CV_8UC1,imageBuffer.data());
                cv::Mat * img = new cv::Mat();
                cv::cvtColor(yuvImg,*img,cv::COLOR_YUV420p2BGR);

                qDebug() << "Frames:" << framecount;

                emit matReady(img);

                imageBuffer.clear();
            }else{
                buffer->remove(0,1);
                buff_mutex.unlock();
            }
}
}
