#ifndef MESSAGE_CLIENT_H
#define MESSAGE_CLIEN_H

/**
 * \file message_client.h
 * \brief Fichier de déclaration de la classe GestionnaireOrdre.
 * \author Sébastien Angibaud
 */

#include <QString>

/**
 * \class MessageClient
 * \brief Classe décrivant un message d'un client ou un message à envoyer à un client.
 * \author Sébastien Angibaud
 */
class MessageClient
{
    public:
        MessageClient();
        MessageClient(const QString & texte);

        QString texte() const;

    private:
        /** \brief Le texte du message. */
        QString m_texte;
};

#endif // MESSAGE_CLIEN_H
