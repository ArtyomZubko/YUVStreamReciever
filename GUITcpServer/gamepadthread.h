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
#include <QJsonObject>

class GamepadThread: public QThread
{
    Q_OBJECT


public:
    GamepadThread(QString,int);

    void run()
    {
        exec();
    }

signals:

public slots:
    void slotConnected();
    void slotSendToServer();
    void updateTime();
    void buttonStateChanged();

private:
    QTcpSocket* m_pTcpSocket;
    QGamepad *m_gamepad;
    QTimer *tmr;
};


#endif // GAMEPADTHREAD_H
