#include <QDebug>
#include <QSerialPortInfo>

#include "cserialport.h"

//#define DEBUG_STRINGS

/*
 * @brief CSerialPort constructor
 *
 * @param {QString} comName Serial port identifier
 * @param {QObject *} parent Parent QT object
*/
CSerialPort::CSerialPort(QString comName, QObject *parent) : QThread(parent)
{
    m_quit = false;
    m_serial = new QSerialPort();
    startSerial(comName);
}

/*
 * @brief CSerialPort destructor
 *
*/
CSerialPort::~CSerialPort()
{
    m_quit = true;
    m_serial->close();
    delete m_serial;
}

/*
 * @brief CSerialPort thread that processes serial port data
 *
*/
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
            /* Parse commands. Let's specify them:
             *  <CMD> <VALUE>\r\n
             *  Possible CMD:
             *  kph <0...1024>\r\n
             *  blk <0,1,2>\r\n
             *  gas <0...1024>\r\n
             *  tmp <0...1024>\r\n
            */
            QString serialDataStr = QString(serialData);
#ifdef DEBUG_STRINGS
            qDebug() << serialDataStr;
#endif
            QStringList tokens = serialDataStr.trimmed().split(" ");
            /* Select command for execution */
            if(tokens[0] == "kph") {
                unsigned int kphValue = tokens[1].toUInt();
                emit updateKph(kphValue);
            }
            else if(tokens[0] == "blk") {
                unsigned int blinkerPosition = tokens[1].toUInt();
                emit updateBlinker(blinkerPosition);
            }
            else if(tokens[0] == "gas") {
                unsigned int gasLevel = tokens[1].toUInt();
                emit updateFuelLevel(gasLevel);

            }
            else if(tokens[0] == "tmp") {
                unsigned int temperatureValue = tokens[1].toUInt();
                emit updateTemperature(temperatureValue);
            }
        }
    }
}

/*
 * @brief CSerialPort function that stops and closes the serial port
 *
*/
void CSerialPort::stop()
{
    m_quit = true;
}

/*
 * @brief CSerialPort function that configures and starts the serial port
 *
 * @param {const QString&} portName Reference to the QString that contains the serial port to be configured
*/
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
