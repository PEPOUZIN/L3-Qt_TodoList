/**
 * @file mainwindow.cpp
 */


#include "mainwindow.h"
#include "databsedelete.h"
#include "databaseinsert.h"
#include "historiquedialogue.h"
#include "qdatetime.h"
#include "qdebug.h"
#include "ui_mainwindow.h"
#include "contact.h"
#include "gestioncontact.h"
#include "QFileInfo"
#include "interactiondialogue.h"
#include "associationinteractiontodo.h"
#include <QMessageBox>
#include <QtAlgorithms>
#include <QList>
#include <functional> // Pour std::function
#include <QRegularExpressionValidator>
#include <iostream>
#include <iomanip> // Include this for setw and setfill
#include <QListWidgetItem>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <iostream>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->Line_Nom->setPlaceholderText("Nom: ");
    ui->Line_Prenom->setPlaceholderText("Prénom: ");
    ui->Line_Entreprise->setPlaceholderText("Entreprise: ");
    ui->Line_Mail->setPlaceholderText("Mail: ");
    ui->Line_Numero->setPlaceholderText("Numéro: ");



    connect(ui->Bt_Valider_Contact, SIGNAL(clicked()), this, SLOT(onBt_ValiderContact()));

    connect(ui->Text_Contact, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onContactItemSelected(QListWidgetItem*)));
    connect(ui->Bt_Supprimer_Contact, SIGNAL(clicked()), this, SLOT(onBt_SupprimerContact()));
    connect(ui->Bt_Modifier_Contact, SIGNAL(clicked()), this, SLOT(onBt_ModifierContact()));
    connect(ui->Bt_Valider_Interaction, SIGNAL(clicked()), this, SLOT(afficherInteractionDialogue()));

    interactionDialogue = new InteractionDialogue(this);
    connect(interactionDialogue, &InteractionDialogue::informationsValidees, this, &MainWindow::infoFromInteractionDialogue);
    connect(ui->Bt_Supprimer_Interaction, SIGNAL(clicked()), this, SLOT(onBt_SupprimerInteraction()));


    todoDialogue = new TodoDialogue(this);
    connect(todoDialogue, &TodoDialogue::informationsValidees, this, &MainWindow::infoFromTodoDialogue);
    connect(ui->Bt_Ajouter_Todo, SIGNAL(clicked()), this, SLOT(afficherTodoDialogue()));
    connect(ui->Text_Interaction, &QListWidget::itemClicked, this, &MainWindow::onInteractionClicked);
    connect(ui->Bt_Supprimer_Todo, SIGNAL(clicked()), this, SLOT(onBt_SupprimerTodo()));


    connect(ui->radio_Nom, SIGNAL(clicked()), this, SLOT(onRadioButtonClicked()));
    connect(ui->radio_Prenom, SIGNAL(clicked()), this, SLOT(onRadioButtonClicked()));
    connect(ui->radio_Entreprise, SIGNAL(clicked()), this, SLOT(onRadioButtonClicked()));
    connect(ui->radio_Mail, SIGNAL(clicked()), this, SLOT(onRadioButtonClicked()));



    historiqueDialogue = new HistoriqueDialogue(this);
    connect(ui->menuHistorique, SIGNAL(clicked()), this, SLOT(onBt_Historique()));



    QRegularExpression regex_lettre("^[A-Z][a-z\\-]*$");
    QRegularExpressionValidator *validator_lettre = new QRegularExpressionValidator(regex_lettre, this);
    ui->Line_Nom->setValidator(validator_lettre);
    ui->Line_Prenom->setValidator(validator_lettre);

    QRegularExpression regex_num("[0-9]+");
    QRegularExpressionValidator *validator_num = new QRegularExpressionValidator(regex_num, this);
    ui->Line_Numero->setValidator(validator_num);

    ui->comboBox->addItems({"Nom", "Prenom", "Entreprise"});
    connect(ui->line_Recherche, &QLineEdit::textChanged, this, &MainWindow::rechercher);

    connect(ui->exportJSON, SIGNAL(clicked()), this, SLOT(exportToJson()));

    //Appel a la BD
    upDateBDContact();


}
/**
 * @brief Met à jour la liste de contacts à partir de la base de données.
 *
 * Cette fonction initialise la liste de contacts de l'application en récupérant
 * les données depuis la base de données SQLite.
 */
void MainWindow::upDateBDContact(){
    // Dans votre code où vous souhaitez mettre à jour la liste de contacts dans GestionContact
    DatabaseInsert database("base.sqlite");
    std::list<Contact> contactsList = database.getAllContactsFromDB();


    // Assurez-vous que GestionContact a une méthode addContact pour ajouter des contacts à la liste
    for (const auto& contact : contactsList) {
        gc.addContact(contact);
        std::string nom = contact.getNom();
        std::string prenom = contact.getPrenom();
        std::string entreprise = contact.getEntreprise();
        std::string mail = contact.getMail();
        std::string numero = contact.getTelephone();
        QString contactString = QString::fromStdString(nom +" "+ prenom +" "+ entreprise +" "+ mail +" "+ numero);
        ui->Text_Contact->addItem(contactString);
    }
}

