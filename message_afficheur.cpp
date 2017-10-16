/** \file message.cpp
 * \brief Fichier d'implémentation de la classe MessageAfficheur.
 * \author Sébastien Angibaud
 */

#include "message_afficheur.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur par défaut de la classe MessageAfficheur.
 */
MessageAfficheur::MessageAfficheur()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe MessageAfficheur.
 * \param texte Une référence constante sur le texte du message à envoyer.
 */
MessageAfficheur::MessageAfficheur(const QString & texte)
    : m_texte(texte)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du texte à envoyer.
 * \return Le texte à envoyer.
 */
QString MessageAfficheur::texte() const
{
    return m_texte;
}
