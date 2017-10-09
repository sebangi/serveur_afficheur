#ifndef AFFICHEURINTERFACE_H
#define AFFICHEURINTERFACE_H

#include <QtSerialPort/QSerialPort>

class message;

class AfficheurInterface
{
    private:
        AfficheurInterface();
        ~AfficheurInterface();

    public:
        static AfficheurInterface* Instance();

        void envoyerMessage(const message& m);

    private:
        int calculerChecksum(const char* trame) const;
        bool connexion_etablie() const;

    private:
        static AfficheurInterface* m_instance;
        QSerialPort m_serial;
};

#endif // AFFICHEURINTERFACE_H
