/**
 * @file historiquedialogue.cpp
 * @brief Implémentation de la classe HistoriqueDialogue.
 */

#include "historiquedialogue.h"
#include <QBoxLayout>

/**
 * @brief Constructeur de la classe HistoriqueDialogue.
 * @param parent Le widget parent.
 */
HistoriqueDialogue::HistoriqueDialogue(QWidget *parent)
    : QDialog(parent) {
    // Créer un widget de liste pour afficher l'historique
    historyListWidget = new QListWidget(this);

    // Créer la mise en page
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(historyListWidget);

    // Définir la mise en page de la fenêtre
    setLayout(layout);

    // Définir le titre de la fenêtre
    setWindowTitle("Historique des Modifications");
}

/**
 * @brief Définit l'historique à afficher dans la fenêtre.
 * @param history La liste des modifications à afficher.
 */
void HistoriqueDialogue::setHistory(const std::list<Modification>& history) {
    // Effacer le contenu actuel de la liste
    historyListWidget->clear();

    // Parcourir l'historique et ajouter chaque élément à la liste
    for (const Modification& modification : history) {
        QString modificationText = QString::fromStdString(modification.details) +
                                   " (" + modification.timestamp.toString("yyyy-MM-dd hh:mm:ss") + ")";
        historyListWidget->addItem(modificationText);
    }
}
