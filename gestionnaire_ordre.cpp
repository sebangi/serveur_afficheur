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
 * \brief Traite un ordre donné.
 * \param mess L'ordre à traiter.
 * \return Le message à renvoyer au client.
 */
MessageClient GestionnaireOrdre::traiterOrdre(const MessageClient &mess)
{
    MessageClient result;

    if ( mess.valide() )
    {
        std::cout << "traitement du message n°" << mess.numero() << std::endl;
        std::cout << "\t- ordre = " << mess.ordre().toStdString() << std::endl;
        if ( mess.a_parametre() )
            std::cout << "\t- parametre = " << mess.parametre().toStdString() << std::endl;

        if ( mess.ordre().compare("AFFICHER") == 0 && mess.a_parametre() )
            result = traiterOrdreAfficher(mess);
    }
    else
    {
        std::cout << "message invalide : pas de traitement de : " << mess.texte().toStdString() << std::endl;
        result = MessageClient(0,"message invalide : " + mess.texte());
    }

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe AfficheurInterface.
 * \param s Le message client reçu.
 * \return Le message à renvoyer au client.
 */
MessageClient GestionnaireOrdre::traiterOrdreAfficher(const MessageClient &mess)
{
    if ( AfficheurInterface::instance()->connexionEtablie() )
    {
        MessageAfficheur mess_afficheur( mess.parametre() );
        AfficheurInterface::instance()->envoyerMessage( mess_afficheur );

        return MessageClient(mess.numero(),"Le message a ete envoye à l'afficheur");
    }
    else
        return MessageClient(mess.numero(),"Erreur : le serveur n'est pas connecte a l'afficheur");
}
