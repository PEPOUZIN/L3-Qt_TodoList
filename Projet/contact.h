/**
 *@file contact.h
 *
*/


#ifndef CONTACT_H
#define CONTACT_H


#include "associationinteractiontodo.h"
#include "interaction.h"
#include "personne.h"
#include "date.h"
#include "gestioninteraction.h"
#include "qdatetime.h"

#include <iostream>
#include <list>


using namespace date;
using namespace std::chrono;
using day_point = std::chrono::time_point<std::chrono::system_clock, days>;

struct Modification {
    QDateTime timestamp;
    enum { Addition, Suppression, MiseAJour } type;
    std::string details;
};

class Contact : public Personne
{


private:

    std::string entreprise;
    std::string photo;
    std::string mail;
    std::string telephone;
    day_point date;
    GestionInteraction gc;
    std::list<AssociationInteractionTodo> associations;
    std::list<Modification> history;



public:

    Contact();
    Contact(const std::string &, const std::string &, const std::string &, const std::string &, const std::string &, const std::string &);
    ~Contact();


    std::string Affichage() const;
    bool operator==(const Contact& other) const;

    void addInteraction(const Interaction& interaction);


    // Obtenir la liste des associations
    const std::list<AssociationInteractionTodo>& getAssociations() const;
    void addAssociation(const AssociationInteractionTodo& association);


    int countAssociations();
    std::string getEntreprise() const;
    std::string getPhoto() const;
    std::string getMail() const;
    std::string getTelephone() const;
    day_point getDate() const;
    const std::list<Interaction> getInteraction() const;
    void updateInteractionList(const std::list<Interaction>& updatedList);
    Interaction& getInteractionAt(int index);
    std::list<AssociationInteractionTodo> getAssociationsByInteraction(const Interaction& interaction);
    std::string showListAssociation();
    void removeAssociationByTodo(const ITodo& todo);
    void updateAssociations(const Interaction& interaction, const std::list<AssociationInteractionTodo>& updatedAssociations);
    std::list<AssociationInteractionTodo> getAssociationsByTodo(const ITodo *todo) const;




    void addModification(const Modification& modification);

    const std::list<Modification>& getHistory() const;


    //void addTodoAssociation(const Interaction& interaction, const ITodo& todo);


    //void addInteraction(const Interaction &interaction);
    //static bool compareByName(const Contact &contact1, const Contact &contact2);



    void setEntreprise(const std::string &);
    void setPhoto(const std::string &);
    void setMail(const std::string &);
    void setTelephone(const std::string &);
    void setDate();
};

#endif // CONTACT_H
