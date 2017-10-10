#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>

class QTcpServer;
class QTcpSocket;
class QNetworkSession;

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
    QTcpServer *tcpServer; // Le socket général
    QTcpSocket *SocketClient; // Le socket client
    QNetworkSession *networkSession; // La session de connexion
    quint16 blockSize;
};

#endif
