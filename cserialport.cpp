#include <QDebug>
#include <QSerialPortInfo>

#include "cserialport.h"


CSerialPort::CSerialPort(QString comName, QObject *parent) : QThread(parent)
{
    m_quit = false;
    m_serial = new QSerialPort();
    //const auto infos = QSerialPortInfo::availablePorts();
    //for (const QSerialPortInfo &info : infos) {
    //    qDebug() << info.portName();
    //}
    startSerial(comName);
}

CSerialPort::~CSerialPort()
{
    m_quit = true;
    m_serial->close();
    delete m_serial;
}

void CSerialPort::run()
{
    if(!m_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "Serial Port offline";
        return;
    }
    else
    {
        qDebug() << "Serial Port online";
    }
    /* Here we read the data coming from the serial port */
    while (!m_quit) {
        /* Wait indefinately for serial data */
        if (m_serial->waitForReadyRead(-1))
        {
            QByteArray serialData = m_serial->readAll();
            while (m_serial->waitForReadyRead(10))
                serialData += m_serial->readAll();
            /* Parse commands */
            qDebug() << serialData;
        }
    }

}
void CSerialPort::stop()
{

}

void CSerialPort::startSerial(const QString &portName)
{
    /* Configure the serial port */
    m_serial->setPortName(portName);
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
}
