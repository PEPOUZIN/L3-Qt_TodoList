/**
 * @file databaseinsert.cpp
 * @brief Implémentation de la classe DatabaseInsert.
 */

#include "databaseinsert.h"
#include "contact.h"
#include "interaction.h"
#include "todo.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QDateTime>
#include "databaseinsert.h"

/**
 * @brief Constructeur de la classe DatabaseInsert.
 * @param dbName Nom de la base de données.
 */
DatabaseInsert::DatabaseInsert(const QString& dbName) {
    // Supprimez la connexion existante si elle existe
    if (QSqlDatabase::contains(dbName)) {
        QSqlDatabase::removeDatabase(dbName);
    }

    // Ajoutez la nouvelle connexion
    db = QSqlDatabase::addDatabase("QSQLITE", dbName);
    db.setDatabaseName(dbName);

    // Ouvrez la connexion à la base de données
    if (!db.open()) {
        qDebug() << "Erreur lors de l'ouverture de la base de données : " << db.lastError().text();
        // Gérer l'erreur selon vos besoins
    } else {
        qDebug() << "Base de données ouverte avec succès.";
    }
}

/**
 * @brief Destructeur de la classe DatabaseInsert.
 */
DatabaseInsert::~DatabaseInsert() {
    // Fermez la connexion à la base de données
    if (db.isOpen()) {
        db.close();
        qDebug() << "Base de données fermée avec succès.";
    }
}

/**
 * @brief Ouvre la connexion à la base de données.
 */
void DatabaseInsert::openDatabase() {
    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "Erreur lors de l'ouverture de la base de données : " << db.lastError().text();
            // Gérer l'erreur selon vos besoins
        } else {
            qDebug() << "Base de données ouverte avec succès.";
        }
    }
}

/**
 * @brief Ferme la connexion à la base de données.
 */
void DatabaseInsert::closeDatabase() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Base de données fermée avec succès.";
    }
}

/**
 * @brief Insère un contact dans la base de données.
 * @param contact Le contact à insérer.
 */
void DatabaseInsert::insertContact(const Contact& contact) {
    openDatabase();

    QSqlQuery query(db);
    query.prepare("INSERT INTO contacts (nom, prenom, entreprise, photo, mail, telephone) VALUES (?, ?, ?, ?, ?, ?)");

    query.addBindValue(QString::fromStdString(contact.getNom()));
    query.addBindValue(QString::fromStdString(contact.getPrenom()));
    query.addBindValue(QString::fromStdString(contact.getEntreprise()));
    query.addBindValue(QString::fromStdString(contact.getPhoto()));
    query.addBindValue(QString::fromStdString(contact.getMail()));
    query.addBindValue(QString::fromStdString(contact.getTelephone()));

    if (!query.exec()) {
        qDebug() << "Erreur d'insertion du contact : " << query.lastError().text();
        closeDatabase();
        return;
    }

    closeDatabase();
}

/**
 * @brief Insère une interaction dans la base de données associée à un contact donné.
 * @param interaction L'interaction à insérer.
 * @param contactId L'ID du contact associé.
 */
void DatabaseInsert::insertInteraction(const Interaction& interaction, int contactId) {
    openDatabase();

    QSqlQuery query(db);
    query.prepare("INSERT INTO interactions (contact_id, contenu, date) VALUES (?, ?, ?)");

    query.addBindValue(contactId);
    query.addBindValue(QString::fromStdString(interaction.getContenu()));

    auto timePoint = interaction.getDate();
    auto time = std::chrono::system_clock::to_time_t(timePoint);
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(static_cast<quint64>(time));
    query.addBindValue(dateTime.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Erreur d'insertion de l'interaction : " << query.lastError().text();
    }

    closeDatabase();
}

/**
 * @brief Insère un todo dans la base de données associé à une interaction donnée.
 * @param todo Le todo à insérer.
 * @param interactionId L'ID de l'interaction associée.
 */
void DatabaseInsert::insertTodo(ITodo& todo, int interactionId) {
    openDatabase();

    QSqlQuery query(db);
    query.prepare("INSERT INTO todos (contenu, date) VALUES(:contenu,:date)");
    query.bindValue(":contenu", QString::fromStdString(todo.getContenu()));

    auto timePoint = todo.getDate();
    auto time = std::chrono::system_clock::to_time_t(timePoint);
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(static_cast<quint64>(time));
    query.bindValue(":date", dateTime.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Erreur d'insertion du Todo avec interaction : " << query.lastError().text();
    }

    // Récupérez l'ID du Todo inséré
    int todoId = query.lastInsertId().toInt();
    qDebug() << todoId;

    // Insérez l'association dans la table de jointure
    query.prepare("INSERT INTO interaction_todo (interaction_id, todo_id) VALUES (?, ?)");
    query.addBindValue(interactionId);
    query.addBindValue(todoId);

    if (!query.exec()) {
        qDebug() << "Erreur d'insertion dans la table de jointure interaction_todo : " << query.lastError().text();
    }

    qDebug() << "Fin insertTodo";
    closeDatabase();
}

