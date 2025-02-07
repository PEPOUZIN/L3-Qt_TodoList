/**
 *@file gestiontodo.h
 *
*/


#ifndef GESTIONTODO_H
#define GESTIONTODO_H

#include <list>
#include "todo.h"

class GestionTodo
{
public:
    GestionTodo();

    void addTodo(const ITodo &todo);
    const std::list<ITodo>& getTodos() const;
    void delTodo(ITodo &todos);
private:
    std::list<ITodo> todos;



};

#endif // GESTIONTODO_H
