/**
 * @file contact.cpp
 */


#include "contact.h"


#include <QDebug>

Contact::Contact()
{

}


Contact::~Contact()
{

}


/**
 * @brief Constructeur de Contact.
 * @param prenom Prénom du contact.
 * @param nom Nom du contact.
 * @param entreprise Nom de l'entreprise du contact.
 * @param photo Chemin vers la photo du contact.
 * @param mail Adresse e-mail du contact.
 * @param telephone Numéro de téléphone du contact.
 * @param date Date de naissance du contact.
 */
Contact::Contact(const std::string &prenom, const std::string &nom, const std::string &entreprise, const std::string &photo, const std::string &mail, const std::string &telephone):Personne(nom,prenom)
{
    this->setEntreprise(entreprise);
    this->setPhoto(photo);
    this->setMail(mail);
    this->setTelephone(telephone);
    this->setDate();
}


/**
 * @brief Contact::setEntreprise setteur Entreprise
 * @param string
 */
void Contact::setEntreprise(const std::string & e)
{
    entreprise = e;
}

/**
 * @brief Contact::setPhoto setteur Photo
 * @param string
 */
void Contact::setPhoto(const std::string & p)
{
    photo = p;
}


/**
 * @brief Contact::setMail setteur Mail
 * @param string
 */
void Contact::setMail(const std::string & m)
{
    mail = m;
}


/**
 * @brief Contact::setTelephone setteur Telephone
 * @param string
 */
void Contact::setTelephone(const std::string & t)
{
    telephone = t;
}


/**
 * @brief Contact::setDate setteur date actuelle
 */
void Contact::setDate()
{
    day_point dp = floor<days>(system_clock::now());
    auto ymd = year_month_day{dp};
    date = day_point{ymd};
}


/**
 * @return Nom de l'entreprise du contact.
 */
std::string Contact::getEntreprise() const
{
    return entreprise;
}

/**
 * @return Chemin vers la photo du contact.
 */
std::string Contact::getPhoto() const
{
    return photo;
}

/**
 * @return Adresse e-mail du contact.
 */
std::string Contact::getMail() const
{
    return mail;
}

/**
 * @return Numéro de téléphone du contact.
 */
std::string Contact::getTelephone() const
{
    return telephone;
}

/**
 * @return Date de naissance du contact.
 */
day_point Contact::getDate() const
{
    return date;
}




/**
 * @brief Surcharge de l'opérateur d'égalité pour comparer deux contacts.
 * @param other Le contact à comparer.
 * @return True si les contacts sont égaux, sinon False.
 */
bool Contact::operator==(const Contact &other) const
{
    return (getNom() == other.getNom() && getPrenom() == other.getPrenom() &&
            getEntreprise() == other.getEntreprise() && getMail() == other.getMail() &&
            getTelephone() == other.getTelephone() && getDate() == other.getDate());
}




/**
 * @return Une chaîne de caractères contenant les détails du contact.
 */
std::string Contact::Affichage() const
{
    //On convertit la date en std::string
    std::time_t now_c = std::chrono::system_clock::to_time_t(date);
    std::string time_str = std::ctime(&now_c);
    std::string details = "Nom: " + getNom() + ", Prenom: " + getPrenom() + ", Entreprise: " + getEntreprise() + ", Telephone: "+ getTelephone() + ", Mail: " + getMail() +", Date: " + time_str;
    return details;
}

/**
 * @brief Contact::getInteraction getteur Interaction
 * @return liste Interaction du contact
 */
const std::list<Interaction> Contact::getInteraction() const{
    return gc.getInteractions();
}

/**
 * @brief Met à jour la liste d'interaction
 * @param updatedList
 */
void Contact::updateInteractionList(const std::list<Interaction>& updatedList) {
    gc.updateInteractions(updatedList);
}

/**
 * @brief Ajout d'une interaction
 * @param interaction
 */
void Contact::addInteraction(const Interaction &interaction) {
    gc.addInteraction(interaction);
}

/**
 * @brief Contact::getInteractionAt
 * @param index
 * @return  l'interaction à l'index donnée
 */
