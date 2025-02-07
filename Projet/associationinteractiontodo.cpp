/**
 * @file associationinteractiontodo.cpp
 * @brief Implémentation de la classe AssociationInteractionTodo.
 */
#include "associationinteractiontodo.h"


/**
 * @brief Constructeur de la classe AssociationInteractionTodo.
 * @param i Pointeur vers l'objet Interaction.
 * @param t Pointeur vers l'objet ITodo.
 */
AssociationInteractionTodo::AssociationInteractionTodo(Interaction* i, ITodo* t)
    : interaction(i), todo(t)
{
   
}
/**
 * @brief Fonction getter pour récupérer l'objet Interaction.
 * @return Pointeur vers l'objet Interaction.
 */
Interaction* AssociationInteractionTodo::getInteraction() const
{
    return interaction;
}
/**
 * @brief Fonction getter pour récupérer l'objet ITodo.
 * @return Pointeur vers l'objet ITodo.
 */
ITodo* AssociationInteractionTodo::getTodo() const
{
    return todo;
}
/**
 * @brief Génère une représentation sous forme de chaîne de caractères de l'AssociationInteractionTodo.
 * @return Représentation sous forme de chaîne de caractères de l'AssociationInteractionTodo.
 */
std::string AssociationInteractionTodo::Affichage() {
    if (interaction && todo) {
        return interaction->Affichage() + " " + todo->Affichage();
    } else {
        return "Invalid AssociationInteractionTodo";
    }
}

/**
 * @brief Opérateur d'égalité surchargé pour comparer deux objets AssociationInteractionTodo.
 * @param other L'objet AssociationInteractionTodo à comparer.
 * @return True si la comparaison est vraie, sinon False.
 */
bool AssociationInteractionTodo::operator==(const AssociationInteractionTodo& other) const {
    // Comparaison basée sur l'égalité de l'interaction et du todo
    return (interaction == other.interaction) && (todo == other.todo);
}
