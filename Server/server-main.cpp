#include <iostream>
#include <SFML/Network.hpp>

#include "Contact.h"
#include "fonctions.h"

using namespace std;

int main()
{
    const int NOMBRE_CONTACTS = 23;

    Contact contacts[NOMBRE_CONTACTS] = {
        Contact("Bergevin", "Luc", "5-21-125", 4607),
        Contact("Brault", "Pier-Luc", "5-21-121", 4565),
        Contact("Cisse", "Mahamadou", "5-21-125", 4599),
        Contact("Couture-Legare", "Renau", "5-21-121", 4600),
        Contact("Demers", "Genevieve", "5-21-117", 4590),
        Contact("Demers", "Olivier", "", 4470),
        Contact("Deschamps", "Jacob", "5-21-113", 4609),
        Contact("Fortin", "Josianne", "5-21-117", 4592),
        Contact("Gagnon", "Julie", "5-21-113", 4595),
        Contact("Guimond-Dufour", "Simon", "5-21-121", 4569),
        Contact("Huppe", "Alexandre", "5-21-105", 4596),
        Contact("Jaramillo", "Alexander", "5-21-111", 4598),
        Contact("Lamothe", "Regis", "5-21-115", 4605),
        Contact("Lapalme", "Jocelyn", "5-21-119", 4606),
        Contact("Musinbegovic", "Almir", "", 4043),
        Contact("Palao-Munoz", "Domingo", "5-21-121", 4604),
        Contact("Payre", "Nicolas", "5-21-125", 4304),
        Contact("Ross", "Olivier", "", 0),
        Contact("Roussel", "Nicolas", "5-21-105", 5255),
        Contact("Scheffler", "Olivier", "", 0),
        Contact("Slougui", "Lyes", "", 4461),
        Contact("St-Yves", "Andre", "5-21-105", 5321),
        Contact("Taschereau", "Cedric", "", 4462)
    };

    sf::UdpSocket socket;

    sf::Packet paquetEntrant;
    sf::Packet paquetSortant;

    unsigned short portServeur = 54000;
    unsigned short portClient;

    sf::IpAddress adresseClient;

    string actionRequete;
    string prenomRequete;
    string nomRequete;

    int idContact;

    setlocale(LC_ALL, "");

    // Attacher le socket au port du serveur
    if (socket.bind(portServeur) != sf::Socket::Done) {
        cout << "Une erreur est survenue lors de la création du socket." << endl;
        return 1;
    }

    cout << "Le serveur écoute sur le port " << portServeur << "." << endl;

    // Tant que le programme n'est pas arrêté par l'utilisateur
    while (true) {
        socket.receive(paquetEntrant, adresseClient, portClient);

        paquetEntrant >> actionRequete;
        if (actionRequete == "SEARCH") {
            paquetEntrant >> nomRequete >> prenomRequete;

            cout << adresseClient << " veut avoir les informations sur le contact: " << prenomRequete << " " << nomRequete << endl;

            idContact = trouverContact(contacts, NOMBRE_CONTACTS, nomRequete, prenomRequete);

            if (idContact == NOMBRE_CONTACTS) {
                cout << "Le contact " << prenomRequete << " " << nomRequete << " n'existe pas.";
                paquetSortant << "NOT_FOUND";
            }
            else {
                paquetSortant << "OK" << contacts[idContact].getNom()
                    << contacts[idContact].getPrenom()
                    << contacts[idContact].getBureau()
                    << sf::Int16(contacts[idContact].getExtensionTelephonique());
            }
        }
        else if (actionRequete == "COUNT") {
            cout << adresseClient << " veut connaître le nombre de contacts sur le serveur." << endl;
            paquetSortant << "OK" << sf::Int16(NOMBRE_CONTACTS);
        }
        else {
            cout << adresseClient << " a envoyé une action invalide: " << actionRequete << endl;
            paquetSortant << "INVALID_ACTION";
        }

        socket.send(paquetSortant, adresseClient, portClient);

        paquetSortant.clear();
    }
}
