/** \file message_client.cpp
 * \brief Fichier d'implémentation de la classe MessageClient.
 * \author Sébastien Angibaud
 */

#include "message_client.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur par défaut de la classe MessageClient.
 */
MessageClient::MessageClient()
{

}


/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe MessageClient.
 * \param texte Une référence constante sur le texte reçu ou à envoyer.
 */
MessageClient::MessageClient(const QString & texte)
    : m_texte(texte)
{

}

QString MessageClient::texte() const
{
    return m_texte;
}
