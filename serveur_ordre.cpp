/** \file serveur_ordre.cpp
 * \brief Fichier d'implémentation de la classe ServeurOrdre.
 * \author Sébastien Angibaud
 */

#include "serveur_ordre.h"

#include <QtNetwork>
#include <stdlib.h>
#include <iostream>

//###############################################################################################################
// Constructeur
/** --------------------------------------------------------------------------------------
 * \brief Constructeur par défaut de la classe ServeurOrdre.
 */
ServeurOrdre::ServeurOrdre()
:   m_tcpServer(0), m_networkSession(0)
{
    m_nbOctetsLus = 0;
    QNetworkConfigurationManager manager;
    QNetworkConfiguration config = manager.defaultConfiguration();
    m_networkSession = new QNetworkSession(config, this);

    // La méthode sessionOuverte sera appelée sur le signal opened
    connect(m_networkSession, SIGNAL(opened()), this, SLOT(sessionOuverte()));

    // La méthode connexionClient sera appelée sur le signal newConnection
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(connexionClient()));

    // Demande d'ouverture de la session
    m_networkSession->open();
}

/** --------------------------------------------------------------------------------------
 * \brief Méthode appelée lors de l'ouverture de session.
 */
void ServeurOrdre::sessionOuverte()
{
    std::cout << "ServeurOrdre::sessionOuverte()" << std::endl;

    m_tcpServer = new QTcpServer(this);

    if (!m_tcpServer->listen(QHostAddress::Any, 53000)) {
        std::cout << "Le serveur n'a pas été correctement lancee." << std::endl;
    }
    else
    {
        std::cout << "Le serveur est pret \n\nIP: " << m_tcpServer->serverAddress().toString().toStdString()
                  << std::endl << "port: " << m_tcpServer->serverPort() << std::endl
                  <<  "Lancez l'application Client maintenant." << std::endl;
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Méthode appelée lors de l'ouverture de communication'une demande de connexion d'un client.
 */
void ServeurOrdre::connexionClient()
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "1- connexion d'un nouveau client" << std::endl;

    m_socketClient = m_tcpServer->nextPendingConnection();

    connect(m_socketClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
    connect(m_socketClient, SIGNAL(readyRead()), this, SLOT(lireTexte()));
}

/** --------------------------------------------------------------------------------------
 * \brief Méthode appelée lors de la réception d'un texte.
 */
void ServeurOrdre::lireTexte()
{
    QDataStream in(m_socketClient);
    in.setVersion(QDataStream::Qt_4_0);

    if (m_nbOctetsLus == 0) {
        if (m_socketClient->bytesAvailable() < (int)sizeof(quint16))
            return;


        in >> m_nbOctetsLus;
    }

    if (m_socketClient->bytesAvailable() < m_nbOctetsLus)
        return;

    QString texte;
    in >> texte;

    std::cout << "2- Reception de : " ;
    std::cout << texte.toStdString() << std::endl;
    m_nbOctetsLus = 0;

    // envoie de la réponse
    envoiTexte("Reponse envoyee par le serveur.");
}

/** --------------------------------------------------------------------------------------
 * \brief Méthode appelée lors d'une déconnexion du client.
 */
void ServeurOrdre::deconnexionClient()
{
    std::cout << "4- Deconnexion client" << std::endl;

    disconnect(m_socketClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
    disconnect(m_socketClient, SIGNAL(readyRead()), this, SLOT(lireTexte()));

    m_socketClient->deleteLater();
}

/** --------------------------------------------------------------------------------------
 * \brief Méthode envoyant un texte donné au client.
 * \param s Une référence contantes sur le texte à envoyer.
 */
void ServeurOrdre::envoiTexte( const std::string& s )
{
    std::cout << "3- Envoi de : " << s << std::endl;
    QString texte = tr(s.c_str());
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << texte;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    m_socketClient->write(block);
}

/** --------------------------------------------------------------------------------------
 * \brief Méthode appelée lors d'un déclenchement d'une exception sur un socket.
 * \param socketError L'erreur survenue.
 */
void ServeurOrdre::afficherErreur(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        std::cout << "Le serveur n'a pa ete trouve. Verifiez le parametrage du serveur et du port." << std::endl;
        break;
    case QAbstractSocket::ConnectionRefusedError:
        std::cout << "La communication a ete refusee. Verifiez que le serveur est pret, ainsi que le parametrage du serveur et du port." << std::endl;
        break;
    default:
        std::cout << "L'erreur suivante s'est produite : " << m_socketClient->errorString().toStdString() << std::endl;
    }
}

