/**
 * @file gestioncontact.cpp
 * @brief Implémentation de la classe GestionContact.
 */

#include "gestioncontact.h"

#include <QList>
#include <algorithm>  // Pour std::sort
#include <functional> // Pour std::function
#include <QDebug>     // Pour les messages de débogage
#include <iostream>
#include <stdexcept>

/**
 * @brief Constructeur par défaut de la classe GestionContact.
 */
GestionContact::GestionContact(): lc()
{

}

/**
 * @brief Destructeur de la classe GestionContact.
 */
GestionContact::~GestionContact()
{

}

/**
 * @brief Récupère un contact par indice pour modification.
 * @param index L'indice du contact à récupérer.
 * @return Le contact correspondant à l'indice.
 * @throw std::out_of_range Si l'indice est invalide.
 */
Contact& GestionContact::getContact(int index) {
    // Assurez-vous que l'index est valide
    if (index >= 0 && index < lc.size()) {
        auto it = lc.begin();
        std::advance(it, index);
        return *it;
    } else {
        // Gérer l'index non valide, par exemple, renvoyer un contact "vide" ou lever une exception
        throw std::out_of_range("Indice d'accès au contact invalide");
    }
}

/**
 * @brief Ajoute un contact à la liste de contacts.
 * @param contact Le contact à ajouter.
 */
void GestionContact::addContact(const Contact &contact)
{
    lc.push_back(contact);
}

/**
 * @brief Supprime un contact de la liste de contacts.
 * @param contact Le contact à supprimer.
 */
void GestionContact::delContact(const Contact &contact)
{
    auto it = std::find(lc.begin(), lc.end(), contact);

    if (it != lc.end())
    {
        lc.erase(it);
    }
}

/**
 * @brief Affiche la liste des contacts.
 */
void GestionContact::showListContact()
{
    std::cout << "Liste des contacts :" << std::endl;

    if (!lc.empty()) {
        for (const Contact& contact : lc)
        {
            std::cout << contact.Affichage() << std::endl;
        }
    } else {
        std::cout << "Aucun contact dans la liste." << std::endl;
    }
}

/**
 * @brief Recherche un contact par nom et affiche les résultats.
 * @param name Le nom à rechercher parmi les contacts.
 */
void GestionContact::researchContact(std::string& name)
{
    bool contactFound = false;

    if (!lc.empty()) {
        for (const Contact& contact : lc) {
            if (contact.getNom() == name) {
                std::cout << contact.Affichage() << std::endl;
                contactFound = true;
            }
        }

        if (!contactFound) {
            std::cout << "Contact non trouvé" << std::endl;
        }
    } else {
        std::cout << "Liste de Contact vide" << std::endl;
    }
}

/**
 * @brief Trie et retourne une copie de la liste de contacts en utilisant un comparateur.
 * @param comparator Foncteur de comparaison pour trier les contacts.
 * @return Une liste triée de contacts.
 */
std::list<Contact> GestionContact::getContacts(const std::function<bool(const Contact&, const Contact&)>& comparator) {
    std::list<Contact> sortedContacts = lc;  // Assurez-vous que "contacts" est votre liste de contacts dans GestionContact
    sortedContacts.sort(comparator);
    return sortedContacts;
}

/**
 * @brief Récupère un contact par numéro de téléphone.
 * @param phoneNumber Le numéro de téléphone du contact à rechercher.
 * @return Une référence constante vers le contact correspondant au numéro de téléphone.
 *         Si le contact n'est pas trouvé, une référence constante vers un contact vide est renvoyée.
 */
const Contact& GestionContact::getContactByPhone(const std::string& phoneNumber) const {
    for (const Contact& contact : lc) {
        if (contact.getTelephone() == phoneNumber) {
            return contact;
        }
    }

    // Retourner une référence constante vers un contact temporaire vide
    return Contact(); // Contact vide avec des valeurs par défaut
}

/**
 * @brief Récupère la liste des contacts.
 * @return Une référence constante vers la liste des contacts.
 */
const std::list<Contact>& GestionContact::getContactsListe() const {
    return lc;
}

/**
 * @brief Récupère le nombre de contacts dans la liste.
 * @return Le nombre de contacts.
 */
int GestionContact::nbContact(){
    return lc.size();
}
