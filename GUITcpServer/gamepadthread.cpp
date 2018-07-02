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

    tmr = new QTimer();
    tmr->setInterval(20);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();


//    connect(m_gamepad, &QGamepad::axisLeftXChanged,this,&GamepadThread::buttonStateChanged);
//    connect(m_gamepad, &QGamepad::axisLeftYChanged,this,&GamepadThread::buttonStateChanged);
//    connect(m_gamepad, &QGamepad::axisRightXChanged,this,&GamepadThread::buttonStateChanged);
//    connect(m_gamepad, &QGamepad::axisRightYChanged,this,&GamepadThread::buttonStateChanged);
//    connect(m_gamepad, &QGamepad::buttonAChanged,this,&GamepadThread::buttonStateChanged);
//    connect(m_gamepad, &QGamepad::buttonBChanged,this,&GamepadThread::buttonStateChanged);
//    connect(m_gamepad, &QGamepad::buttonYChanged,this,&GamepadThread::buttonStateChanged);
//    connect(m_gamepad, &QGamepad::buttonXChanged,this,&GamepadThread::buttonStateChanged);
//    connect(m_gamepad, &QGamepad::buttonL2Changed,this,&GamepadThread::buttonStateChanged);
//    connect(m_gamepad, &QGamepad::buttonR2Changed,this,&GamepadThread::buttonStateChanged);
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
    buffer.clear();
    quint8 LX =  mapRange(100*(m_gamepad->axisLeftX()),-100,100,0,255);
    quint8 LY =  mapRange(100*(m_gamepad->axisLeftY()),-100,100,0,255);
    quint8 RX =  mapRange(100*(m_gamepad->axisRightX()),-100,100,0,255);
    quint8 RY =  mapRange(100*(m_gamepad->axisRightY()),-100,100,0,255);
    quint8 A = m_gamepad->buttonA();
    quint8 B = m_gamepad->buttonB();
    quint8 X = m_gamepad->buttonX();
    quint8 Y = m_gamepad->buttonY();
    quint8 L2 = mapRange(100*(m_gamepad->buttonL2()),0,100,0,255);
    quint8 R2 = mapRange(100*(m_gamepad->buttonR2()),0,100,0,255);
    buffer.append(LX);
    buffer.append(LY);
    buffer.append(RX);
    buffer.append(RY);
    buffer.append(A);
    buffer.append(B);
    buffer.append(X);
    buffer.append(Y);
    buffer.append(L2);
    buffer.append(R2);


//    qDebug() <<L2;
//    qDebug() << R2;
    m_pTcpSocket->write(buffer);
}

void GamepadThread::buttonStateChanged(){
//    QByteArray buffer;
//    buffer.append(QString::number(m_gamepad->axisLeftX())+"S"+QString::number(m_gamepad->axisLeftY()) + "S" + QString::number(m_gamepad->axisRightX()) + "S" + QString::number(m_gamepad->axisRightY())+ "S" + QString::number(m_gamepad->buttonA())  + "S" + QString::number(m_gamepad->buttonB()) + "S" + QString::number(m_gamepad->buttonX()) + "S" + QString::number(m_gamepad->buttonY())+ "S" + QString::number(m_gamepad->buttonL2()) + "S" + QString::number(m_gamepad->buttonR2())      );
//    m_pTcpSocket->write(buffer);
}

int GamepadThread::mapRange(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
