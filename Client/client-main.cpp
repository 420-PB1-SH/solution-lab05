#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

int main()
{
    sf::UdpSocket socket;
    sf::SocketSelector selecteur;
    sf::IpAddress adresseServeur = "127.0.0.1";
    sf::IpAddress adressePaquetEntrant;
    sf::Packet paquetEntrant;
    sf::Packet paquetSortant;

    unsigned short portServeur = 54000;
    unsigned short portClient;
    unsigned short portPaquetEntrant;

    string prenomRecherche;
    string nomRecherche;
    string codeResultat;
    string prenomResultat;
    string nomResultat;
    string bureau;
    sf::Int16 extensionTelephonique;

    setlocale(LC_ALL, "");

    socket.bind(sf::Socket::AnyPort);
    portClient = socket.getLocalPort();

    selecteur.add(socket);

    cout << "Annuaire des enseignants d'informatique" << endl;
    cout << "===========" << endl << endl;

    paquetSortant << "COUNT";
    socket.send(paquetSortant, adresseServeur, portServeur);
    paquetSortant.clear();

    if (selecteur.wait(sf::seconds(5))) {
        socket.receive(paquetEntrant, adressePaquetEntrant, portPaquetEntrant);

        paquetEntrant >> codeResultat;
        if (codeResultat == "OK") {
            sf::Int16 nombreContacts;
            paquetEntrant >> nombreContacts;
            cout << "Le serveur contient " << nombreContacts << " contacts." << endl;
        }
        else {
            cout << "Erreur inconnue." << endl;
        }
    }
    else {
        cout << "Le nombre de contacts sur le serveur n'a pas pu �tre r�cup�r�." << endl;
    }

    cout << "Entrer le pr�nom rercherch�: ";
    getline(cin, prenomRecherche);

    cout << "Entrer le nom recherch�: ";
    getline(cin, nomRecherche);

    paquetSortant << "SEARCH" << nomRecherche << prenomRecherche;

    socket.send(paquetSortant, adresseServeur, portServeur);

    if (selecteur.wait(sf::seconds(5))) {
        socket.receive(paquetEntrant, adressePaquetEntrant, portPaquetEntrant);

        paquetEntrant >> codeResultat;
        if (codeResultat == "OK") {
            paquetEntrant >> nomResultat >> prenomResultat >> bureau >> extensionTelephonique;
            cout << "Voici les informations retourn�es par le serveur: " << endl
                << "Nom: " << nomResultat << endl
                << "Pr�nom: " << prenomResultat << endl
                << "Bureau: " << bureau << endl
                << "Extension t�l�phonique: " << extensionTelephonique << endl;
        }
        else if (codeResultat == "NOT_FOUND") {
            cout << "Le contact demand� n'existe pas." << endl;
        }
        else {
            cout << "Erreur inconnue." << endl;
        }
    }
    else {
        cout << "Le serveur n'a retourn� aucune r�ponse apr�s 5 secondes." << endl;
    }
}