Interaction& Contact::getInteractionAt(int index) {
    // Vérifiez d'abord si l'index est valide
    if (index >= 0 && index < gc.getInteractions().size()) {
        // Obtenez la liste des interactions
        const std::list<Interaction>& interactions = gc.getInteractions();

        // Utilisez un itérateur pour accéder à l'élément à l'index spécifié
        auto iter = std::next(interactions.begin(), index);

        // Retournez la référence vers l'Interaction à l'index spécifié
        return const_cast<Interaction&>(*iter);
    } else {
        throw std::out_of_range("Index d'interaction hors limites");
    }
}

/**
 * @brief Contact::addAssociation
 * @param association
 */
void Contact::addAssociation(const AssociationInteractionTodo &association) {
    associations.push_back(association);
}


/**
 * @brief Contact::getAssociations
 * @return une liste d'association
 */
const std::list<AssociationInteractionTodo>& Contact::getAssociations() const {
    return associations;
}

/**
 * @brief Contact::getAssociationsByInteraction
 * @param interaction
 * @return  une liste d'association selon l'interaction
 */
std::list<AssociationInteractionTodo> Contact::getAssociationsByInteraction(const Interaction& interaction) {
    std::list<AssociationInteractionTodo> filteredAssociations;

    for (const auto& association : associations) {
        if (association.getInteraction() == &interaction) {
            filteredAssociations.push_back(association);
        }
    }

    return filteredAssociations;
}

/**
 * @brief Contact::countAssociations
 * @return la taille de la liste d'association
 */
int Contact::countAssociations()
{
    // Utilisez la taille de la liste pour obtenir le nombre d'associations
    return associations.size();
}

/**
 * @brief Contact::showListAssociation
 * @return un string d'affichage de la liste d'association
 */
std::string Contact::showListAssociation() {
    // Afficher la liste d'associations dans la console
    std::string aff;
    for (auto &association : associations) {
        aff.append(association.Affichage() + "\n");
        // Assurez-vous que Affichage() est défini correctement dans la classe AssociationInteractionTodo
    }
    return aff;
}

/**
 * @brief Contact::removeAssociationByTodo retire les associations contenant le todo
 * @param todo
 */
void Contact::removeAssociationByTodo(const ITodo& todo) {
    associations.remove_if([&todo](const AssociationInteractionTodo& association) {
        return association.getTodo() == &todo;
    });
}


/**
 * @brief Contact::updateAssociations met à jour la liste d'association
 * @param interaction
 * @param updatedAssociations
 */
void Contact::updateAssociations(const Interaction& interaction, const std::list<AssociationInteractionTodo>& updatedAssociations) {
    // Parcourir les associations pour l'interaction spécifiée
    for (auto& assoc : associations) {
        if (assoc.getInteraction() == &interaction) {
            // Supprimer toutes les associations existantes pour cette interaction
            associations.remove(assoc);

            // Ajouter les nouvelles associations
            for (const auto& updatedAssoc : updatedAssociations) {
                addAssociation(updatedAssoc);
            }

            // Vous pouvez également ajouter un break ici si chaque interaction est censée avoir une seule association
            break;
        }
    }
}

/**
 * @brief Contact::getAssociationsByTodo
 * @param todo
 * @return une liste d'association selon l'interaction
 */
std::list<AssociationInteractionTodo> Contact::getAssociationsByTodo(const ITodo *todo) const {
    std::list<AssociationInteractionTodo> result;

    // Utilisation de std::copy_if pour filtrer les associations
    std::copy_if(associations.begin(), associations.end(), std::back_inserter(result),
                 [todo](const AssociationInteractionTodo &association) {
                     return association.getTodo() == todo;
                 });

    return result;
}




/**
 * @brief Contact::addModification ajoute un historique à la liste
 * @param modification
 */
void Contact::addModification(const Modification& modification) {
    history.push_back(modification);
}

/**
 * @brief Contact::getHistory
 * @return la liste d'historique
 */
const std::list<Modification>& Contact::getHistory() const {
    return history;
}
