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

public:
    explicit CBackend(QObject* object, QString comName, QObject *parent = nullptr);
    ~CBackend();

    double getDataGauge(){
        return m_dDataGauge;
    }

    int getBlinkerSide() {
        return m_dBlinkerSide;
    }

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

signals:
    void valueDataGaugeChanged();
    void blinkerSideChanged();

public slots:

private:
    double m_dDataGauge;
    int m_dBlinkerSide;
    int timerId;

    CSerialPort *serialPortThread; //Pointer to CSerialPort thread

protected:
    void timerEvent(QTimerEvent *event);


};


#endif // CBACKEND_H
