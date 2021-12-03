#ifndef CBACKEND_H
#define CBACKEND_H


#include <QPointF>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QThread>
#include "cserialport.h"


class CBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double getDataGauge READ getDataGauge NOTIFY valueDataGaugeChanged);
    Q_PROPERTY(int getBlinkerSide READ getBlinkerSide NOTIFY blinkerSideChanged);
    Q_PROPERTY(int getFuelLevel READ getFuelLevel NOTIFY fuelLevelChanged);
    Q_PROPERTY(int getTemperature READ getTemperature NOTIFY temperatureChanged);

public:
    explicit CBackend(QObject* object, QString comName, QObject *parent = nullptr);
    ~CBackend();

    /* Propery GET */
    double getDataGauge(){
        return m_dDataGauge;
    }

    int getBlinkerSide() {
        return m_dBlinkerSide;
    }

    int getFuelLevel() {
        return m_dFuelLevel;
    }

    int getTemperature() {
        return m_dTemperature;
    }

    /* Property SET */
    void setDataGauge(double value){
        if (value == m_dDataGauge)
            return;
        m_dDataGauge = value;
        emit valueDataGaugeChanged();
    }

    void setBlinkerSide(int value){
        if (value == m_dBlinkerSide)
            return;
        m_dBlinkerSide = value;
        emit blinkerSideChanged();
    }

    void setFuelLevel(int value){
        if (value == m_dFuelLevel)
            return;
        m_dFuelLevel = value;
        emit fuelLevelChanged();
    }

    void setTemperature(int value){
        if (value == m_dTemperature)
            return;
        m_dTemperature = value;
        emit temperatureChanged();
    }



signals:
    void valueDataGaugeChanged();
    void blinkerSideChanged();
    void fuelLevelChanged();
    void temperatureChanged();


public slots:

private:
    double m_dDataGauge;
    int m_dBlinkerSide;
    int m_dFuelLevel;
    int m_dTemperature;
    int timerId;

    CSerialPort *serialPortThread; //Pointer to CSerialPort thread

protected:
    void timerEvent(QTimerEvent *event);


};


#endif // CBACKEND_H
