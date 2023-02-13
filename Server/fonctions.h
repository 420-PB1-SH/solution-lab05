#pragma once

#include <string>
#include "Contact.h"

using namespace std;

string transformerEnMinuscules(string chaine);

int trouverContact(Contact contacts[], int nombreContacts, string nomContact, string prenomContact);
