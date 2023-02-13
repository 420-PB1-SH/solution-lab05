#pragma once

#include <string>

using namespace std;

class Contact {
private:
	string _nom;
	string _prenom;
	string _bureau;
	short _extensionTelephonique;

public:
	Contact();
	Contact(string nom, string prenom, string bureau, int extensionTelephonique);
	~Contact();

	string getNom()const;
	string getPrenom()const;
	string getBureau()const;
	short getExtensionTelephonique()const;

	void setNom(string nom);
	void setPrenom(string prenom);
	void setBureau(string bureau);
	void setExtensionTelephonique(short extensionTelephonique);
};
