#ifndef AFFICHEURINTERFACE_H
#define AFFICHEURINTERFACE_H

/**
 * \file afficheurinterface.h
 * \brief Fichier de déclaration de la classe AfficheurInterface.
 * \author Sébastien Angibaud
 */

#include <QtSerialPort/QSerialPort>

class Message;

/**
 * \class AfficheurInterface
 * \brief Classe permettant de faire l'interface avec un afficheur.
 * \author Sébastien Angibaud
 */
class AfficheurInterface
{
    private:
        AfficheurInterface();
        ~AfficheurInterface();

    public:
        static AfficheurInterface* instance();
        void envoyerMessage(const Message& m);

    private:
        int calculerChecksum(const char* trame) const;
        bool connexionEtablie() const;

    private:
        /** \brief Pointeur sur l'instance singleton AfficheurInterface. */
        static AfficheurInterface* m_instance;

        /** \brief Le port série. */
        QSerialPort m_portSerie;
};

#endif // AFFICHEURINTERFACE_H