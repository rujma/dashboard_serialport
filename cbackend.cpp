#include <QDebug>

#include "cbackend.h"

#define ANALOG_PRECISION    1024

CBackend::CBackend(QObject* object, QString comName, QObject *parent) : QObject(parent)
{
    m_dDataGauge = 0.0;
    m_dBlinkerSide = -1;
    m_dFuelLevel = 85;
    m_dTemperature = 20;
#ifdef TEST_MODE
    timerId = startTimer(1000);
#endif
    /* Create CSerialPort instance */
    serialPortThread = new CSerialPort(comName, this);
    /* Connect SIGNALS */
    connect(serialPortThread, SIGNAL(updateKph(unsigned int)), this, SLOT(backendUpdateKph(unsigned int)));
    connect(serialPortThread, SIGNAL(updateBlinker(unsigned int)), this, SLOT(backendUpdateBlinker(unsigned int)));
    connect(serialPortThread, SIGNAL(updateTemperature(unsigned int)), this, SLOT(backendUpdateTemperature(unsigned int)));
    connect(serialPortThread, SIGNAL(updateFuelLevel(unsigned int)), this, SLOT(backendUpdateFuelLevel(unsigned int)));
    /* Start CSerialPort thread */
    serialPortThread->start();
}


CBackend::~CBackend()
{

}

#ifdef TEST_MODE
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
#endif

void CBackend::backendUpdateKph(unsigned int kphValue)
{
    setDataGauge(kphValue);
}

void CBackend::backendUpdateBlinker(unsigned int blinkerPosition)
{
    if(blinkerPosition != 0)
    {
        /* Blinker value is either 3 for left or 4 for right */
        blinkerPosition += 2;
    }
    setBlinkerSide(blinkerPosition);
}


void CBackend::backendUpdateTemperature(unsigned int temperatureValue)
{
    /* Temperature range is from 0 to 100 */
    double tempNorm = (double)((double)temperatureValue / (double)ANALOG_PRECISION) * 100;
    setTemperature(tempNorm);
}


void CBackend::backendUpdateFuelLevel(unsigned int gasLevel)
{
    /* Fuel range is from 0 to 100 */
    double fuelNorm = (double)((double)gasLevel / (double)ANALOG_PRECISION) * 100;
    setFuelLevel(fuelNorm);
}


