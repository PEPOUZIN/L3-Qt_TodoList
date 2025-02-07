/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radio_Nom;
    QLineEdit *Line_Nom;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radio_Prenom;
    QLineEdit *Line_Prenom;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *radio_Entreprise;
    QLineEdit *Line_Entreprise;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radio_Mail;
    QLineEdit *Line_Mail;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *Line_Numero;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *Bt_Modifier_Contact;
    QPushButton *Bt_Valider_Contact;
    QPushButton *Bt_Supprimer_Contact;
    QListWidget *Text_Contact;
    QListWidget *Text_Interaction;
    QListWidget *Text_Todo;
    QWidget *horizontalLayoutWidget_8;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *Bt_Valider_Interaction;
    QWidget *horizontalLayoutWidget_9;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *Bt_Supprimer_Interaction;
    QWidget *horizontalLayoutWidget_10;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *Bt_Ajouter_Todo;
    QPushButton *Bt_Supprimer_Todo;
    QLineEdit *line_Recherche;
    QComboBox *comboBox;
    QLabel *Label_Photo;
    QPushButton *menuHistorique;
    QLabel *label_Nombre;
    QLabel *Nombre;
    QPushButton *exportJSON;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(798, 708);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(-1, -1, 401, 261));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        radio_Nom = new QRadioButton(verticalLayoutWidget);
        radio_Nom->setObjectName("radio_Nom");

        horizontalLayout->addWidget(radio_Nom);

        Line_Nom = new QLineEdit(verticalLayoutWidget);
        Line_Nom->setObjectName("Line_Nom");

        horizontalLayout->addWidget(Line_Nom);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        radio_Prenom = new QRadioButton(verticalLayoutWidget);
        radio_Prenom->setObjectName("radio_Prenom");

        horizontalLayout_3->addWidget(radio_Prenom);

        Line_Prenom = new QLineEdit(verticalLayoutWidget);
        Line_Prenom->setObjectName("Line_Prenom");

        horizontalLayout_3->addWidget(Line_Prenom);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        radio_Entreprise = new QRadioButton(verticalLayoutWidget);
        radio_Entreprise->setObjectName("radio_Entreprise");

        horizontalLayout_6->addWidget(radio_Entreprise);

        Line_Entreprise = new QLineEdit(verticalLayoutWidget);
        Line_Entreprise->setObjectName("Line_Entreprise");

        horizontalLayout_6->addWidget(Line_Entreprise);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        radio_Mail = new QRadioButton(verticalLayoutWidget);
        radio_Mail->setObjectName("radio_Mail");

        horizontalLayout_5->addWidget(radio_Mail);

        Line_Mail = new QLineEdit(verticalLayoutWidget);
        Line_Mail->setObjectName("Line_Mail");

        horizontalLayout_5->addWidget(Line_Mail);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        Line_Numero = new QLineEdit(verticalLayoutWidget);
        Line_Numero->setObjectName("Line_Numero");

        horizontalLayout_4->addWidget(Line_Numero);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        Bt_Modifier_Contact = new QPushButton(verticalLayoutWidget);
        Bt_Modifier_Contact->setObjectName("Bt_Modifier_Contact");

        horizontalLayout_8->addWidget(Bt_Modifier_Contact);

        Bt_Valider_Contact = new QPushButton(verticalLayoutWidget);
        Bt_Valider_Contact->setObjectName("Bt_Valider_Contact");

        horizontalLayout_8->addWidget(Bt_Valider_Contact);

        Bt_Supprimer_Contact = new QPushButton(verticalLayoutWidget);
        Bt_Supprimer_Contact->setObjectName("Bt_Supprimer_Contact");

        horizontalLayout_8->addWidget(Bt_Supprimer_Contact);


        verticalLayout->addLayout(horizontalLayout_8);

        Text_Contact = new QListWidget(centralwidget);
        Text_Contact->setObjectName("Text_Contact");
        Text_Contact->setGeometry(QRect(10, 330, 391, 241));
        Text_Interaction = new QListWidget(centralwidget);
        Text_Interaction->setObjectName("Text_Interaction");
        Text_Interaction->setGeometry(QRect(410, 270, 381, 131));
        Text_Todo = new QListWidget(centralwidget);
        Text_Todo->setObjectName("Text_Todo");
        Text_Todo->setGeometry(QRect(410, 440, 381, 131));
        horizontalLayoutWidget_8 = new QWidget(centralwidget);
        horizontalLayoutWidget_8->setObjectName("horizontalLayoutWidget_8");
        horizontalLayoutWidget_8->setGeometry(QRect(20, 580, 381, 41));
        horizontalLayout_11 = new QHBoxLayout(horizontalLayoutWidget_8);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        Bt_Valider_Interaction = new QPushButton(horizontalLayoutWidget_8);
        Bt_Valider_Interaction->setObjectName("Bt_Valider_Interaction");

        horizontalLayout_11->addWidget(Bt_Valider_Interaction);

        horizontalLayoutWidget_9 = new QWidget(centralwidget);
        horizontalLayoutWidget_9->setObjectName("horizontalLayoutWidget_9");
        horizontalLayoutWidget_9->setGeometry(QRect(410, 400, 381, 41));
        horizontalLayout_12 = new QHBoxLayout(horizontalLayoutWidget_9);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        Bt_Supprimer_Interaction = new QPushButton(horizontalLayoutWidget_9);
        Bt_Supprimer_Interaction->setObjectName("Bt_Supprimer_Interaction");

        horizontalLayout_12->addWidget(Bt_Supprimer_Interaction);

        horizontalLayoutWidget_10 = new QWidget(centralwidget);
        horizontalLayoutWidget_10->setObjectName("horizontalLayoutWidget_10");
        horizontalLayoutWidget_10->setGeometry(QRect(410, 570, 381, 51));
        horizontalLayout_13 = new QHBoxLayout(horizontalLayoutWidget_10);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        Bt_Ajouter_Todo = new QPushButton(horizontalLayoutWidget_10);
        Bt_Ajouter_Todo->setObjectName("Bt_Ajouter_Todo");

        horizontalLayout_13->addWidget(Bt_Ajouter_Todo);

        Bt_Supprimer_Todo = new QPushButton(horizontalLayoutWidget_10);
        Bt_Supprimer_Todo->setObjectName("Bt_Supprimer_Todo");

        horizontalLayout_13->addWidget(Bt_Supprimer_Todo);

        line_Recherche = new QLineEdit(centralwidget);
        line_Recherche->setObjectName("line_Recherche");
        line_Recherche->setGeometry(QRect(10, 300, 391, 24));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(10, 270, 391, 24));
        Label_Photo = new QLabel(centralwidget);
        Label_Photo->setObjectName("Label_Photo");
        Label_Photo->setGeometry(QRect(510, 10, 171, 191));
        menuHistorique = new QPushButton(centralwidget);
        menuHistorique->setObjectName("menuHistorique");
        menuHistorique->setGeometry(QRect(410, 240, 381, 26));
        label_Nombre = new QLabel(centralwidget);
        label_Nombre->setObjectName("label_Nombre");
        label_Nombre->setGeometry(QRect(410, 220, 151, 18));
        Nombre = new QLabel(centralwidget);
        Nombre->setObjectName("Nombre");
        Nombre->setGeometry(QRect(560, 220, 66, 18));
        exportJSON = new QPushButton(centralwidget);
        exportJSON->setObjectName("exportJSON");
        exportJSON->setGeometry(QRect(19, 630, 201, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 798, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        radio_Nom->setText(QString());
        Line_Nom->setText(QString());
        radio_Prenom->setText(QString());
        Line_Prenom->setText(QString());
        radio_Entreprise->setText(QString());
        Line_Entreprise->setText(QString());
        radio_Mail->setText(QString());
        Line_Mail->setText(QString());
        Line_Numero->setText(QString());
        Bt_Modifier_Contact->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        Bt_Valider_Contact->setText(QCoreApplication::translate("MainWindow", "Valider", nullptr));
        Bt_Supprimer_Contact->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        Bt_Valider_Interaction->setText(QCoreApplication::translate("MainWindow", "Cr\303\251er Interaction", nullptr));
        Bt_Supprimer_Interaction->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        Bt_Ajouter_Todo->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        Bt_Supprimer_Todo->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        Label_Photo->setText(QString());
        menuHistorique->setText(QCoreApplication::translate("MainWindow", "Historique", nullptr));
        label_Nombre->setText(QCoreApplication::translate("MainWindow", "Nombre de Contacts:", nullptr));
        Nombre->setText(QString());
        exportJSON->setText(QCoreApplication::translate("MainWindow", "Export JSON", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