/**
 * @brief Recherche des contacts en fonction du texte fourni.
 * @param text Le texte à rechercher.
 *
 * Cette fonction effectue une recherche dans la liste des contacts
 * en fonction du texte fourni et met à jour l'affichage en conséquence.
 */
void MainWindow::rechercher(const QString &text) {
    // Obtenez le choix actuel de la combobox
    QString choixRecherche = ui->comboBox->currentText();

    // En fonction du choix, effectuez la recherche dans la liste des contacts
    if (choixRecherche == "Nom") {
        rechercherParNom(text);
    } else if (choixRecherche == "Prenom") {
        rechercherParPrenom(text);
    } else if (choixRecherche == "Entreprise") {
        rechercherParEntreprise(text);
    } else if (choixRecherche == "Mail") {
        rechercherParMail(text);
    }

}

void MainWindow::rechercherParNom(const QString &text) {
    ui->Text_Contact->clear(); // Efface la liste actuelle

    // Parcours de la liste de contacts
    for (const Contact &contact : gc.getContactsListe()) {
        // Si le nom du contact contient le texte de recherche (insensible à la casse)
        if (QString::fromStdString(contact.getNom()).contains(text, Qt::CaseInsensitive)) {
            // Ajoutez le contact correspondant à la liste
            QString contactString = QString::fromStdString(
                contact.getPrenom() + " " + contact.getNom() + " " + contact.getEntreprise() +" "+
                " " + contact.getMail() + " " +
                " " + contact.getTelephone()
                );
            ui->Text_Contact->addItem(contactString);
        }
    }
}

// Fonction de recherche par prénom (similaire à la recherche par nom)
void MainWindow::rechercherParPrenom(const QString &text) {
    ui->Text_Contact->clear();

    for (const Contact &contact : gc.getContactsListe()) {
        if (QString::fromStdString(contact.getPrenom()).contains(text, Qt::CaseInsensitive)) {
            QString contactString = QString::fromStdString(
                contact.getPrenom() + " " + contact.getNom() + " " + contact.getEntreprise() +" "+
                " " + contact.getMail() + " " +
                " " + contact.getTelephone()
                );
            ui->Text_Contact->addItem(contactString);
        }
    }
}

// Fonction de recherche par entreprise
void MainWindow::rechercherParEntreprise(const QString &text) {
    ui->Text_Contact->clear();

    for (const Contact &contact : gc.getContactsListe()) {
        if (QString::fromStdString(contact.getEntreprise()).contains(text, Qt::CaseInsensitive)) {
            QString contactString = QString::fromStdString(
                contact.getPrenom() + " " + contact.getNom() + " " + contact.getEntreprise() +" "+
                " " + contact.getMail() + " " +
                " " + contact.getTelephone()
                );
            ui->Text_Contact->addItem(contactString);
        }
    }
}

// Fonction de recherche par e-mail
void MainWindow::rechercherParMail(const QString &text) {
    ui->Text_Contact->clear();

    for (const Contact &contact : gc.getContactsListe()) {
        if (QString::fromStdString(contact.getMail()).contains(text, Qt::CaseInsensitive)) {
            QString contactString = QString::fromStdString(
                contact.getPrenom() + " " + contact.getNom() + " " + contact.getEntreprise() +" "+
                " " + contact.getMail() + " " +
                " " + contact.getTelephone()
                );
            ui->Text_Contact->addItem(contactString);
        }
    }
}
/**
 * @brief Met à jour les UI quand on selectionne un conatct
 * @param item selectionne l'item de la qListWidget
 */
void MainWindow::onContactItemSelected(QListWidgetItem *item) {
    // Récupérer l'index de l'élément sélectionné
    int selectedIndex = ui->Text_Contact->row(item);

    // Récupérer le contact correspondant
    const Contact &selectedContact = gc.getContact(selectedIndex);

    // Supposez que getPhoto() retourne le chemin du fichier pour chaque contact
    QString photoPath = QString::fromStdString(selectedContact.getPhoto());

    // Assurez-vous que le chemin de la photo n'est pas vide
    if (!photoPath.isEmpty()) {
        QPixmap photo(photoPath);

        // Assurez-vous que la photo est valide
        if (!photo.isNull()) {
            ui->Label_Photo->setPixmap(photo);
            ui->Label_Photo->setScaledContents(true);
        } else {
            qDebug() << "Erreur : Impossible de charger la photo.";
        }
    } else {
        qDebug() << "Chemin de la photo vide.";
    }


    ui->Line_Nom->setText(QString::fromStdString(selectedContact.getPrenom()));
    ui->Line_Prenom->setText(QString::fromStdString(selectedContact.getNom()));
    ui->Line_Entreprise->setText(QString::fromStdString(selectedContact.getEntreprise()));
    ui->Line_Mail->setText(QString::fromStdString(selectedContact.getMail()));
    ui->Line_Numero->setText(QString::fromStdString(selectedContact.getTelephone()));




    updateLastModificationLabel(selectedContact.getDate());

    // Afficher les interactions correspondantes dans Text_Interactions
    displayInteractions(selectedContact);
    ui->Text_Todo->clear();

}



