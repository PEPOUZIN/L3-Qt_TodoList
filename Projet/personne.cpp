/**
 * @file personne.cpp
 */

#include "personne.h"


/**
 * @brief Constructeur par défaut de la classe Personne.
 */
Personne::Personne()
{

}



/**
 * @brief Constructeur de la classe Personne avec nom et prénom.
 * @param n Le nom de la personne.
 * @param pre Le prénom de la personne.
 */
Personne::Personne(const std::string &n, const std::string &pre)
{
    this->setNom(n);
    this->setPrenom(pre);
}






/**
 * @brief Définit le nom de la personne.
 * @param n Le nom de la personne.
 */
void Personne::setNom(const std::string & n){
    nom = n;
}


/**
 * @brief Définit le prénom de la personne.
 * @param p Le prénom de la personne.
 */
void Personne::setPrenom(const std::string & p){
    prenom = p;
}



/**
 * @return Le nom de la personne.
 */
std::string Personne::getNom() const{
    return nom;
}


/**
 * @return Le prénom de la personne.
 */
std::string Personne::getPrenom() const{
    return prenom;
}
