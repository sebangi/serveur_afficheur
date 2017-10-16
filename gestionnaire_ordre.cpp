/** \file gestionnaire_ordre.cpp
 * \brief Fichier d'implémentation de la classe GestionnaireOrdre.
 * \author Sébastien Angibaud
 */

#include "gestionnaire_ordre.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe GestionnaireOrdre.
 */
GestionnaireOrdre::GestionnaireOrdre()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe AfficheurInterface.
 * \param s Le message client reçu.
 * \return Le message à renvoyer au client.
 */
MessageClient GestionnaireOrdre::traiterOrdre(const MessageClient &mess)
{
    std::cout << "traitement de " << mess.texte().toStdString() << std::endl;

    return MessageClient("ordre bien reçu");
}
