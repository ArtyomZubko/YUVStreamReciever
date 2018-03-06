#include "gamepadthread.h"

GamepadThread::GamepadThread(QString adress,int port)
{
//    socket = new QUdpSocket(this);
//    socket->bind(QHostAddress::Any, 1234);
//    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(adress, port);
    connect(m_pTcpSocket, SIGNAL(connected()), this,SLOT(slotConnected()));

    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    if (gamepads.isEmpty()) {
        return;
    }

    m_gamepad = new QGamepad(*gamepads.begin(), this);

//    tmr = new QTimer();
//    tmr->setInterval(10);
//    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
//    tmr->start();


    connect(m_gamepad, &QGamepad::axisLeftXChanged,this,&GamepadThread::buttonStateChanged);
    connect(m_gamepad, &QGamepad::axisLeftYChanged,this,&GamepadThread::buttonStateChanged);
    connect(m_gamepad, &QGamepad::axisRightXChanged,this,&GamepadThread::buttonStateChanged);
    connect(m_gamepad, &QGamepad::axisRightYChanged,this,&GamepadThread::buttonStateChanged);
    connect(m_gamepad, &QGamepad::buttonAChanged,this,&GamepadThread::buttonStateChanged);
    connect(m_gamepad, &QGamepad::buttonBChanged,this,&GamepadThread::buttonStateChanged);
    connect(m_gamepad, &QGamepad::buttonYChanged,this,&GamepadThread::buttonStateChanged);
    connect(m_gamepad, &QGamepad::buttonXChanged,this,&GamepadThread::buttonStateChanged);
    connect(m_gamepad, &QGamepad::buttonL2Changed,this,&GamepadThread::buttonStateChanged);
    connect(m_gamepad, &QGamepad::buttonR2Changed,this,&GamepadThread::buttonStateChanged);
}

void GamepadThread::slotConnected()
{
    qDebug() << "connected";


}

void GamepadThread::slotSendToServer()
{


}

void GamepadThread::updateTime()
{
    QByteArray buffer;
    buffer.append(QString::number(m_gamepad->axisLeftX())+"S"+QString::number(m_gamepad->axisLeftY()) + "S" + QString::number(m_gamepad->axisRightX()) + "S" + QString::number(m_gamepad->axisRightY())+ "S" + QString::number(m_gamepad->buttonA())  + "S" + QString::number(m_gamepad->buttonB()) + "S" + QString::number(m_gamepad->buttonX()) + "S" + QString::number(m_gamepad->buttonY())+ "S" + QString::number(m_gamepad->buttonL2()) + "S" + QString::number(m_gamepad->buttonR2())      );
//    buffer.append("{ \"LX\":" + QString::number(m_gamepad->axisLeftX())
//                  + ", \"LY\":" + QString::number(m_gamepad->axisLeftY())
//                  + ", \"RX\":" + QString::number(m_gamepad->axisRightX())
//                  + ", \"RY\":" + QString::number(m_gamepad->axisRightY())
//                  + ", \"A\":" + QString::number(m_gamepad->buttonA())
//                  + ", \"B\":" + QString::number(m_gamepad->buttonB())
//                  + ", \"X\":" + QString::number(m_gamepad->buttonX())
//                  + ", \"Y\":" + QString::number(m_gamepad->buttonY())
//                  + ", \"LT\":" + QString::number(m_gamepad->buttonL2())
//                  + ", \"RT\":" + QString::number(m_gamepad->buttonR2())
//                  +"} ");


    m_pTcpSocket->write(buffer);

}

void GamepadThread::buttonStateChanged(){
    QByteArray buffer;
    buffer.append(QString::number(m_gamepad->axisLeftX())+"S"+QString::number(m_gamepad->axisLeftY()) + "S" + QString::number(m_gamepad->axisRightX()) + "S" + QString::number(m_gamepad->axisRightY())+ "S" + QString::number(m_gamepad->buttonA())  + "S" + QString::number(m_gamepad->buttonB()) + "S" + QString::number(m_gamepad->buttonX()) + "S" + QString::number(m_gamepad->buttonY())+ "S" + QString::number(m_gamepad->buttonL2()) + "S" + QString::number(m_gamepad->buttonR2())      );
    m_pTcpSocket->write(buffer);
}