MainWindow::~MainWindow() {
    if (interactionDialogue) {
        delete interactionDialogue;
        interactionDialogue = nullptr;  // Facultatif, mais une bonne pratique pour éviter les pointeurs invalides
    }

    if (todoDialogue) {
        delete todoDialogue;
        todoDialogue = nullptr;  // Facultatif, mais une bonne pratique pour éviter les pointeurs invalides
    }
    delete ui;
}



/**
 * @brief Créer un contact
 */
void MainWindow::onBt_ValiderContact(){
    std::string nom = ui->Line_Nom->text().toStdString();
    std::string prenom = ui->Line_Prenom->text().toStdString();
    std::string entreprise = ui->Line_Entreprise->text().toStdString();
    std::string mail = ui->Line_Mail->text().toStdString();
    std::string numero = ui->Line_Numero->text().toStdString();

    QString filePath = QFileDialog::getOpenFileName(this, "Sélectionner une image", QString(), "Images (*.png *.jpg *.jpeg *.bmp *.gif)");

    if (!filePath.isEmpty()) {
        int selectedContactIndex = ui->Text_Contact->currentRow();
        if (selectedContactIndex >= 0) {
            gc.getContact(selectedContactIndex).setPhoto(filePath.toStdString());
            if (selectedContactIndex == ui->Text_Contact->currentIndex().row()) {
                ui->Label_Photo->setPixmap(QPixmap(filePath));
                ui->Label_Photo->setScaledContents(true);
            }
        }
    }

    if (!nom.empty() && !prenom.empty() && !entreprise.empty() && !filePath.isNull() && !mail.empty() && !numero.empty() /*&& fileInfo.exists() && fileInfo.isFile()*/) {
        Contact nouveauContact(nom, prenom, entreprise,filePath.toStdString(), mail, numero);
        gc.addContact(nouveauContact);

        //Insertion base de donnée:
        DatabaseInsert databaseInsert("base.sqlite");
        databaseInsert.insertContact(nouveauContact);

        QString contactString = QString::fromStdString(nom +" "+ prenom +" "+ entreprise +" "+ mail +" "+ numero);

        ui->Text_Contact->addItem(contactString);
        auto timeNow = system_clock::now();
        auto ymd = year_month_day{ nouveauContact.getDate() };
        auto hms = make_time(timeNow - floor<days>(timeNow));

        auto day = ymd.day();
        auto month = ymd.month();
        auto year = ymd.year();
        auto hour = hms.hours().count();
        auto minute = hms.minutes().count();
        auto second = hms.seconds().count();

        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << static_cast<unsigned>(day) << "/"
            << std::setw(2) << std::setfill('0') << static_cast<unsigned>(month) << "/"
            << year << " "
            << std::setw(2) << std::setfill('0') << static_cast<unsigned>(hour) << ":"
            << std::setw(2) << std::setfill('0') << static_cast<unsigned>(minute) << ":"
            << std::setw(2) << std::setfill('0') << static_cast<unsigned>(second);

        ui->Nombre->setText(QString::number(gc.nbContact()));

        Modification modification;
        modification.timestamp = QDateTime::currentDateTime();
        modification.type = Modification::Addition;
        modification.details = "Création du contact : " + nouveauContact.getNom() + " "+ nouveauContact.getPrenom();
        nouveauContact.addModification(modification);
    }
    else {
        QMessageBox::information(this, "Manque d'informations", "Veuillez remplir toutes les cases avant de valider.");


    }
}

/**
 * @brief Met à jour le Contact séléctioné
 */
