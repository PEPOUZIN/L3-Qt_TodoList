/**
 * @file table.cpp
 */

#include "table.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <chrono>
#include <iostream>

/**
 * @brief Constructeur par défaut de la classe Table.
 */
Table::Table() {

}

/**
 * @brief Crée la base de données SQLite et les tables nécessaires si elles n'existent pas déjà.
 */
void Table::createDatabase() {
    // Spécifiez le nom de votre base de données SQLite
    QString dbName = "base.sqlite";

    // Initialisez la base de données
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    // Ouvrez la connexion à la base de données
    if (!db.open()) {
        qDebug() << "Erreur lors de l'ouverture de la base de données:" << db.lastError().text();
        return;
    }

    QSqlQuery query;

    // Vérifiez si la table des contacts existe
    bool isContactsTableExists = db.tables().contains("contacts");
    if (!isContactsTableExists) {
        // Créez la table des contacts
        if (!query.exec("CREATE TABLE contacts ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "nom TEXT NOT NULL,"
                        "prenom TEXT NOT NULL,"
                        "entreprise TEXT,"
                        "photo TEXT,"
                        "mail TEXT,"
                        "telephone TEXT)")) {
            qDebug() << "Erreur lors de la création de la table des contacts:" << query.lastError().text();
            // Fermez la connexion à la base de données en cas d'erreur
            db.close();
            return;
        }
    }

    // Vérifiez si la table des interactions existe
    bool isInteractionsTableExists = db.tables().contains("interactions");
    if (!isInteractionsTableExists) {
        // Créez la table des interactions
        if (!query.exec("CREATE TABLE interactions ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "contact_id INTEGER NOT NULL,"
                        "contenu TEXT NOT NULL,"
                        "date DATE NOT NULL,"
                        "FOREIGN KEY(contact_id) REFERENCES contacts(id))")) {
            qDebug() << "Erreur lors de la création de la table des interactions:" << query.lastError().text();
            // Fermez la connexion à la base de données en cas d'erreur
            db.close();
            return;
        }
    }

    // Vérifiez si la table des todos existe
    bool isTodosTableExists = db.tables().contains("todos");
    if (!isTodosTableExists) {
        // Créez la table des todos
        if (!query.exec("CREATE TABLE todos ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "contenu TEXT NOT NULL,"
                        "date DATE NOT NULL)")) {
            qDebug() << "Erreur lors de la création de la table des todos:" << query.lastError().text();
            // Fermez la connexion à la base de données en cas d'erreur
            db.close();
            return;
        }
    }

    // Vérifiez si la table de jointure existe
    bool isInteractionTodoTableExists = db.tables().contains("interaction_todo");
    if (!isInteractionTodoTableExists) {
        // Créez la table de jointure pour gérer la relation entre interactions et todos
        if (!query.exec("CREATE TABLE interaction_todo ("
                        "interaction_id INTEGER,"
                        "todo_id INTEGER,"
                        "FOREIGN KEY(interaction_id) REFERENCES interactions(id),"
                        "FOREIGN KEY(todo_id) REFERENCES todos(id))")) {
            qDebug() << "Erreur lors de la création de la table de jointure interaction_todo:" << query.lastError().text();
            // Fermez la connexion à la base de données en cas d'erreur
            db.close();
            return;
        }
    }

    // Fermez la connexion à la base de données
    db.close();
}
