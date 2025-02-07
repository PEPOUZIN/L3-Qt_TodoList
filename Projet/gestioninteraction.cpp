/**
 * @file gestioninteraction.cpp
 * @brief Implémentation de la classe GestionInteraction.
 */

#include "gestioninteraction.h"

/**
 * @brief Constructeur par défaut de la classe GestionInteraction.
 */
GestionInteraction::GestionInteraction()
{

}

/**
 * @brief Ajoute une interaction à la liste des interactions.
 * @param interaction Une référence vers l'interaction à ajouter.
 */
void GestionInteraction::addInteraction(const Interaction &interaction)
{
    linteraction.push_back(interaction);
}

/**
 * @brief Récupère la liste des interactions.
 * @return Une référence constante vers la liste des interactions.
 */
const std::list<Interaction>& GestionInteraction::getInteractions() const {
    return linteraction;
}

/**
 * @brief Supprime une interaction spécifiée de la liste des interactions.
 * @param interactionToRemove L'interaction à supprimer.
 */
void GestionInteraction::delInteraction(const Interaction &interactionToRemove)
{
    linteraction.remove_if([&interactionToRemove](const Interaction &i) {
        return i.getContenu() == interactionToRemove.getContenu() &&
               i.getDate() == interactionToRemove.getDate();
    });
}

/**
 * @brief Met à jour la liste des interactions avec une nouvelle liste spécifiée.
 * @param updatedList La nouvelle liste d'interactions.
 */
void GestionInteraction::updateInteractions(const std::list<Interaction>& updatedList) {
    linteraction = updatedList;
}
