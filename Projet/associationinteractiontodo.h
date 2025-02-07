/**
 *@file associationinteractiontodo.h
 *
*/

#ifndef ASSOCIATIONINTERACTIONTODO_H
#define ASSOCIATIONINTERACTIONTODO_H

#include "interaction.h"
#include "todo.h"

class AssociationInteractionTodo
{
public:
    AssociationInteractionTodo(Interaction* i, ITodo* t);
    //AssociationInteractionTodo(Interaction i, ITodo t);


    // Getters
    Interaction* getInteraction() const;
    ITodo* getTodo() const;
    std::string Affichage();
    bool operator==(const AssociationInteractionTodo& other) const;


private:
    Interaction *interaction;
    ITodo *todo;
};

#endif // ASSOCIATIONINTERACTIONTODO_H
