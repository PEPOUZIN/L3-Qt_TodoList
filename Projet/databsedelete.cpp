/**
 * @file databasedelete.cpp
 * @brief Implémentation de la classe DatabaseDelete.
 */

#include "databsedelete.h"

/**
 * @brief Constructeur de la classe DatabaseDelete.
 * @param dbName Nom de la base de données.
 */
DatabaseDelete::DatabaseDelete(const QString& dbName) {
    if (QSqlDatabase::contains(dbName)) {
        QSqlDatabase::removeDatabase(dbName);
    }

    db = QSqlDatabase::addDatabase("QSQLITE", dbName);
    db.setDatabaseName(dbName);
}

/**
 * @brief Destructeur de la classe DatabaseDelete.
 */
DatabaseDelete::~DatabaseDelete() {
    closeDatabase();
}

/**
 * @brief Ouvre la connexion à la base de données.
 */
void DatabaseDelete::openDatabase() {
    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "Erreur lors de l'ouverture de la base de données : " << db.lastError().text();
            // Gérer l'erreur selon vos besoins
        } else {
            qDebug() << "Base de données ouverte avec succès.";
        }
    } else {
        qDebug() << "La connexion à la base de données existe déjà.";
    }
}

/**
 * @brief Ferme la connexion à la base de données.
 */
void DatabaseDelete::closeDatabase() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Base de données fermée avec succès.";
    } else {
        qDebug() << "La connexion à la base de données n'est pas ouverte.";
    }
}

/**
 * @brief Supprime un contact de la base de données.
 * @param contact Le contact à supprimer.
 * @param contactId L'ID du contact à supprimer.
 */
void DatabaseDelete::deleteContact(const Contact& contact, int contactId) {
    openDatabase();

    if (contactId == -1) {
        qDebug() << "Le contact n'a pas été trouvé.";
        closeDatabase();
        return;
    }

    // Supprimez les interactions associées
    deleteInteraction(contactId);

    // Supprimez le contact
    QSqlQuery query(db);
    query.prepare("DELETE FROM contacts WHERE id = ?");
    query.addBindValue(contactId);

    if (!query.exec()) {
        qDebug() << "Erreur de suppression du contact : " << query.lastError().text();
        // Gérer l'erreur selon vos besoins
    }

    closeDatabase();
}

/**
 * @brief Supprime les interactions associées à un contact.
 * @param contactId L'ID du contact.
 */
void DatabaseDelete::deleteInteraction(int contactId) {
    // Récupérez les IDs des interactions associées au contact
    QSqlQuery selectQuery(db);
    selectQuery.prepare("SELECT id FROM interactions WHERE contact_id = ?");
    selectQuery.addBindValue(contactId);

    if (!selectQuery.exec()) {
        qDebug() << "Erreur lors de la récupération des IDs d'interactions : " << selectQuery.lastError().text();
        // Gérer l'erreur selon vos besoins
        return;
    }

    // Supprimez les todos associés aux interactions supprimées et les enregistrements de la table de liaison
    while (selectQuery.next()) {
        int interactionId = selectQuery.value(0).toInt();
        qDebug()<< interactionId << "Id interactionId";
        deleteTodoAndInteraction(interactionId);
    }

    qDebug() << "Interactions, todos, et enregistrements de la table de liaison associés supprimés avec succès.";
}

/**
 * @brief Supprime les todos et les enregistrements de la table de liaison associés à une interaction.
 * @param interactionId L'ID de l'interaction.
 */
void DatabaseDelete::deleteTodoAndInteraction(int interactionId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM todos WHERE id IN (SELECT todo_id FROM interaction_todo WHERE interaction_id = ?)");
    query.addBindValue(interactionId);

    if (!query.exec()) {
        qDebug() << "Erreur de suppression des todos : " << query.lastError().text();
        // Gérer l'erreur selon vos besoins
        return;
    }

    // Supprimer les enregistrements de la table de liaison (interaction_todo)
    query.prepare("DELETE FROM interaction_todo WHERE interaction_id = ?");
    query.addBindValue(interactionId);

    if (!query.exec()) {
        qDebug() << "Erreur de suppression des enregistrements de la table de liaison : " << query.lastError().text();
        // Gérer l'erreur selon vos besoins
        return;
    }

    // Enfin, supprimer l'interaction
    query.prepare("DELETE FROM interactions WHERE id = ?");
    query.addBindValue(interactionId);

    if (!query.exec()) {
        qDebug() << "Erreur de suppression de l'interaction : " << query.lastError().text();
        // Gérer l'erreur selon vos besoins
        return;
    }

    qDebug() << "Todos, et enregistrements de la table de liaison associés à l'interaction supprimés avec succès.";
}

/**
 * @brief Récupère l'ID d'un contact à partir de son numéro de téléphone.
 * @param phoneNumber Le numéro de téléphone du contact.
 * @return L'ID du contact.
 */
int DatabaseDelete::getContactIdByPhoneNumber(const QString& phoneNumber) {
    openDatabase();

    QSqlQuery query(db);
    query.prepare("SELECT id FROM contacts WHERE telephone = ?");
    query.addBindValue(phoneNumber);

    int contactId = -1;
    if (query.exec() && query.next()) {
        contactId = query.value(0).toInt();
    } else {
        qDebug() << "Erreur lors de la récupération de l'ID du contact par numéro de téléphone : " << query.lastError().text();
    }

    closeDatabase();
    return contactId;
}

/**
 * @brief Récupère l'ID d'une interaction à partir de son contenu.
 * @param content Le contenu de l'interaction.
 * @return L'ID de l'interaction.
 */
int DatabaseDelete::getInteractionIdByContent(const QString& content) {
    openDatabase();

    QSqlQuery query(db);
    query.prepare("SELECT id FROM interactions WHERE contenu = ?");
    query.addBindValue(content);

    int interactionId = -1;
    if (query.exec() && query.next()) {
        interactionId = query.value(0).toInt();
    } else {
        qDebug() << "Erreur lors de la récupération de l'ID de l'interaction : " << query.lastError().text();
    }

    closeDatabase();
    return interactionId;
}
