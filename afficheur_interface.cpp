/** \file afficheur_interface.cpp
 * \brief Fichier d'implémentation de la classe AfficheurInterface.
 * \author Sébastien Angibaud
 */

#include "afficheur_interface.h"
#include "message.h"

#include <iostream>
#include <sstream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <windows.h>

// Initialisation de la variable membre statique
AfficheurInterface* AfficheurInterface::m_instance = NULL;

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe AfficheurInterface.
 */
AfficheurInterface::AfficheurInterface()
{
    // Paramétrage du port série
    m_portSerie.setPortName("COM1");
    m_portSerie.setBaudRate(QSerialPort::Baud9600);
    m_portSerie.setDataBits(QSerialPort::Data8);
    m_portSerie.setParity(QSerialPort::NoParity);
    m_portSerie.setStopBits(QSerialPort::OneStop);

    // Ouverture du port série
    m_portSerie.open(QIODevice::ReadWrite);
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe AfficheurInterface.
 */
AfficheurInterface::~AfficheurInterface()
{
    if( m_portSerie.isOpen() )
        m_portSerie.close();
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de l'instance singleton AfficheurInterface.
 * \return Le pointeur sur le singleton AfficheurInterface.
 */
AfficheurInterface* AfficheurInterface::instance()
{
    if ( m_instance == NULL )
        m_instance = new AfficheurInterface();

    return m_instance;
}

/** --------------------------------------------------------------------------------------
 * \brief Teste si la connexion est correctement établie.
 * \return \b True si la connexion est établie, \b False sinon.
 */
bool AfficheurInterface::connexionEtablie() const
{
    return m_portSerie.isOpen() && m_portSerie.isWritable();
}

/** --------------------------------------------------------------------------------------
 * \brief Envoie un message à l'afficheur.
 * \param m Une référence constance sur le message à envoyer.
 */
void AfficheurInterface::envoyerMessage( const Message & m)
{
    if ( connexionEtablie() )
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

        m_portSerie.write(data.c_str(), data.length());
        m_portSerie.flush();
        std::cout << "envoi de data=" << data.c_str() << std::endl;

        m_portSerie.waitForReadyRead(3000);
        QByteArray retour_data = m_portSerie.readAll();
        std::cout << "retour_data=" << retour_data.toStdString() << std::endl;
    }
    else
        std::cout << "connexion non etablie" << std::endl;
}

/** --------------------------------------------------------------------------------------
 * \brief Calcul du checksum d'une trame donnée. Le checksum est un simple xor.
 * \param trame La trame dont il faut calculer le checksum.
 * \return L'entier checksum calculé.
 */
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