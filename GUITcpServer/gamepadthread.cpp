#include "gamepadthread.h"

GamepadThread::GamepadThread(QString adress,int port)
{
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(adress, port);
    connect(m_pTcpSocket, SIGNAL(connected()), this,SLOT(slotConnected()));

    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    if (gamepads.isEmpty()) {
        return;
    }

    m_gamepad = new QGamepad(*gamepads.begin(), this);

    tmr = new QTimer();
    tmr->setInterval(10);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();


    connect(m_gamepad, &QGamepad::axisLeftXChanged, this, [](double value){
        qDebug() << "Left X" << value;
    });
    connect(m_gamepad, &QGamepad::axisLeftYChanged, this, [](double value){
        qDebug() << "Left Y" << value;
    });
    connect(m_gamepad, &QGamepad::axisRightXChanged, this, [](double value){
        qDebug() << "Right X" << value;
    });
    connect(m_gamepad, &QGamepad::axisRightYChanged, this, [](double value){
        qDebug() << "Right Y" << value;
    });
    connect(m_gamepad, &QGamepad::buttonAChanged, this, [](bool pressed){
        qDebug() << "Button A" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonBChanged, this, [](bool pressed){
        qDebug() << "Button B" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonXChanged, this, [](bool pressed){
        qDebug() << "Button X" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonYChanged, this, [](bool pressed){
        qDebug() << "Button Y" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonL1Changed, this, [](bool pressed){
        qDebug() << "Button L1" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonR1Changed, this, [](bool pressed){
        qDebug() << "Button R1" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonL2Changed, this, [](double value){
        qDebug() << "Button L2: " << value;
    });
    connect(m_gamepad, &QGamepad::buttonR2Changed, this, [](double value){
        qDebug() << "Button R2: " << value;
    });
    connect(m_gamepad, &QGamepad::buttonSelectChanged, this, [](bool pressed){
        qDebug() << "Button Select" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonStartChanged, this, [](bool pressed){
        qDebug() << "Button Start" << pressed;
    });
    connect(m_gamepad, &QGamepad::buttonGuideChanged, this, [](bool pressed){
        qDebug() << "Button Guide" << pressed;
    });
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
    buffer.append(QString::number(m_gamepad->buttonA()));
    m_pTcpSocket->write(buffer + '\n');

}
