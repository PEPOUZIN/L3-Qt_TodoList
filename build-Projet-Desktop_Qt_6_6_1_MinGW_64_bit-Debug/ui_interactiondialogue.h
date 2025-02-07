/********************************************************************************
** Form generated from reading UI file 'interactiondialogue.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERACTIONDIALOGUE_H
#define UI_INTERACTIONDIALOGUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InteractionDialogue
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *Text_Interaction;
    QLabel *label_2;
    QCalendarWidget *Text_Date;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *Bt_Contenu_Valider;
    QPushButton *Bt_Contenu_Annuler;

    void setupUi(QDialog *InteractionDialogue)
    {
        if (InteractionDialogue->objectName().isEmpty())
            InteractionDialogue->setObjectName("InteractionDialogue");
        InteractionDialogue->resize(400, 306);
        verticalLayoutWidget = new QWidget(InteractionDialogue);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(-1, -1, 401, 271));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("Carlito")});
        font.setBold(true);
        label->setFont(font);

        verticalLayout->addWidget(label);

        Text_Interaction = new QLineEdit(verticalLayoutWidget);
        Text_Interaction->setObjectName("Text_Interaction");

        verticalLayout->addWidget(Text_Interaction);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);
        label_2->setFrameShadow(QFrame::Plain);

        verticalLayout->addWidget(label_2);

        Text_Date = new QCalendarWidget(verticalLayoutWidget);
        Text_Date->setObjectName("Text_Date");

        verticalLayout->addWidget(Text_Date);

        horizontalLayoutWidget = new QWidget(InteractionDialogue);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 270, 401, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Bt_Contenu_Valider = new QPushButton(horizontalLayoutWidget);
        Bt_Contenu_Valider->setObjectName("Bt_Contenu_Valider");

        horizontalLayout->addWidget(Bt_Contenu_Valider);

        Bt_Contenu_Annuler = new QPushButton(horizontalLayoutWidget);
        Bt_Contenu_Annuler->setObjectName("Bt_Contenu_Annuler");

        horizontalLayout->addWidget(Bt_Contenu_Annuler);


        retranslateUi(InteractionDialogue);

        QMetaObject::connectSlotsByName(InteractionDialogue);
    } // setupUi

    void retranslateUi(QDialog *InteractionDialogue)
    {
        InteractionDialogue->setWindowTitle(QCoreApplication::translate("InteractionDialogue", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("InteractionDialogue", "Entrez un Contenu :", nullptr));
        label_2->setText(QCoreApplication::translate("InteractionDialogue", "Choisir une Date :", nullptr));
        Bt_Contenu_Valider->setText(QCoreApplication::translate("InteractionDialogue", "Valider", nullptr));
        Bt_Contenu_Annuler->setText(QCoreApplication::translate("InteractionDialogue", "Annuler", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InteractionDialogue: public Ui_InteractionDialogue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERACTIONDIALOGUE_H