void MainWindow::onBt_ModifierContact() {

    // Récupérer les nouvelles valeurs du contact depuis les QLineEdit
    QString updatedNom = ui->Line_Nom->text();
    QString updatedPrenom = ui->Line_Prenom->text();
    QString updatedEntreprise = ui->Line_Entreprise->text();
    QString updatedMail = ui->Line_Mail->text();
    QString updatedNumero = ui->Line_Numero->text();

    // Vérifier que les champs obligatoires ne sont pas vides
    if (updatedNom.isEmpty() || updatedPrenom.isEmpty() || updatedEntreprise.isEmpty() || updatedMail.isEmpty() || updatedNumero.isEmpty()  /*updatedPhoto.isEmpty()*/) {
        QMessageBox::information(this, "Champs obligatoires", "Veuillez saisir toutes les informations avant de modifier le contact.");
        return;  // Arrêter la fonction si les champs obligatoires sont vides
    }

    // Récupérer l'élément sélectionné dans le QListWidget
    QListWidgetItem *selectedItem = ui->Text_Contact->currentItem();

    // Vérifier si un élément est sélectionné
    if (selectedItem) {
        // Récupérer l'index de l'élément sélectionné
        int selectedIndex = ui->Text_Contact->row(selectedItem);

        // Récupérer le contact associé à l'élément sélectionné dans la liste GestionContact
        Contact &contactToUpdate = gc.getContact(selectedIndex);

        //Recuperation de L'id pour la BD
        DatabaseInsert databaseInsert("base.sqlite");
        int contactId = databaseInsert.getContactIdByPhoneNumber(QString::fromStdString(contactToUpdate.getTelephone()));


        // Mettre à jour le contact avec les nouvelles valeurs
        contactToUpdate.setNom(updatedNom.toStdString());
        contactToUpdate.setPrenom(updatedPrenom.toStdString());
        contactToUpdate.setEntreprise(updatedEntreprise.toStdString());
        contactToUpdate.setMail(updatedMail.toStdString());
        contactToUpdate.setTelephone(updatedNumero.toStdString());

        // Mettre à jour la date de modification du contact
        contactToUpdate.setDate();

        // Mettre à jour le QLabel avec "Dernière modif:" suivi de la date et de l'heure actuelles
        updateLastModificationLabel(contactToUpdate.getDate());

        // Mettre à jour les champs de l'interface utilisateur
        ui->Line_Nom->setText(updatedNom);
        ui->Line_Prenom->setText(updatedPrenom);
        ui->Line_Entreprise->setText(updatedEntreprise);
        ui->Line_Mail->setText(updatedMail);
        ui->Line_Numero->setText(updatedNumero);

        QString updatedContactString = QString("%1 %2 %3 %4 %5")
                                           .arg(updatedNom)
                                           .arg(updatedPrenom)
                                           .arg(updatedEntreprise)
                                           .arg(updatedMail)
                                           .arg(updatedNumero);
        updateContact(selectedItem, updatedContactString);


        Modification modification;
        modification.timestamp = QDateTime::currentDateTime();
        modification.type = Modification::MiseAJour;
        modification.details = "Mise à jour du contact : " + contactToUpdate.getNom() + " "+ contactToUpdate.getPrenom();
        contactToUpdate.addModification(modification);

       //databaseInsert.updateContact(updatedContactString,contactId);
    }

}


/**
 * @brief Supprime un contact de la liste
 */
void MainWindow::onBt_SupprimerContact() {
    // Récupérer l'élément sélectionné dans le QListWidget
    QListWidgetItem *selectedItem = ui->Text_Contact->currentItem();

    // Vérifier si un élément est sélectionné
    if (selectedItem) {
        // Récupérer l'index de l'élément sélectionné
        int selectedIndex = ui->Text_Contact->row(selectedItem);

        //Suprimer le contact interaction et todo dans la BD
        DatabaseDelete databaseDelete("base.sqlite");
        int contactId = databaseDelete.getContactIdByPhoneNumber(QString::fromStdString(gc.getContact(selectedIndex).getTelephone()));
        databaseDelete.deleteContact(gc.getContact(selectedIndex),contactId);

        // Supprimer le contact sélectionné de la liste GestionContact
        gc.delContact(gc.getContact(selectedIndex));

        // Supprimer l'élément visuel dans le QListWidget
        delete ui->Text_Contact->takeItem(selectedIndex);

        // Effacer les informations supplémentaires dans le deuxième QListWidget
        ui->Text_Interaction->clear();
        ui->Text_Todo->clear();
        ui->Nombre->setText(QString::number(gc.nbContact()));
    }
}




/**
 * @brief Met à jour le QLabel affichant la dernière modification.
 * @param modificationDate La date de la dernière modification.
 *
 * Cette fonction prend une date de modification et met à jour le QLabel
 * avec la date et l'heure formatées.
 */
void MainWindow::updateLastModificationLabel(const std::chrono::system_clock::time_point &modificationDate) {
    // Convertir la date de modification en QString
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(std::chrono::system_clock::to_time_t(modificationDate));

    // Convertir la date et l'heure en heure locale
    dateTime = dateTime.toLocalTime();

    // Mettre à jour le QLabel avec la date et l'heure de modification
    QString lastModificationString = "Modif : " + dateTime.toString("dd/MM/yyyy hh:mm:ss");
}

/**
 * @brief Met à jour l'élément de contact visuellement.
 * @param item L'élément QListWidgetItem à mettre à jour.
 * @param updatedContactString La chaîne représentant le contact mis à jour.
 *
 * Cette fonction prend un élément QListWidgetItem et une chaîne représentant
 * le contact mis à jour, puis met à jour visuellement cet élément dans la liste.
 */
void MainWindow::updateContact(QListWidgetItem *item, const QString &updatedContactString) {
    if (item) {
        item->setText(updatedContactString);
    }
}

/**
 * @brief Obtient la liste triée des contacts en utilisant un comparateur.
 * @param comparator Le comparateur pour trier les contacts.
 * @return La liste triée des contacts.
 *
 * Cette fonction prend un comparateur et renvoie la liste triée des contacts
 * en utilisant ce comparateur.
 */
QList<Contact> MainWindow::getContacts(const std::function<bool(const Contact&, const Contact&)>& comparator) {
    // Obtenez la liste triée en utilisant la fonction de GestionContact
    std::list<Contact> sortedContacts = gc.getContacts(comparator);

    // Convertissez std::list en QList en utilisant les itérateurs
    QList<Contact> sortedQContacts;
    for (const auto& contact : sortedContacts) {
        sortedQContacts.append(contact);
    }

    return sortedQContacts;
}