/**
 * @brief Récupère l'ID d'une interaction à partir de son contenu.
 * @param content Le contenu de l'interaction.
 * @return L'ID de l'interaction.
 */
int DatabaseInsert::getInteractionIdByContent(const QString& content) {
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

    return interactionId;
}

/**
 * @brief Récupère l'ID d'un contact à partir de son numéro de téléphone.
 * @param phoneNumber Le numéro de téléphone du contact.
 * @return L'ID du contact.
 */
int DatabaseInsert::getContactIdByPhoneNumber(const QString& phoneNumber) {
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
 * @brief Met à jour les informations d'un contact dans la base de données.
 * @param selectedItem Les nouvelles informations du contact.
 * @param contactId L'ID du contact à mettre à jour.
 */
void DatabaseInsert::updateContact(const QString& selectedItem, int contactId) {
    openDatabase();

    QStringList updatedContactList = selectedItem.split(" ");

    QSqlQuery query(db);
    query.prepare("UPDATE contacts SET nom = ?, prenom = ?, entreprise = ?, photo = ?, mail = ?, telephone = ? WHERE id = ?");

    query.addBindValue(updatedContactList[0]);
    query.addBindValue(updatedContactList[1]);
    query.addBindValue(updatedContactList[2]);
    query.addBindValue(updatedContactList[3]);
    query.addBindValue(updatedContactList[4]);
    query.addBindValue(updatedContactList[5]);
    query.addBindValue(contactId);

    if (!query.exec()) {
        qDebug() << "Erreur de mise à jour du contact : " << query.lastError().text();
        // Gérer l'erreur selon vos besoins
    } else {
        qDebug() << "Contact mis à jour avec succès.";
    }


}

/**
 * @brief Récupère tous les contacts de la base de données.
 * @return Liste de tous les contacts.
 */
std::list<Contact> DatabaseInsert::getAllContactsFromDB() {
    openDatabase();

    std::list<Contact> contactsList;

    QSqlQuery queryContacts("SELECT * FROM contacts", db);
    while (queryContacts.next()) {
        Contact contact;
        contact.setNom(queryContacts.value("nom").toString().toStdString());
        contact.setPrenom(queryContacts.value("prenom").toString().toStdString());
        contact.setEntreprise(queryContacts.value("entreprise").toString().toStdString());
        contact.setPhoto(queryContacts.value("photo").toString().toStdString());
        contact.setMail(queryContacts.value("mail").toString().toStdString());
        contact.setTelephone(queryContacts.value("telephone").toString().toStdString());

        // Récupérez et ajoutez les interactions associées à ce contact
        int contactId = queryContacts.value("id").toInt();
        std::list<Interaction> interactionsList = getInteractionsForContact(contactId);

        ///////////////////////////////////////////////////////////////////////////

        qDebug() << interactionsList.size() << "taille";
        for (auto listI : interactionsList) {
            contact.addInteraction(listI);
            qDebug() << listI.getContenu() << "contenue";
            int interactionID = getInteractionIdByContent(QString::fromStdString(listI.getContenu()));
            qDebug() << interactionID << "interactionID";
        }

        //////////////////////////////////////////////////////////////////////////
        // contact.updateInteractionList(interactionsList);
        contactsList.push_back(contact);
    }

    closeDatabase();

    return contactsList;
}

/**
 * @brief Récupère les interactions associées à un contact.
 * @param contactId L'ID du contact.
 * @return Liste des interactions associées.
 */
std::list<Interaction> DatabaseInsert::getInteractionsForContact(int contactId) {
    openDatabase();
    std::list<Interaction> interactionsList;

    QSqlQuery queryA(db);
    queryA.prepare("SELECT * FROM interactions WHERE contact_id = ?");
    queryA.addBindValue(contactId);

    if (queryA.exec()) {
        while (queryA.next()) {
            std::string contenu = queryA.value("contenu").toString().toStdString();
            std::string dateString = queryA.value("date").toString().toStdString();
            int day, month, year;
            char slash; // Pour stocker le caractère "/"

            std::istringstream dateStream(dateString);
            dateStream >> day >> slash >> month >> slash >> year;

            // Formatter la date en "jour mois année"
            std::ostringstream formattedDate;
            formattedDate << year << " " << month << " " << day;

            Interaction interaction(contenu, year, month, day);
            interactionsList.push_back(interaction);
        }
    } else {
        qDebug() << "Erreur lors de la récupération des interactions : " << queryA.lastError().text();
    }

    return interactionsList;
}
