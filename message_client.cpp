/** \file message_client.cpp
 * \brief Fichier d'implémentation de la classe MessageClient.
 * \author Sébastien Angibaud
 */

#include "message_client.h"

#include <QStringList>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur par défaut de la classe MessageClient.
 */
MessageClient::MessageClient()
    : m_numero(0), m_valide(false)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe MessageClient.
 * \param texte Une référence constante sur le texte reçu ou à envoyer.
 */
MessageClient::MessageClient(const QString & texte)
{
    m_valide = true;

    QStringList liste = texte.split('|');
    if ( liste.size() < 2 || liste.size() > 3 )
        m_valide = false;
    else
    {
        QStringList::Iterator it = liste.begin();

        // le numero
        m_numero = it->toInt( & m_valide );
        ++it;

        // l'ordre
        m_ordre = *it;
        ++it;

        // eventuellement le parametre
        if ( it != liste.end() )
            m_parametre = *it;
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe MessageClient.
 * \param numero Le numero du message.
 * \param ordre L'ordre du message.
 * \param parametre Le parametre du message.
 */
MessageClient::MessageClient(int numero, QString ordre, QString parametre)
    : m_numero(numero), m_ordre(ordre), m_parametre(parametre), m_valide(false)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du texte.
 * \return Le texte du message.
 */
QString MessageClient::texte() const
{
    QString result( QString::number(m_numero) + "|" + m_ordre );

    if ( ! m_parametre.isEmpty() )
        result = result + m_parametre;

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du numero.
 * \return Le numero du message.
 */
int MessageClient::numero() const
{
    return m_numero;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de l'ordre du message.
 * \return L'ordre du message.
 */
QString MessageClient::ordre() const
{
    return m_ordre;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du parametre du message.
 * \return Le parametre du message.
 */
QString MessageClient::parametre() const
{
    return m_parametre;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si le message est valide.
 * \return La validité du message.
 */
bool MessageClient::valide() const
{
    return m_valide;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si le message a un parametre.
 * \return Un booléen indiquant si le message a un parametre.
 */
bool MessageClient::a_parametre() const
{
    return ! m_parametre.isEmpty();
}
