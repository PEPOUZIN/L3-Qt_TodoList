/**
 *@file personne.h
*/

#ifndef PERSONNE_H
#define PERSONNE_H


#include <iostream>



class Personne
{


public:

    Personne();
    Personne(const std::string &nom, const std::string &prenom);

    std::string getNom() const;
    std::string getPrenom() const;

    void setNom(const std::string &);
    void setPrenom(const std::string &);



private:

    std::string nom;
    std::string prenom;
};

#endif // PERSONNE_H
