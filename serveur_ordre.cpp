#include "serveur_ordre.h"

#include <QtNetwork>
#include <stdlib.h>
#include <iostream>

//###############################################################################################################
// Constructeur
ServeurOrdre::ServeurOrdre()
:   tcpServer(0), networkSession(0)
{
    blockSize = 0;
    QNetworkConfigurationManager manager;
    QNetworkConfiguration config = manager.defaultConfiguration();
    networkSession = new QNetworkSession(config, this);

    // La méthode sessionOuverte sera appelée sur le signal opened
    connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOuverte()));

    // Ouverture de la session
    networkSession->open();

    // La méthode connexionClient sera appelée sur le signal newConnection
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(connexionClient()));
}

//###############################################################################################################
/** \brief Méthode appelée lors de l'ouverture de session.
*/
void ServeurOrdre::sessionOuverte()
{
    std::cout << "ServeurOrdre::sessionOuverte()" << std::endl;

    tcpServer = new QTcpServer(this);

    if (!tcpServer->listen(QHostAddress::Any, 53000)) {
        std::cout << "Le serveur n'a pas été correctement lancee." << std::endl;
    }
    else
    {
        std::cout << "Le serveur est pret \n\nIP: " << tcpServer->serverAddress().toString().toStdString()
                  << std::endl << "port: " << tcpServer->serverPort() << std::endl
                  <<  "Lancez l'application Client maintenant." << std::endl;
    }
}

//###############################################################################################################
// Méthode appelée lors d'e l'ouverture de communication'une demande de connexion d'un client
void ServeurOrdre::connexionClient()
{
    std::cout << "-----------------------------" << std::endl;
    std::cout << "1- connexion d'un nouveau client" << std::endl;

    SocketClient = tcpServer->nextPendingConnection();

    connect(SocketClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
    connect(SocketClient, SIGNAL(readyRead()), this, SLOT(lireTexte()));
}

//###############################################################################################################
// Méthode appelée lors de la réception d'un texte
void ServeurOrdre::lireTexte()
{
    QDataStream in(SocketClient);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (SocketClient->bytesAvailable() < (int)sizeof(quint16))
            return;


        in >> blockSize;
    }

    if (SocketClient->bytesAvailable() < blockSize)
        return;

    QString texte;
    in >> texte;

    std::cout << "2- Reception de : " ;
    std::cout << texte.toStdString() << std::endl;
    blockSize = 0;

    // envoie de la réponse
    envoiTexte("Reponse envoyee par le serveur.");
}

//###############################################################################################################
// Méthode appelée lors d'une déconnexion du client
void ServeurOrdre::deconnexionClient()
{
    std::cout << "4- Deconnexion client" << std::endl;

    disconnect(SocketClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
    disconnect(SocketClient, SIGNAL(readyRead()), this, SLOT(lireTexte()));

    SocketClient->deleteLater();
    //QThread::sleep(3);
}

//###############################################################################################################
// Méthode envoyant un texte au client
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

    SocketClient->write(block);
}

//###############################################################################################################
// Méthode appelée lors d'un déclenchement d'une exception sur un socket
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
        std::cout << "L'erreur suivante s'est produite : " << SocketClient->errorString().toStdString() << std::endl;
    }
}

