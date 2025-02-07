/**
 * @file interaction.cpp
 * @brief Implémentation de la classe Interaction.
 */

#include "interaction.h"
#include <sstream>
#include <iomanip>


/**
 * @brief Constructeur de la classe Interaction.
 * @param c Le contenu de l'interaction.
 * @param d La date de l'interaction.
 */
Interaction::Interaction(const std::string &c, const int &j, const int &m, const int &a)
{
    this->setContenu(c);
    this->setDate(j, m, a);
}

/**
 * @brief Destructeur de la classe Interaction.
 */
Interaction::~Interaction()
{

}

/**
 * @return Le contenu de l'interaction.
 */
std::string Interaction::getContenu() const
{
    return contenu;
}

/**
 * @return La date de l'interaction.
 */
day_point Interaction::getDate() const
{
    return date;
}

/**
 * @brief Définit le contenu de l'interaction.
 * @param c Le nouveau contenu de l'interaction.
 */
void Interaction::setContenu(const std::string &c)
{
    contenu = c;
}

/**
 * @brief Définit la date de l'interaction.
 * @param ymd2 La nouvelle date de l'interaction.
 */
void Interaction::setDate(const int &j, const int &m, const int &a)
{
    // Extraire la date courante
    auto ymd2 = year(a) / month(m) / day(j);
    date = day_point{ymd2};
}

/**
 * @brief Définit la date de l'interaction depuis un day_point.
 * @param dp La nouvelle date de l'interaction.
 */
void Interaction::setDateDP(const day_point &dp)
{
    date = dp;
}

/**
 * @return Une chaîne de caractères représentant l'interaction.
 */
std::string Interaction::Affichage() const
{
    // On transforme le format ymd en string
    auto ymd = year_month_day{date};
    std::ostringstream oss;
    oss << ymd.year() << '-' << std::setw(2) << std::setfill('0') << (unsigned)ymd.month() << '-' << std::setw(2) << std::setfill('0') << (unsigned)ymd.day();
    std::string s = oss.str();
    std::string aff = getContenu() + " @date " + s;
    return aff;
}

/**
 * @brief Surcharge de l'opérateur d'égalité pour comparer deux interactions.
 * @param other L'autre interaction à comparer.
 * @return True si les interactions sont égales, False sinon.
 */
bool Interaction::operator==(const Interaction &other) const
{
    return getContenu() == other.getContenu() && getDateAsString() == other.getDateAsString();
}

/**
 * @brief Obtient la date de l'interaction sous forme de chaîne de caractères.
 * @return La date de l'interaction au format chaîne de caractères.
 */
std::string Interaction::getDateAsString() const
{
    std::stringstream ss;
    return ss.str();
}
