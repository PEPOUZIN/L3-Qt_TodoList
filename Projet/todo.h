/**
 *@file todo.h
*/


#ifndef ITODO_H
#define ITODO_H

#include <string>

#include "date.h"

using namespace date;
using namespace std::chrono;
using day_point = std::chrono::time_point<std::chrono::system_clock, days>;





class ITodo

{


private:

    std::string contenu;
    day_point date;



public:

    ITodo(std::string contenu, const int &, const int &, const int &);
    ITodo(std::string contenu);
    ~ITodo();

    std::string getContenu();
    void setContenu(std::string);
    day_point getDate();
    void setDate(const int &, const int &, const int &);
    void setDateDP(const day_point &);
    std::string getDateAsString() const;


    std::string Affichage();
};

#endif // ITODO_H
