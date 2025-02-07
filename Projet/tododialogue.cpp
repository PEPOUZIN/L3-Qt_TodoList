/**
 * @file tododialogue.cpp
 */

#include "tododialogue.h"
#include "qdebug.h"
#include "ui_tododialogue.h"

/**
 * @brief Constructeur de la classe TodoDialogue.
 * @param parent Le widget parent (par défaut nullptr).
 */
TodoDialogue::TodoDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tododialogue)
{
    ui->setupUi(this);

    // Connecte le signal clicked du bouton Bt_Contenu_Valider à la fonction onBtContenuValiderClicked
    connect(ui->Bt_Contenu_Valider, SIGNAL(clicked()), this, SLOT(onBtContenuValiderClicked()));
}

/**
 * @brief Destructeur de la classe TodoDialogue.
 */
TodoDialogue::~TodoDialogue()
{
    delete ui;
}

/**
 * @brief Obtient le contenu saisi dans le champ Text_todo.
 * @return Le contenu saisi.
 */
QString TodoDialogue::getContenu() const {
    return ui->Text_todo->text();
}

/**
 * @brief Obtient la date sélectionnée dans le champ Text_Date.
 * @return La date sélectionnée sous forme de chaîne de caractères au format "yyyy-MM-dd".
 */
QString TodoDialogue::getDate() const {
    QDate selectedDate = ui->Text_Date->selectedDate();
    QString dateString = selectedDate.toString("yyyy-MM-dd");  // Format de date souhaité
    return dateString;
}

/**
 * @brief Fonction déclenchée lors du clic sur le bouton Bt_Contenu_Valider.
 * Émet le signal informationsValidees avec le contenu et la date saisis, puis ferme la fenêtre de dialogue.
 */
void TodoDialogue::onBtContenuValiderClicked() {
    QString contenu = getContenu();
    QString date = getDate();
    QString res = contenu;
    emit informationsValidees(res);

    // Ferme la fenêtre de dialogue
    close();
}