/**
 * @brief Permet de choisir un tri à faire
 */
void MainWindow::onRadioButtonClicked() {
    // Déterminez le critère de tri en fonction du bouton radio sélectionné
    std::function<bool(const Contact&, const Contact&)> comparator;

    if (ui->radio_Prenom->isChecked()) {
        comparator = [](const Contact& c1, const Contact& c2) {
            return QString::compare(QString::fromStdString(c1.getPrenom()),
                                    QString::fromStdString(c2.getPrenom()),
                                    Qt::CaseInsensitive) < 0;
        };
    } else if (ui->radio_Nom->isChecked()) {
        comparator = [](const Contact& c1, const Contact& c2) {
            return QString::compare(QString::fromStdString(c1.getNom()),
                                    QString::fromStdString(c2.getNom()),
                                    Qt::CaseInsensitive) < 0;
        };
    } else if (ui->radio_Entreprise->isChecked()) {
        comparator = [](const Contact& c1, const Contact& c2) {
            return QString::compare(QString::fromStdString(c1.getEntreprise()),
                                    QString::fromStdString(c2.getEntreprise()),
                                    Qt::CaseInsensitive) < 0;
        };
    } else if (ui->radio_Mail->isChecked()) {
        comparator = [](const Contact& c1, const Contact& c2) {
            return QString::compare(QString::fromStdString(c1.getMail()),
                                    QString::fromStdString(c2.getMail()),
                                    Qt::CaseInsensitive) < 0;
        };
    } // Ajoutez d'autres cas en fonction de vos besoins

    // Obtenez la liste triée en fonction du critère sélectionné
    QList<Contact> sortedContacts = getContacts(comparator);

    // Mettez à jour votre UI avec la liste triée
    updateContactListUI(sortedContacts);
}










/**
 * @brief permet d'afficher la qDialog
 */
void MainWindow::afficherInteractionDialogue()
{
    // Vérifier s'il y a un élément sélectionné dans Text_Contact
    if (QListWidgetItem *selectedItem = ui->Text_Contact->currentItem()) {

        // Utilisez la variable membre interactionDialogue
        interactionDialogue->show();

        // Vous pouvez ajouter d'autres logiques ici si nécessaire
    } else {
        // Afficher un message ou prendre toute autre action appropriée si aucun contact n'est sélectionné
        QMessageBox::information(this, "Aucun contact sélectionné", "Veuillez sélectionner un contact avant d'ajouter une interaction.");
    }
}


/**
 * @brief affiche les interactions
 * @param choisis le contact pour ses interactions
 */
void MainWindow::displayInteractions(const Contact &contact) {
    // Effacer le contenu actuel de Text_Interactions
    ui->Text_Interaction->clear();

    // Récupérer la liste des interactions du contact
    std::list<Interaction> ls = contact.getInteraction();
    // Afficher chaque interaction dans Text_Interactions
    for (const Interaction &interaction : ls) {
        QString interactionString = QString::fromStdString(interaction.Affichage());
        QListWidgetItem *item = new QListWidgetItem(interactionString);
        ui->Text_Interaction->addItem(item);
    }
}




/**
 * @brief affiche la qDialog
 */
void MainWindow::infoFromInteractionDialogue(const QString& info1) {

    QString dateString = interactionDialogue->getDate();

    QDate selectedDate = QDate::fromString(dateString, "yyyy-MM-dd");

    int day = selectedDate.day();
    int month = selectedDate.month();
    int year = selectedDate.year();

    int selectedIndex = ui->Text_Contact->row(ui->Text_Contact->currentItem());

    // Ajouter l'interaction au contact actuellement sélectionné
    Contact &selectedContact = gc.getContact(selectedIndex);

    // Utilisez le constructeur de la classe Interaction
    Interaction newInteraction(info1.toStdString(), day, month, year);

    // Ajoutez la nouvelle interaction au contact
    selectedContact.addInteraction(newInteraction);

    //Ajoutez interaction BD
    DatabaseInsert databaseInsert("base.sqlite");
    int contactId = databaseInsert.getContactIdByPhoneNumber(QString::fromStdString(selectedContact.getTelephone()));
    databaseInsert.insertInteraction(newInteraction,contactId);

    displayInteractions(selectedContact);
}









/**
 * @brief supprime l'interaction séléctionée
 */
