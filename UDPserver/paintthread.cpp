#include "paintthread.h"


void paintThread::paintFrame(QByteArray *buffer)
{

<<<<<<< HEAD
////        //Тестовый алгоритм
 //       long int  currupted_bytes_counter = 0;
//        while (buffer->size() > SIZE_OF_YUV420p_FRAME+2)
=======
//        //Тестовый алгоритм
//        int currupted_bytes_counter = 0;
//        while (buffer->size() >= currupted_bytes_counter + SIZE_OF_YUV420p_FRAME+2)//протестировать > либо >=
>>>>>>> 4578b3aedf344189a0295aba49ea65cd0b1b49e1
//        {
//            if((buffer->at(currupted_bytes_counter)==START_BYTE) && (buffer->at(SIZE_OF_YUV420p_FRAME + 1) == END_BYTE)){
//                buff_mutex.lock();
//                if(currupted_bytes_counter>0){//удаление всех предыдущих байтов, не являющихся частью пакета
//                    buffer->remove(0,currupted_bytes_counter);
//                }
//                for (int a=1; a < SIZE_OF_YUV420p_FRAME+1; a++){//копируем изображение в отдельный буфер без байтов пакета
//                    imageBuffer.append(buffer->at(a));
//                }
//                buffer->remove(0,SIZE_OF_YUV420p_FRAME+2);//удаление пакета из главного буфера
//                buff_mutex.unlock();
//                framecount++;

//                cv::Mat yuvImg = cv::Mat(FRAME_HEIGHT+FRAME_HEIGHT/2,FRAME_WIDTH,CV_8UC1,imageBuffer.data());
//                cv::Mat * img = new cv::Mat();
//                cv::cvtColor(yuvImg,*img,cv::COLOR_YUV420p2BGR);
//                qDebug() << "Frames:" << framecount;

//                emit matReady(img);
//                imageBuffer.clear();
//                currupted_bytes_counter = 0;//обнуление счётчика поврежд. байтов


//            }else{
//                currupted_bytes_counter++;
//                qDebug() << "CORRUPTED" << currupted_bytes_counter;
//            }

//        }




        while (buffer->size() > SIZE_OF_YUV420p_FRAME+2)
         {
            if((buffer->at(0)==START_BYTE) && (buffer->at(SIZE_OF_YUV420p_FRAME + 1) == END_BYTE)){
                buff_mutex.lock();
                for (int a=1; a < SIZE_OF_YUV420p_FRAME+1; a++){
                    imageBuffer.append(buffer->at(a));
                }
                buffer->remove(0,SIZE_OF_YUV420p_FRAME+2);
                buff_mutex.unlock();
                framecount++;

                cv::Mat yuvImg = cv::Mat(FRAME_HEIGHT + FRAME_HEIGHT/2,FRAME_WIDTH,CV_8UC1,imageBuffer.data());
                cv::Mat * img = new cv::Mat();
                cv::cvtColor(yuvImg,*img,cv::COLOR_YUV420p2BGR);

                qDebug() << "Frames:" << framecount;

                emit matReady(img);

                imageBuffer.clear();
            }else{
                buffer->remove(0,1);
//                unsigned char a = buffer->at(SIZE_OF_YUV420p_FRAME + 1);
//                a= buffer->at(SIZE_OF_YUV420p_FRAME + 2);
//                a=buffer->at(SIZE_OF_YUV420p_FRAME);
//                a= buffer->at(SIZE_OF_YUV420p_FRAME - 1);
//                currupted_bytes_counter++;
                qDebug() << "CORRUPTED";
             //   if(currupted_bytes_counter > 5) buffer->clear();

            }
        }

}
