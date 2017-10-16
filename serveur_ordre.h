#ifndef SERVER_H
#define SERVER_H

/**
 * \file serveur_ordre.h
 * \brief Fichier de déclaration de la classe ServeurOrdre.
 * \author Sébastien Angibaud
 */

#include <QObject>
#include <QTcpSocket>

class QTcpServer;
class QTcpSocket;
class QNetworkSession;

/**
 * \class ServeurOrdre
 * \brief Classe décrivant un serveur recevant des ordres des clients.
 * \author Sébastien Angibaud
 */
class ServeurOrdre : public QObject{
    Q_OBJECT

public:
    ServeurOrdre();

private slots:
    void sessionOuverte();
    void connexionClient();
    void lireTexte();
    void deconnexionClient();
    void afficherErreur(QAbstractSocket::SocketError socketError);

private:
    void envoiTexte( const std::string& s);

private:
    /** \brief Un pointeur sur le socket général d'écoute. */
    QTcpServer *m_tcpServer;

    /** \brief Un pointeur sur le socket client. */
    QTcpSocket *m_socketClient;

    /** \brief UN pointeur sur la session de connexion. */
    QNetworkSession *m_networkSession;

    /** \brief Le nombre d'octets lues. */
    quint16 m_nbOctetsLus;
};

#endif
