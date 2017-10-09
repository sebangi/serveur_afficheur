#include <QCoreApplication>

#include <QtSerialPort/QSerialPort>
#include <iostream>
#include <sstream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <windows.h>

#include "message.h"
#include "afficheurinterface.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    string entree_clavier;
    AfficheurInterface* afficheur = AfficheurInterface::Instance();

    while (int i = 1){
        getline(cin, entree_clavier);

        message mess( entree_clavier );
        afficheur->envoyerMessage( mess );

        Sleep(5000);
    }


    return a.exec();
}
