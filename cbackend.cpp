#include <QDebug>

#include "cbackend.h"

CBackend::CBackend(QObject* object, QString comName, QObject *parent) : QObject(parent)
{
    m_dDataGauge = 0.0;
    m_dBlinkerSide = -1;
    m_dFuelLevel = 85;
    m_dTemperature = 20;
    timerId = startTimer(1000);
    serialPortThread = new CSerialPort(comName, this);
    serialPortThread->start();
}


CBackend::~CBackend()
{

}


void CBackend::timerEvent(QTimerEvent *event)
{
    (void)event;
    static int kph = 0;
    static int blinker = 3;
    kph += 1;
    if(blinker == 3)
        blinker = 4;
    else{
        blinker = 3;
    }


    setDataGauge(kph);
    setBlinkerSide(blinker);

}

