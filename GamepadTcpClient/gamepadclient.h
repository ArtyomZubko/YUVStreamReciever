#ifndef GAMEPADCLIENT_H
#define GAMEPADCLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QtGamepad/QGamepad>
#include <QtGamepad/QGamepadManager>
#include <QTimer>

class GamepadClient : public QObject
{
    Q_OBJECT
public:
    explicit GamepadClient(QString,int);
    int mapRange(int x, int in_min, int in_max, int out_min, int out_max);

signals:

public slots:
    void updateTime();
    void threadFinished();
    void connectToHost();

private:
    QTcpSocket* pTcpSocket;
    QGamepad *gamepad;
    QTimer *timer;
    QByteArray buffer;
    QString hostName;
    int hostPort;
};

#endif // GAMEPADCLIENT_H
