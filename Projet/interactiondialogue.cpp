/**
 * @file interactiondialogue.cpp
 */

#include "interactiondialogue.h"
#include "qdebug.h"
#include "ui_interactiondialogue.h"
#include <QMessageBox>

/**
 * @brief Constructeur de la classe InteractionDialogue.
 * @param parent Le widget parent.
 */
InteractionDialogue::InteractionDialogue(QWidget *parent)
    : QDialog(parent), ui(new Ui::InteractionDialogue) {
    // Initialiser l'interface utilisateur de la boîte de dialogue
    ui->setupUi(this);

    // Définir le bouton par défaut (celui qui est activé en appuyant sur la touche Entrée)
    ui->Bt_Contenu_Valider->setDefault(true);

    // Connecter le signal clicked du bouton Valider à la slot correspondante
    connect(ui->Bt_Contenu_Valider, SIGNAL(clicked()), this, SLOT(onBtContenuValiderClicked()));

    // Connecter le signal clicked du bouton Annuler à la slot correspondante
    connect(ui->Bt_Contenu_Annuler, SIGNAL(clicked()), this, SLOT(onAnnulerClicked()));
}

/**
 * @brief Destructeur de la classe InteractionDialogue.
 */
InteractionDialogue::~InteractionDialogue() {
    delete ui;
}

/**
 * @brief Obtenir le contenu saisi dans la boîte de dialogue.
 * @return Le contenu saisi.
 */
QString InteractionDialogue::getContenu() const {
    return ui->Text_Interaction->text();
}

/**
 * @brief Obtenir la date saisi dans la boîte de dialogue.
 * @return La date saisi au format "yyyy-MM-dd".
 */
QString InteractionDialogue::getDate() const {
    QDate selectedDate = ui->Text_Date->selectedDate();
    QString dateString = selectedDate.toString("yyyy-MM-dd");  // Format de date souhaité
    return dateString;
}

/**
 * @brief Slot appelé lors du clic sur le bouton Valider.
 */
void InteractionDialogue::onBtContenuValiderClicked() {
    QString contenu = getContenu();
    QString date = getDate();

    // Vérifier que les deux champs sont remplis
    if (contenu.isEmpty() || date.isEmpty()) {
        // Afficher un message ou prendre une autre action appropriée en cas de champ non rempli
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs avant de valider.");
        return;  // Arrêter la fonction si les champs ne sont pas remplis
    }

    QString res = contenu;
    emit informationsValidees(res);
    close();
}


/**
 * @brief Définir le contenu affiché dans la boîte de dialogue.
 * @param contenu Le contenu à afficher.
 */
void InteractionDialogue::setContenu(const QString &contenu) {
    ui->Text_Interaction->setText(contenu);
}

/**
 * @brief Slot appelé lors du clic sur le bouton Annuler.
 */
void InteractionDialogue::onAnnulerClicked() {
    reject();  // Ferme la boîte de dialogue avec un résultat de rejet
}
