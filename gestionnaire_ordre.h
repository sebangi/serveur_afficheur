#ifndef GESTIONNAIRE_ORDRE_H
#define GESTIONNAIRE_ORDRE_H

/**
 * \file gestionnaire_ordre.h
 * \brief Fichier de déclaration de la classe GestionnaireOrdre.
 * \author Sébastien Angibaud
 */

#include "message_client.h"

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
};

#endif // GESTIONNAIRE_ORDRE_H
