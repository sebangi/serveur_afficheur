#include "server_ordre.h"

#include <QtNetwork>
#include <stdlib.h>
#include <iostream>

//###############################################################################################################
// Constructeur
ServeurOrdre::ServeurOrdre()
:   tcpServer(0), networkSession(0)
{
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
// Méthode appelée lors de l'ouverture de session
void ServeurOrdre::sessionOuverte()
{
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
    SocketClient = tcpServer->nextPendingConnection();

    connect(SocketClient, SIGNAL(disconnected()),
            SocketClient, SLOT(deleteLater()));

    envoiTexte("Ce texte a ete envoye par le serveur.");

    SocketClient->disconnectFromHost();
}

//###############################################################################################################
// Méthode envoyant un texte au client
void ServeurOrdre::envoiTexte( const std::string& s )
{
    std::cout << "Envoi de : " << s << std::endl;
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
