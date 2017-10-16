#ifndef MESSAGE_AFFICHEUR_H
#define MESSAGE_AFFICHEUR_H

/**
 * \file MessageAfficheur.h
 * \brief Fichier de déclaration de la classe MessageAfficheur.
 * \author Sébastien Angibaud
 */

#include <QString>

/**
 * \class MessageAfficheur
 * \brief Classe décrivant un message à envoyer à l'afficheur.
 * \author Sébastien Angibaud
 */
class MessageAfficheur
{
    public:
        MessageAfficheur();
        MessageAfficheur( const QString & texte );

        QString texte() const;

    private:
        /** \brief Le texte du message. */
        QString m_texte;
};

#endif // MESSAGE_AFFICHEUR_H
