#ifndef MESSAGE_H
#define MESSAGE_H

/**
 * \file message.h
 * \brief Fichier de déclaration de la classe Message.
 * \author Sébastien Angibaud
 */

#include <string>

/**
 * \class Message
 * \brief Classe décrivant un message à envoyer à l'afficheur.
 * \author Sébastien Angibaud
 */
class Message
{
    public:
        Message();
        Message( const std::string & texte );

        std::string texte() const;

    private:
        /** \brief Le texte du message. */
        std::string m_texte;
};

#endif // MESSAGE_H
