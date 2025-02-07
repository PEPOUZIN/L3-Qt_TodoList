/********************************************************************************
** Form generated from reading UI file 'historiquedialogue.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORIQUEDIALOGUE_H
#define UI_HISTORIQUEDIALOGUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_HistoriqueDialogue
{
public:

    void setupUi(QDialog *HistoriqueDialogue)
    {
        if (HistoriqueDialogue->objectName().isEmpty())
            HistoriqueDialogue->setObjectName("HistoriqueDialogue");
        HistoriqueDialogue->resize(400, 300);

        retranslateUi(HistoriqueDialogue);

        QMetaObject::connectSlotsByName(HistoriqueDialogue);
    } // setupUi

    void retranslateUi(QDialog *HistoriqueDialogue)
    {
        HistoriqueDialogue->setWindowTitle(QCoreApplication::translate("HistoriqueDialogue", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistoriqueDialogue: public Ui_HistoriqueDialogue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORIQUEDIALOGUE_H
