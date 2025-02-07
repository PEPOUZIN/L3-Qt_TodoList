/**
 * @file todo.cpp
 */

#include "todo.h"

#include <iomanip>


/**
 * @brief Constructeur de la classe ITodo.
 * @param id L'identifiant de l'interaction associée au todo.
 * @param c Le contenu du todo.
 * @param d La date du todo.
 */
ITodo::ITodo(std::string c, const int &j, const int &m, const int &a)
{
    setContenu(c);
    setDate(j,m,a);
}


ITodo::~ITodo()
{

}

/**
 * @brief Destructeur de la classe ITodo.
 */
ITodo::ITodo(std::string c)
{
    setContenu(c);
    //date = floor<days>(system_clock::now());
}




/**
 * @return Le contenu du todo.
 */
std::string ITodo::getContenu(){
    return contenu;
}

/**
 * @return La date du todo.
 */
day_point ITodo::getDate(){
    return date;
}


std::string ITodo::getDateAsString() const {
    // Utilisez un std::stringstream pour effectuer la conversion
    std::stringstream ss;
    ss << date; // Suppose que day_point a une surcharge d'opérateur pour l'opérateur <<

    // Retournez la chaîne résultante
    return ss.str();
}


/**
 * @brief Définit le contenu du todo.
 * @param s Le nouveau contenu du todo.
 */
void ITodo::setContenu(std::string s){
    contenu= s;
}


/**
 * @brief Définit la date du todo.
 * @param d La nouvelle date du todo.
 */
void ITodo::setDate(const int &j, const int &m, const int &a){
    //extraire la date courante
    auto ymd2 = year(a)/month(m)/day(j);
    date = day_point{ymd2};
}


/**
 * @brief Définit la date du todo.
 * @param dp La nouvelle date du todo.
 */
void ITodo::setDateDP(const day_point &dp)
{
    date = dp;
}




/**
 * @return Une chaîne de caractères représentant le todo.
 */
std::string ITodo::Affichage()
{
    auto ymd = year_month_day{date};
    std::ostringstream oss;
    oss << ymd.year() << '-' << std::setw(2) << std::setfill('0') << (unsigned)ymd.month() << '-' << std::setw(2) << std::setfill('0') << (unsigned)ymd.day();
    std::string s = oss.str();
    std::string aff = "@todo " + getContenu() + " @date " + s;
    return aff;
}
