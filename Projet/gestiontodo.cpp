/**
 * @file gestiontodo.cpp
 * @brief Implémentation de la classe GestionTodo.
 */

#include "gestiontodo.h"

/**
 * @brief Constructeur par défaut de la classe GestionTodo.
 */
GestionTodo::GestionTodo()
{

}

/**
 * @brief Ajoute une tâche à la liste de tâches.
 * @param todo Une référence vers la tâche à ajouter.
 */
void GestionTodo::addTodo(const ITodo &todo)
{
    todos.push_back(todo);  // Utilisez "todos" au lieu de "linteraction"
}

/**
 * @brief Récupère la liste des tâches.
 * @return Une référence constante vers la liste des tâches.
 */
const std::list<ITodo>& GestionTodo::getTodos() const {
    return todos;
}

/**
 * @brief Supprime une tâche spécifiée de la liste des tâches.
 * @param todoToRemove Une référence vers la tâche à supprimer.
 */
void GestionTodo::delTodo(ITodo &todoToRemove)
{
    todos.remove_if([&todoToRemove](ITodo &i) {
        return i.getContenu() == todoToRemove.getContenu() &&
               i.getDate() == todoToRemove.getDate();
    });
}