void MainWindow::onBt_SupprimerInteraction() {
    // Récupérer l'index de l'interaction sélectionnée dans Text_Interaction
    int selectedIndex = ui->Text_Interaction->currentRow();

    // Récupérer le contact actuellement sélectionné
    const Contact &selectedContact = gc.getContact(ui->Text_Contact->currentRow());

    // Récupérer la liste des interactions du contact (const reference)
    const std::list<Interaction> &interactions = selectedContact.getInteraction();

    // Vérifier si un élément est sélectionné
    if (selectedIndex >= 0 && selectedIndex < static_cast<int>(interactions.size())) {
        // Copier la liste actuelle des interactions
        std::list<Interaction> modifiedInteractions = interactions;

        // Trouver l'itérateur de l'interaction à supprimer
        auto it = std::next(modifiedInteractions.begin(), selectedIndex);

        // Supprimer l'interaction dans la BD
        DatabaseDelete databaseDelete("base.sqlite");
        int interactionID = databaseDelete.getInteractionIdByContent(QString::fromStdString(it->getContenu()));
        qDebug() << interactionID << "id interaction";

        // Vérifier si la base de données est ouverte
        databaseDelete.openDatabase();
        // Supprimer l'interaction et les todos associés
        databaseDelete.deleteTodoAndInteraction(interactionID);
        databaseDelete.closeDatabase();


        // Supprimer l'interaction de la liste copiée
        modifiedInteractions.erase(it);

        // Mettre à jour la liste des interactions dans le contact
        const_cast<Contact&>(selectedContact).updateInteractionList(modifiedInteractions);

        // Mettre à jour l'affichage des interactions
        displayInteractions(selectedContact);

        // Mettez à jour l'horodatage pour refléter la modification récente
        updateLastModificationLabel(std::chrono::system_clock::now());
        ui->Text_Todo->clear();
    } else {
        // Afficher un message si aucune interaction n'est sélectionnée
        QMessageBox::information(this, "Aucune interaction sélectionnée", "Veuillez sélectionner une interaction avant de la supprimer.");
    }
}




/**
 * @brief Modifie une interaction
 */
void MainWindow::modifierInteractionDepuisListe() {
    // Récupérer l'index de l'élément sélectionné dans Text_Interaction
    int selectedIndex = ui->Text_Interaction->currentRow();

    // Vérifier si une interaction est sélectionnée
    if (selectedIndex < 0) {
        QMessageBox::information(this, "Aucune interaction sélectionnée", "Veuillez sélectionner une interaction avant de la modifier.");
        return;
    }

    // Récupérer le contact actuellement sélectionné
    int selectedContactIndex = ui->Text_Contact->currentRow();
    if (selectedContactIndex < 0) {
        // Aucun contact sélectionné, affichez un message d'erreur si nécessaire
        return;
    }



    // Ouvrir InteractionDialogue avec les détails de l'interaction sélectionnée pour modification
    InteractionDialogue dialog(this);

    dialog.setContenu(QString::fromStdString(gc.getContact(selectedContactIndex).getInteractionAt(selectedIndex).getContenu()));

    // Convertir day_point à QDate
    std::chrono::time_point<std::chrono::system_clock> tp = gc.getContact(selectedContactIndex).getInteractionAt(selectedIndex).getDate();
    int result = dialog.exec();

    if (result == QDialog::Accepted) {

        // Convertir la QString de la date en QDate
        QDate selectedDate = QDate::fromString(dialog.getDate(), "yyyy-MM-dd");

        // Extraire les composants jour, mois, année
        int day = selectedDate.day();
        int month = selectedDate.month();
        int year = selectedDate.year();


        gc.getContact(selectedContactIndex).getInteractionAt(selectedIndex).setContenu(dialog.getContenu().toStdString());
        gc.getContact(selectedContactIndex).getInteractionAt(selectedIndex).setDate(day, month, year);
        displayInteractions(gc.getContact(selectedContactIndex));
    }

}


/**
 * @brief mise à jour de l'ui
 * @param contacts
 */
void MainWindow::updateContactListUI(const QList<Contact>& contacts) {
    // Effacez la liste actuelle
    ui->Text_Contact->clear();

    // Ajoutez chaque contact trié à la liste
    for (const Contact& contact : contacts) {
        // Construisez la chaîne avec plus d'informations
        QString contactString = QString::fromStdString(
            contact.getPrenom() + " " + contact.getNom() + " " + contact.getEntreprise() +" "+
            " " + contact.getMail() + " " +
            " " + contact.getTelephone()
            );

        // Ajoutez la chaîne à la liste
        ui->Text_Contact->addItem(contactString);
    }

    // Mettez à jour l'affichage des détails du contact sélectionné (si un contact est sélectionné)
    QListWidgetItem* selectedItem = ui->Text_Contact->currentItem();
    if (selectedItem) {
        onContactItemSelected(selectedItem);
    }
}

void MainWindow::afficherTodoDialogue()
{
    // Vérifier s'il y a une interaction sélectionnée dans Text_Interaction
    if (QListWidgetItem *selectedItem = ui->Text_Interaction->currentItem()) {

        // Utilisez la variable membre todoDialogue
        todoDialogue->show();

    } else {
        // Afficher un message ou prendre toute autre action appropriée si aucune interaction n'est sélectionnée
        QMessageBox::information(this, "Aucune interaction sélectionné", "Veuillez sélectionner une interaction avant d'ajouter un ToDo.");
    }
}

/**
 * @brief affiche la qdialog afin de créer un todo
 * @param info1
 */
