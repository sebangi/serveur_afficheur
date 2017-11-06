#ifndef GESTIONNAIRE_ORDRE_H
#define GESTIONNAIRE_ORDRE_H

/**
 * \file gestionnaire_ordre.h
 * \brief Fichier de déclaration de la classe GestionnaireOrdre.
 * \author Sébastien Angibaud
 */

#include "message_client.h"
#include <map>
#include <QString>

/**
 * \class GestionnaireOrdre
 * \brief Classe décrivant un gestionnaire des ordres des clients.
 * \author Sébastien Angibaud
 */
class GestionnaireOrdre
{
    public:
        GestionnaireOrdre();

        MessageClient traiterOrdre( const MessageClient & s);

    private:
        MessageClient traiterOrdreAfficher(const MessageClient &mess);
        MessageClient traiterOrdreCouleur(const MessageClient &mess);
        MessageClient traiterSetStringVariable(const MessageClient &mess);
        MessageClient traiterSetIntVariable(const MessageClient &mess);
        MessageClient traiterGetStringVariable(const MessageClient &mess);
        MessageClient traiterGetIntVariable(const MessageClient &mess);

    private:
        /** \brief Les variables de types string. */
        std::map<QString, QString> m_string_variables;

        /** \brief Les variables de types int. */
        std::map<QString, int> m_int_variables;
};

#endif // GESTIONNAIRE_ORDRE_H
