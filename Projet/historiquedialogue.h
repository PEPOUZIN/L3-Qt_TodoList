/**
 *@file historiquedialogue.h
 *
*/

#ifndef HISTORIQUEDIALOG_H
#define HISTORIQUEDIALOG_H

#include <QDialog>
#include <QListWidget>
#include "contact.h" // Assurez-vous d'inclure le fichier de déclaration de votre classe Contact

class HistoriqueDialogue : public QDialog {
    Q_OBJECT

public:
    HistoriqueDialogue(QWidget *parent = nullptr);

    // Fonction pour définir l'historique à afficher
    void setHistory(const std::list<Modification>& history);

private:
    QListWidget *historyListWidget;
};

#endif // HISTORIQUEDIALOG_H
