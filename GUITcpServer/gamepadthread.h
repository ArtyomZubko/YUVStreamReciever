#ifndef GAMEPADTHREAD_H
#define GAMEPADTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QTcpSocket>
#include <QtGamepad/QGamepad>
#include <QtGamepad/QGamepadManager>
#include <QTimer>

class GamepadThread: public QThread
{
    Q_OBJECT


public:
    GamepadThread(QString,int);

    void run()
    {
        exec();
    }
int mapRange(int x, int in_min, int in_max, int out_min, int out_max);
signals:

public slots:
    void slotConnected();
    void slotSendToServer();
    void updateTime();
    void buttonStateChanged();
    void threadFinished();

private:
    QTcpSocket* m_pTcpSocket;
    QGamepad *m_gamepad;
    QTimer *tmr;
    QByteArray buffer;
};


#endif // GAMEPADTHREAD_H
