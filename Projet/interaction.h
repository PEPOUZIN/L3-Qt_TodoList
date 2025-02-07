/**
 *@file interaction.h
*/

#ifndef INTERACTION_H
#define INTERACTION_H

#include "date.h"
#include "todo.h"
#include <QString>
#include <list>

using namespace date;
using namespace std::chrono;
using day_point = std::chrono::time_point<std::chrono::system_clock, days>;

//class AssociationInteractionTodo;


class Interaction
{


private:

    //static int nextID;

    //int id;
    std::string contenu;
    day_point date;
    //std::list<AssociationInteractionTodo> associations;




public:

    Interaction(const std::string &, const int &, const int &, const int &);
    Interaction(const std::string &contenu, const std::string &dateString);
    ~Interaction();


    //const std::list<AssociationInteractionTodo>& getAssociations() const;
    //void addAssociation(const AssociationInteractionTodo& association);
    bool operator==(const Interaction& other) const;

    void setDate(const int &, const int &, const int &);
    void setDateDP(const day_point &);
    void setContenu(const std::string &);

    day_point getDate()const;
    std::string getContenu()const;
    //int getID();

    std::string Affichage() const;

    std::string getDateAsString() const;


};

#endif // INTERACTION_H
