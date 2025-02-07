/**
 *@file gestioncontact.h
 *
*/


#ifndef GESTIONCONTACT_H
#define GESTIONCONTACT_H

#include "contact.h"
#include "functional"


class GestionContact
{


private:

    std::list<Contact> lc;


public:

    GestionContact();
    ~GestionContact();

    void addContact(const Contact &);
    void delContact(const Contact &);
    void showListContact();
    void researchContact(std::string &name);
    Contact &getContact(int index);
    std::list<Contact> getContacts(const std::function<bool(const Contact&, const Contact&)>& comparator);
    const Contact &getContactByPhone(const std::string &phoneNumber) const;
    const std::list<Contact>& getContactsListe() const;
    int nbContact();



};

#endif // GESTIONCONTACT_H
