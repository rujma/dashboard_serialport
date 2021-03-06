#ifndef CSERIALPORT_H
#define CSERIALPORT_H

#include <QObject>
#include <QThread>
#include <QtDebug>
#include <cmath>
#include <QFile>
#include <QSerialPort>

//#define DEBUG_STRINGS

class CSerialPort : public QThread
{
    Q_OBJECT
public:
    explicit CSerialPort(QString comName, QObject *parent = nullptr);
    ~CSerialPort();
    void run();
    void stop();
    void startSerial(const QString &portName);

private:
    QSerialPort *m_serial;
    bool m_quit;

signals:
    void updateBlinker(unsigned int); /* Set left, right blinker or off blinker */
    void updateKph(unsigned int); /* Set speedometer */
    void updateTemperature(unsigned int); /* Set oil temperature */
    void updateFuelLevel(unsigned int);   /* Set fuel level */


};


#endif // CSERIALPORT_H
