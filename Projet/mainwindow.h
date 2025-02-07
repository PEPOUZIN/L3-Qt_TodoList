/**
 *@file mainwindow.h
 *
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "gestioncontact.h"
#include "historiquedialogue.h"
#include "interactiondialogue.h"
#include "tododialogue.h"
#include <QListWidgetItem>
#include <QMainWindow>
#include <QFileDialog>
#include <QPixmap>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GestionContact gc;
    InteractionDialogue *interactionDialogue;
    TodoDialogue *todoDialogue;
    HistoriqueDialogue *historiqueDialogue;



    void updateContact(QListWidgetItem *item, const QString &updatedContactString);
    void displayInteractions(const Contact &contact);
    void updateContactListUI(const QList<Contact> &sortedContacts);
    QList<Contact> getContacts(const std::function<bool(const Contact&, const Contact&)>& comparator);
    void infoFromTodoDialogue(const QString& info1);
    void displayTodos(const Interaction &interaction);
    void rechercherParNom(const QString &text);
    void rechercherParPrenom(const QString &text);
    void rechercherParEntreprise(const QString &text);
    void rechercherParMail(const QString &text);
    void upDateBDContact();
    void updateLastModificationLabel(const std::chrono::time_point<std::chrono::system_clock> &modificationDate);
    Contact getSelectedContact(int index);



private slots:
    void onBt_ValiderContact();
    void onBt_ModifierContact();
    void onBt_SupprimerContact();
    void onContactItemSelected(QListWidgetItem *item);
    void afficherInteractionDialogue();
    void infoFromInteractionDialogue(const QString& info1);
    void modifierInteractionDepuisListe();
    void onRadioButtonClicked();
    void onBt_SupprimerInteraction();
    void rechercher(const QString &text);
    void onInteractionClicked(QListWidgetItem *item);
    void onBt_SupprimerTodo();
    void onBt_Historique();
    void afficherTodoDialogue();
    void exportToJson();


};
#endif // MAINWINDOW_H