void MainWindow::infoFromTodoDialogue(const QString& info1) {
    QString dateString = todoDialogue->getDate();

    // Parse the date string using QDate
    QDate selectedDate = QDate::fromString(dateString, "yyyy-MM-dd");

    // Récupérer l'index du Contact actuellement sélectionné
    int selectedContactIndex = ui->Text_Contact->currentRow();

    // Vérifier si l'index est valide
    if (selectedContactIndex >= 0 && selectedContactIndex < static_cast<int>(gc.getContactsListe().size())) {
        // Récupérer le Contact actuellement sélectionné
        Contact& selectedContact = gc.getContact(selectedContactIndex);
        // Récupérer l'index de l'Interaction actuellement sélectionnée
        int selectedInteractionIndex = ui->Text_Interaction->row(ui->Text_Interaction->currentItem());

        // Vérifier si l'index est valide
        if (selectedInteractionIndex >= 0 && selectedInteractionIndex < static_cast<int>(selectedContact.getInteraction().size())) {
            // Récupérer l'Interaction actuellement sélectionnée
            Interaction selectedInteraction = selectedContact.getInteractionAt(selectedInteractionIndex);

            ITodo* newTodo = new ITodo(info1.toStdString(), selectedDate.day(), selectedDate.month(), selectedDate.year());

            AssociationInteractionTodo as(&selectedInteraction, newTodo);

            //Ajouter l'interaction a la BD
            DatabaseInsert databaseInsert("base.sqlite");
            int interaction1Id = databaseInsert.getInteractionIdByContent(QString::fromStdString(selectedInteraction.getContenu()));
            databaseInsert.insertTodo(*newTodo, interaction1Id);



            // Ajouter l'AssociationInteractionTodo à l'Interaction
            selectedContact.addAssociation(as);

            // Actualiser l'affichage des Todos
            displayTodos(selectedInteraction);
        } else {
            qDebug() << "Erreur : Indice d'accès à l'Interaction invalide.";
        }
    } else {
        qDebug() << "Erreur : Indice d'accès au Contact invalide.";
    }
}






/**
 * @brief affiche la liste de todos de l'interaction
 */
void MainWindow::displayTodos(const Interaction &interaction) {
    ui->Text_Todo->clear();

    // Récupérer l'index du Contact actuellement sélectionné
    int selectedContactIndex = ui->Text_Contact->currentRow();

    // Vérifier si l'index est valide
    if (selectedContactIndex >= 0 && selectedContactIndex < static_cast<int>(gc.getContactsListe().size())) {
        // Récupérer le Contact actuellement sélectionné
        Contact &selectedContact = gc.getContact(selectedContactIndex);

        // Récupérer la liste des Associations entre Interaction et Todo depuis le Contact
        std::list<AssociationInteractionTodo> associations = selectedContact.getAssociations();

        // Parcourir la liste des associations
        for (const auto &association : associations) {
            ITodo* todo = association.getTodo();

            // Vérifier si le pointeur est valide
            if (todo) {
                QString todoString = QString::fromStdString(todo->Affichage());
                new QListWidgetItem(todoString, ui->Text_Todo);
            } else {
                qDebug() << "Erreur : pointeur de Todo non valide.";
            }
        }
    } else {
        qDebug() << "Erreur : Indice d'accès au Contact invalide.";
    }
}



/**
 * @brief Obtient la liste de todos associés à l'item interaction
 * @param item
 */
void MainWindow::onInteractionClicked(QListWidgetItem *item) {


    if (item) {
        // Récupérer l'index du Contact actuellement sélectionné
        int selectedContactIndex = ui->Text_Contact->currentRow();

        // Vérifier si l'index est valide
        if (selectedContactIndex >= 0 && selectedContactIndex < static_cast<int>(gc.getContactsListe().size())) {
            Contact &selectedContact = gc.getContact(selectedContactIndex);

            // Utilisez item directement pour obtenir l'index sans appeler currentRow()
            int selectedIndex = ui->Text_Interaction->row(item);

            // Assurez-vous que selectedIndex est dans la plage valide
            if (selectedIndex >= 0 && selectedIndex < static_cast<int>(selectedContact.getInteraction().size())) {
                Interaction selectedInteraction = selectedContact.getInteractionAt(selectedIndex);

                displayTodos(selectedInteraction);
            } else {
                qDebug() << "Error: Invalid index for interaction.";
            }
        } else {
            qDebug() << "Error: Invalid access index to the contact.";
        }
    }
}


/**
 * @brief permet de supprimer le todo séléctionner
 */
