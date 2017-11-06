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

        if ( mess.ordre().compare("AFFICHER") == 0 )
            result = traiterOrdreAfficher(mess);
        else if ( mess.ordre().compare("COULEUR") == 0 )
            result = traiterOrdreCouleur(mess);
    }
    else
    {
        std::cout << "message invalide : pas de traitement de : " << mess.texte().toStdString() << std::endl;
        result = MessageClient(0,"message invalide : " + mess.texte());
    }

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Traitement d'un ordre d'affichage.
 * \param mess Le message client reçu.
 * \return Le message à renvoyer au client.
 */
MessageClient GestionnaireOrdre::traiterOrdreAfficher(const MessageClient &mess)
{
    if ( AfficheurInterface::instance()->connexionEtablie() )
    {
        if ( mess.a_parametre() )
        {
            AfficheurInterface::instance()->envoyerMessage( mess );
            return MessageClient(mess.numero(),"Le message a ete envoye à l'afficheur.");
        }
        else
            return MessageClient(mess.numero(),"Erreur : Le message à envoyer est vide.");
    }
    else
        return MessageClient(mess.numero(),"Erreur : le serveur n'est pas connecte a l'afficheur.");
}

/** --------------------------------------------------------------------------------------
 * \brief Traitement d'un ordre de choix de couleur.
 * \param mess Le message client reçu.
 * \return Le message à renvoyer au client.
 */
MessageClient GestionnaireOrdre::traiterOrdreCouleur(const MessageClient &mess)
{
    bool result = AfficheurInterface::instance()->setCouleur( mess );

    if ( result )
        return MessageClient(mess.numero(),"Le message a ete envoye à l'afficheur.");
    else
        return MessageClient(mess.numero(),"Le choix de couleur n'est pas conforme.");
}

/** --------------------------------------------------------------------------------------
 * \brief Traitement d'un ordre d'initialisation d'une variable de type String.
 * \param mess Le message client reçu.
 * \return Le message à renvoyer au client.
 */
MessageClient GestionnaireOrdre::traiterSetStringVariable(const MessageClient &mess)
{
    if ( mess.a_parametre() )
        if ( mess.nb_parametres() == 2 )
        {
            m_string_variables[ mess.parametre(0) ] = mess.parametre(1);
            return MessageClient(mess.numero(),"L'initialisation est effectuée.");
        }

    return MessageClient(mess.numero(),"La demande d'initialisation n'est pas au bon format.");
}

/** --------------------------------------------------------------------------------------
 * \brief Traitement d'un ordre d'initialisation d'une variable de type int.
 * \param mess Le message client reçu.
 * \return Le message à renvoyer au client.
 */
MessageClient GestionnaireOrdre::traiterSetIntVariable(const MessageClient &mess)
{
    if ( mess.a_parametre() )
        if ( mess.nb_parametres() == 2 )
        {
            m_int_variables[ mess.parametre(0) ] = mess.parametre(1).toInt();
            return MessageClient(mess.numero(),"L'initialisation est effectuée.");
        }

    return MessageClient(mess.numero(),"La demande d'initialisation n'est pas au bon format.");
}

/** --------------------------------------------------------------------------------------
 * \brief Traitement d'un ordre d'accès à une variable de type String.
 * \param mess Le message client reçu.
 * \return Le message à renvoyer au client.
 */
MessageClient GestionnaireOrdre::traiterGetStringVariable(const MessageClient &mess)
{
    if ( mess.a_parametre() )
        if ( mess.nb_parametres() == 1 )
        {
            std::map<QString, QString>::iterator it = m_string_variables.find( mess.parametre(0) );
            if ( it == m_string_variables.end() )
                return MessageClient(mess.numero(),"La variable demandée n'existe pas.");
            else
            {
                std::vector<QString> l;
                l.push_back( it->second );
                return MessageClient(mess.numero(),"GET",l);
            }
        }

    return MessageClient(mess.numero(),"La demande d'accès n'est pas au bon format.");
}

/** --------------------------------------------------------------------------------------
 * \brief Traitement d'un ordre d'accès à une variable de type Int.
 * \param mess Le message client reçu.
 * \return Le message à renvoyer au client.
 */
MessageClient GestionnaireOrdre::traiterGetIntVariable(const MessageClient &mess)
{
    if ( mess.a_parametre() )
        if ( mess.nb_parametres() == 1 )
        {
            std::map<QString, int>::iterator it = m_int_variables.find( mess.parametre(0) );
            if ( it == m_int_variables.end() )
                return MessageClient(mess.numero(),"La variable demandée n'existe pas.");
            else
            {
                std::vector<QString> l;
                l.push_back( QString::number(it->second) );
                return MessageClient(mess.numero(),"GET",l);
            }
        }

    return MessageClient(mess.numero(),"La demande d'accès n'est pas au bon format.");
}
