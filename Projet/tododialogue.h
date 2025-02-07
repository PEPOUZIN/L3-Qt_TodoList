/**
 *@file tododialogue.h
 *
*/

#ifndef TODODIALOGUE_H
#define TODODIALOGUE_H

#include <QDialog>

namespace Ui {
class tododialogue;
}

class TodoDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit TodoDialogue(QWidget *parent = nullptr);
    ~TodoDialogue();
    QString getContenu() const;
    QString getDate() const;


private:
    Ui::tododialogue *ui;
public slots:
    void onBtContenuValiderClicked();

signals:
    void informationsValidees(const QString& info1);

};

#endif // TODODIALOGUE_H
