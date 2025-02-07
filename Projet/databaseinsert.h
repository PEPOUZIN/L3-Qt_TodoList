/**
 *@file databaseinsert.h
 *
*/


#ifndef DATABASEINSERT_H
#define DATABASEINSERT_H

// databaseinsert.h

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "contact.h"
#include "interaction.h"
#include "todo.h"

class DatabaseInsert {
private:
    QSqlDatabase db;

public:
    DatabaseInsert(const QString& dbName);
    ~DatabaseInsert();

    void openDatabase();
    void closeDatabase();

    void insertContact(const Contact& contact);
    void insertInteraction(const Interaction& interaction, int contactId);
    void insertTodo( ITodo& todo, int interactionId);
    int  getInteractionIdByContent(const QString& content);
    int getContactIdByPhoneNumber(const QString& phoneNumber);
    void updateContact(const QString& selectedItem, int contactId);
    std::list<Contact> getAllContactsFromDB();
    std::list<Interaction> getInteractionsForContact(int contactId);
    std::list<ITodo> getTodosForContact(int interactionID);



};

#endif
