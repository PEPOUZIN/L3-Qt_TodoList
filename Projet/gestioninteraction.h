/**
 *@file gestioninteraction.h
 *
*/


#ifndef GESTIONINTERACTION_H
#define GESTIONINTERACTION_H
#include <list>
#include "interaction.h"

class GestionInteraction
{

private:
    std::list<Interaction> linteraction;

public:
    GestionInteraction();

    void addInteraction(const Interaction &interaction);
    const std::list<Interaction>& getInteractions() const;
    void delInteraction(const Interaction &interaction);
    void updateInteractions(const std::list<Interaction>& updatedList);


};

#endif // GESTIONINTERACTION_H
