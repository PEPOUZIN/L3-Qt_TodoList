//#include "associationinteractiontodo.h"
#include "mainwindow.h"
//#include "contact.h"
//#include "gestioncontact.h"
//#include "todo.h"
#include "table.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <chrono>
#include <iostream>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Table t;
    t.createDatabase();

/*
    // Créez un gestionnaire de contacts
    GestionContact gc;

    // Créez un contact
    Contact c("John", "Doe", "CompanyA", "file", "john@example.com", "123456789");

    // Ajoutez le contact au gestionnaire de contacts
    gc.addContact(c);
    // Créez une interaction pour ce contact
    Interaction i1("Meeting",23, 05, 2012);
    Interaction i2("Call",25, 05, 2017);

    // Ajoutez ces interactions au contact
    c.addInteraction(i1);
    c.addInteraction(i2);

    // Créez des todos pour ces interactions
    ITodo todo1("Prepare presentation");
    ITodo todo2("Send follow-up email");
    ITodo todo3("Call back client");

    // Créez un gestionnaire pour les associations
    AssociationInteractionTodo assoc(&i1, &todo1);
    AssociationInteractionTodo assoc1(&i1, &todo2);
    AssociationInteractionTodo assoc2(&i2, &todo3);

    c.addAssociation(assoc);
    c.addAssociation(assoc1);
    c.addAssociation(assoc2);
    std::list<AssociationInteractionTodo> associations = c.getAssociationsByInteraction(i1);
    qDebug() << associations.size();
    qDebug() << c.showListAssociation();

    c.removeAssociationByTodo(todo2);
    //c.removeAssociationByTodo(todo1);
    qDebug() << c.showListAssociation();

    c.addAssociation(AssociationInteractionTodo(&i2, &todo1));
    qDebug() << c.showListAssociation();

    c.getInteractionAt(0).setContenu("ouiiiiiiiiiiiiiiiii");
    c.updateAssociationsAfterInteractionUpdate(c.getInteractionAt(1));
    qDebug() << "Interactions:";
    for (const Interaction& interaction : c.getInteraction()) {
        qDebug() << QString::fromStdString(interaction.Affichage());
    }

    qDebug() << c.showListAssociation();

    c.addAssociation(AssociationInteractionTodo(&i2, &todo2));
    qDebug() << c.showListAssociation();*/
    return a.exec();
}
