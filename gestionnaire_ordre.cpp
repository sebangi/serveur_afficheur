/** \file gestionnaire_ordre.cpp
 * \brief Fichier d'implémentation de la classe GestionnaireOrdre.
 * \author Sébastien Angibaud
 */

#include "gestionnaire_ordre.h"

#include "afficheur_interface.h"
#include "message_afficheur.h"

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
    if ( mess.valide() )
    {
        std::cout << "traitement du message n°" << mess.numero() << std::endl;
        std::cout << "\t- ordre = " << mess.ordre().toStdString() << std::endl;
        if ( mess.a_parametre() )
            std::cout << "\t- parametre = " << mess.parametre().toStdString() << std::endl;

        if ( mess.ordre().compare("AFFICHER") == 0 && mess.a_parametre() )
        {
            MessageAfficheur mess_afficheur( mess.parametre() );
            AfficheurInterface::instance()->envoyerMessage( mess_afficheur );
        }

        return MessageClient(mess.numero(),"ordre bien reçu");
    }
    else
    {
        std::cout << "message invalide : pas de traitement de : " << mess.texte().toStdString() << std::endl;
        return MessageClient(0,"message invalide : " + mess.texte());
    }
}
