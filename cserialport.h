#ifndef CSERIALPORT_H
#define CSERIALPORT_H

#include <QObject>
#include <QThread>
#include <QtDebug>
#include <cmath>
#include <QFile>
#include <QSerialPort>

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
    void updateBlinker(int); /* Set left, right blinker or off blinker */
    void updateKph(int); /* Set speedometer */
    void updateTemperature(double); /* Set oil temperature */
    void updateFuelLevel(double);   /* Set fuel level */


};


#endif // CSERIALPORT_H
