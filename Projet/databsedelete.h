/**
 *@file databsedelete.h
 *
*/

#ifndef DATABASEDELETE_H
#define DATABASEDELETE_H

#include "contact.h"
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

class DatabaseDelete {
public:
    DatabaseDelete(const QString& dbName);
    ~DatabaseDelete();

    void openDatabase();
    void closeDatabase();

    void deleteContact(const Contact& contact, int contactId);
    void deleteInteraction(int conatctID);
    void deleteTodo(int todoId);
    int getInteractionIdByContent(const QString& content);
    void deleteTodoAndInteraction(int interactionId);

    int getContactIdByPhoneNumber(const QString& phoneNumber);
private:
    QSqlDatabase db;
};

#endif // DATABASEDELETE_H
