#include <QDebug>
#include <QSerialPort>
#include "cbackend.h"

CBackend::CBackend(QObject* object, QObject *parent) : QObject(parent)
{
    m_dDataGauge = 0.0;
    m_dBlinkerSide = -1;
    timerId = startTimer(1000);
}


CBackend::~CBackend()
{

}

void CBackend::startSerial(const QString &portName)
{
    run();
}

void CBackend::run()
{
    QSerialPort serial;
    /* Here we read the data coming from the serial port */
    for(;;)
    {

    }
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

