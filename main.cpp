/** \file main.cpp
 * \brief Fichier principal de l'application serveur_afficheur.
 * \author Sébastien Angibaud
 */

#include <QCoreApplication>

#include <QtSerialPort/QSerialPort>
#include <iostream>
#include <sstream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <windows.h>

#include "serveur_ordre.h"

using namespace std;

/** --------------------------------------------------------------------------------------
 * \brief Fonction principale de l'application serveur_afficheur.
 * \param argc Le nombre de paramètres de l'application.
 * \param argv Le tableau contenant les paramètres de l'application.
 * \return Le code de sortie de la fonction quit() de QCoreApplication.
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // création du serveur
    ServeurOrdre serveur;

    return a.exec();
}