void MainWindow::onBt_SupprimerTodo() {
    // Récupérer l'index du Contact actuellement sélectionné
    int selectedContactIndex = ui->Text_Contact->currentRow();

    // Vérifier si l'index est valide
    if (selectedContactIndex >= 0 && selectedContactIndex < static_cast<int>(gc.getContactsListe().size())) {
        Contact &selectedContact = gc.getContact(ui->Text_Contact->currentRow());

        // Récupérer l'index de l'Interaction actuellement sélectionnée
        int selectedInteractionIndex = ui->Text_Interaction->currentRow();

        // Vérifier si l'index de l'interaction est valide
        if (selectedInteractionIndex >= 0 && selectedInteractionIndex < static_cast<int>(selectedContact.getInteraction().size())) {
            Interaction &selectedInteraction = selectedContact.getInteractionAt(selectedInteractionIndex);

            // Récupérer le todo actuellement sélectionné
            int selectedTodoIndex = ui->Text_Todo->currentRow();

            // Vérifier si l'index du todo est valide
            if (selectedTodoIndex >= 0 && selectedTodoIndex < static_cast<int>(selectedContact.getAssociations().size())) {

                std::list<AssociationInteractionTodo> associations = selectedContact.getAssociationsByInteraction(gc.getContact(ui->Text_Contact->currentRow()).getInteractionAt(0));

                // Vérifier si l'index du todo est valide
                if (selectedTodoIndex >= 0 && selectedTodoIndex < static_cast<int>(associations.size())) {
                    try {
                        auto iter = std::next(associations.begin(), selectedTodoIndex);

                        // Supprimer l'élément de la liste
                        associations.erase(iter);
                        iter = associations.begin();

                        // Maintenant, l'élément à l'index selectedTodoIndex a été supprimé de la liste
                    } catch (const std::exception& e) {
                        // Gérer l'exception
                        qDebug() << "Erreur lors de la suppression de l'élément : " << e.what();
                    }

                    // Mettre à jour l'affichage des todos
                    displayTodos(selectedInteraction);
                } else {
                    // Gérer le cas où l'index n'est pas valide
                    QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner un todo avant de supprimer l'association.");
                }
            } else {
                QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner un todo avant de supprimer l'association.");
            }
        } else {
            qDebug() << "Erreur : Index invalide pour l'interaction.";
        }
    } else {
        qDebug() << "Erreur : Accès invalide à l'index du contact.";
    }
}


/**
 * @brief permet d'afficher la qdialog
 */
void MainWindow::onBt_Historique() {
    int selectedContactIndex = ui->Text_Contact->currentRow();
    if (selectedContactIndex >= 0 && selectedContactIndex < static_cast<int>(gc.getContactsListe().size())) {
        const Contact& selectedContact = gc.getContact(selectedContactIndex);
        const std::list<Modification>& history = selectedContact.getHistory();

        // Créer une instance de la fenêtre d'historique

        historiqueDialogue->setHistory(history);

        // Afficher la fenêtre d'historique
        historiqueDialogue->exec();
    } else {
        qDebug() << "Erreur : Accès invalide à l'index du contact.";
    }
}

/**
 * @brief Permet de créer un export json
 */
void MainWindow::exportToJson() {
    qDebug() << "Export en cours...";

    // Obtenez le répertoire courant de l'application
    QString currentPath = QDir::currentPath();
    qDebug() << currentPath.toStdString();

    // Créez le chemin complet du fichier en concaténant le répertoire courant et le nom du fichier
    QString filePath = currentPath + "/export.json";
    // Créer un objet JSON pour représenter la gestion de contacts
    QJsonObject gestionContactsObject;

    // Ajouter des propriétés spécifiques de votre gestion de contacts
    // (par exemple, les contacts et leurs propriétés)
    QJsonArray contactsArray;
    for (const auto &contact : gc.getContactsListe()) {
        QJsonObject contactObject;
        contactObject["nom"] = QString::fromStdString(contact.getNom());
        contactObject["prenom"] = QString::fromStdString(contact.getPrenom());
        contactObject["entreprise"] = QString::fromStdString(contact.getEntreprise());
        contactObject["photo"] = QString::fromStdString(contact.getPhoto());
        contactObject["mail"] = QString::fromStdString(contact.getMail());
        contactObject["numero"] = QString::fromStdString(contact.getTelephone());
        // Ajoutez d'autres propriétés du contact

        // Ajouter les interactions du contact
        QJsonArray interactionsArray;
        for (const auto &interaction : contact.getInteraction()) {
            QJsonObject interactionObject;
            interactionObject["description"] = QString::fromStdString(interaction.Affichage());
            // Ajoutez d'autres propriétés de l'interaction

            // Ajouter les todos de l'interaction
            QJsonArray todosArray;
            for (const auto &todo : contact.getAssociations()) {
                QJsonObject todoObject;
                todoObject["description"] = QString::fromStdString(todo.getTodo()->Affichage());
                // Ajoutez d'autres propriétés du todo
                todosArray.append(todoObject);
            }
            interactionObject["todos"] = todosArray;

            interactionsArray.append(interactionObject);
        }
        contactObject["interactions"] = interactionsArray;

        contactsArray.append(contactObject);
    }
    gestionContactsObject["contacts"] = contactsArray;

    // Créer un document JSON
    QJsonDocument jsonDocument(gestionContactsObject);

    // Enregistrer le document JSON dans un fichier
    QFile jsonFile(filePath);
    if (jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        jsonFile.write(jsonDocument.toJson());
        jsonFile.close();
    } else {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier pour l'export JSON.";
    }
}

