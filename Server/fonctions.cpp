#include "fonctions.h";

string transformerEnMinuscules(string chaine) {
	string resultat;
	for (auto caractere : chaine) {
		resultat += tolower(caractere);
	}
	return resultat;
}

int trouverContact(Contact contacts[], int nombreContacts, string nomContact, string prenomContact) {
	Contact contact;
	string prenomMinuscules;
	string nomMinuscules;
	string nomRecherche = transformerEnMinuscules(nomContact);
	string prenomRecherche = transformerEnMinuscules(prenomContact);

	for (int i = 0; i < nombreContacts; i++) {
		contact = contacts[i];
		prenomMinuscules = transformerEnMinuscules(contact.getPrenom());
		nomMinuscules = transformerEnMinuscules(contact.getNom());

		if (nomRecherche == nomMinuscules && prenomRecherche == prenomMinuscules) {
			return i;
		}
	}

	return nombreContacts;
}