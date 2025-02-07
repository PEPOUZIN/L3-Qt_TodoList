/********************************************************************************
** Form generated from reading UI file 'tododialogue.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TODODIALOGUE_H
#define UI_TODODIALOGUE_H

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

class Ui_tododialogue
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *Text_todo;
    QLabel *label_2;
    QCalendarWidget *Text_Date;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *Bt_Contenu_Valider;
    QPushButton *Bt_Contenu_Annuler;

    void setupUi(QDialog *tododialogue)
    {
        if (tododialogue->objectName().isEmpty())
            tododialogue->setObjectName("tododialogue");
        tododialogue->resize(400, 300);
        verticalLayoutWidget = new QWidget(tododialogue);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 401, 261));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setBold(true);
        label->setFont(font);
        label->setScaledContents(false);

        verticalLayout->addWidget(label);

        Text_todo = new QLineEdit(verticalLayoutWidget);
        Text_todo->setObjectName("Text_todo");

        verticalLayout->addWidget(Text_todo);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        Text_Date = new QCalendarWidget(verticalLayoutWidget);
        Text_Date->setObjectName("Text_Date");

        verticalLayout->addWidget(Text_Date);

        horizontalLayoutWidget = new QWidget(tododialogue);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 270, 401, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Bt_Contenu_Valider = new QPushButton(horizontalLayoutWidget);
        Bt_Contenu_Valider->setObjectName("Bt_Contenu_Valider");
        Bt_Contenu_Valider->setFont(font);

        horizontalLayout->addWidget(Bt_Contenu_Valider);

        Bt_Contenu_Annuler = new QPushButton(horizontalLayoutWidget);
        Bt_Contenu_Annuler->setObjectName("Bt_Contenu_Annuler");
        Bt_Contenu_Annuler->setFont(font);

        horizontalLayout->addWidget(Bt_Contenu_Annuler);


        retranslateUi(tododialogue);

        QMetaObject::connectSlotsByName(tododialogue);
    } // setupUi

    void retranslateUi(QDialog *tododialogue)
    {
        tododialogue->setWindowTitle(QCoreApplication::translate("tododialogue", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("tododialogue", "Entrer un contenu", nullptr));
        label_2->setText(QCoreApplication::translate("tododialogue", "Choisir une date", nullptr));
        Bt_Contenu_Valider->setText(QCoreApplication::translate("tododialogue", "Valider", nullptr));
        Bt_Contenu_Annuler->setText(QCoreApplication::translate("tododialogue", "Annuler", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tododialogue: public Ui_tododialogue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TODODIALOGUE_H
