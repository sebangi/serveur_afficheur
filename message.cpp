/** \file message.cpp
 * \brief Fichier d'implémentation de la classe Message.
 * \author Sébastien Angibaud
 */

#include "message.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur par défaut de la classe Message.
 */
Message::Message()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe message.
 * \param texte Un référence constante sur le texte du message à envoyer.
 */
Message::Message(const std::string & texte)
    : m_texte(texte)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du texte à envoyer.
 * \return Le texte à envoyer.
 */
std::string Message::texte() const
{
    return m_texte;
}
