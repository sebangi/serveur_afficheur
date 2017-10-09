#include "afficheurinterface.h"
#include "message.h"

#include <iostream>
#include <sstream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <windows.h>

AfficheurInterface* AfficheurInterface::m_instance = NULL;

AfficheurInterface::AfficheurInterface()
{
    m_serial.setPortName("COM1");
    m_serial.setBaudRate(QSerialPort::Baud9600);
    m_serial.setDataBits(QSerialPort::Data8);
    m_serial.setParity(QSerialPort::NoParity);
    m_serial.setStopBits(QSerialPort::OneStop);

    m_serial.open(QIODevice::ReadWrite);
}

AfficheurInterface::~AfficheurInterface()
{
    if( m_serial.isOpen() )
        m_serial.close();
}

AfficheurInterface* AfficheurInterface::Instance()
{
    if ( m_instance == NULL )
        m_instance = new AfficheurInterface();

    return m_instance;
}

bool AfficheurInterface::connexion_etablie() const
{
    return m_serial.isOpen() && m_serial.isWritable();

}

void AfficheurInterface::envoyerMessage( const message & m)
{
    if ( connexion_etablie() )
    {
        std::string startOfTrame = "<ID01>";
        std::string startOfMessage = "<L1><PA><FE><MA><WC><FE>";
        std::string mess = startOfMessage + m.texte();

        int checkSum = calculerChecksum(mess.c_str());
        std::string endOfTrame = "<E>";

        std::stringstream hx;
        std::stringstream hh;
        hx << std::uppercase << std::hex << checkSum; // int decimal_value
        if (checkSum < 16)
            hh << "0";
        hh << hx.str();
        std::string res(hh.str());
        res += "\0";

        std::string data = startOfTrame + mess + res + endOfTrame;

        m_serial.write(data.c_str(), data.length());
        m_serial.flush();
        std::cout << "envoi de data=" << data.c_str() << std::endl;

        m_serial.waitForReadyRead(3000);
        QByteArray retour_data = m_serial.readAll();
        std::cout << "retour_data=" << retour_data.toStdString() << std::endl;
    }
    else
        std::cout << "connexion non etablie" << std::endl;
}

int AfficheurInterface::calculerChecksum(const char* trame) const
{
    unsigned char c, checksum=0;
    int i=0;

    while ((c=trame[ i ])!=0)
    {
        checksum^=c;
        i++;
    }

    return checksum;
}
