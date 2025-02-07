/**
 *@file interactiondialogue.h
 *
*/

#ifndef INTERACTIONDIALOGUE_H
#define INTERACTIONDIALOGUE_H


#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class InteractionDialogue; }
QT_END_NAMESPACE

class InteractionDialogue : public QDialog {
    Q_OBJECT

public:
    explicit InteractionDialogue(QWidget *parent = nullptr);
    ~InteractionDialogue();

    QString getContenu() const;
    QString getDate() const;
    void setContenu(const QString &contenu);
    void setDate(QDate q);

private:
    Ui::InteractionDialogue *ui;

public slots:
    void onBtContenuValiderClicked();
    void onAnnulerClicked();


signals:
    void informationsValidees(const QString& info1);

};
#endif // INTERACTIONDIALOGUE_H
