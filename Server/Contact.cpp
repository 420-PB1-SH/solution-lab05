#include <assert.h>

#include "Contact.h"

Contact::Contact() {
    _nom = "";
    _prenom = "";
    _bureau = "";
    _extensionTelephonique = 0;
}

Contact::Contact(string nom, string prenom, string bureau, int extensionTelephonique) {
    _nom = nom;
    _prenom = prenom;
    _bureau = bureau;
    _extensionTelephonique = extensionTelephonique;
}

Contact::~Contact() {
    _nom = "";
    _prenom = "";
    _bureau = "";
    _extensionTelephonique = 0;
}

string Contact::getNom()const {
    return _nom;
}

string Contact::getPrenom()const {
    return _prenom;
}

string Contact::getBureau()const {
    return _bureau;
}

short Contact::getExtensionTelephonique()const {
    return _extensionTelephonique;
}

void Contact::setNom(string nom) {
    _nom = nom;
}

void Contact::setPrenom(string prenom) {
    _prenom = prenom;
}

void Contact::setBureau(string bureau) {
    _bureau = bureau;
}

void Contact::setExtensionTelephonique(short extensionTelephonique) {
    assert(extensionTelephonique > 999 && extensionTelephonique < 10000);
    _extensionTelephonique = extensionTelephonique;
}
