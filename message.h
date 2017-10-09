#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>


/**
 * \brief Déclaration de la classe message décrivant un message à envoyer à l'afficheur.
 **/
class message
{
    public:
        message();
        message( std::string texte );

        std::string texte() const;

    private:
        std::string m_texte;
};

#endif // MESSAGE_H
