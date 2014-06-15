/********************************************************************************
** Form generated from reading UI file 'capacitorbankplacement.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAPACITORBANKPLACEMENT_H
#define UI_CAPACITORBANKPLACEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CapacitorBankPlacement
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *bankplacementSID_lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *bankplacementUID_lineEdit;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_12;
    QLineEdit *name_lineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *bankplacementAlias_lineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *bankplacementCatType_comboBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *bankplacementBankType_comboBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QComboBox *bankplacementNLC_comboBox;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QComboBox *bankplacementBC_comboBox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QComboBox *bankplacementPC_comboBox;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QLineEdit *bankplacementNS_lineEdit;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QComboBox *bankplacementLDM_comboBox;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    QPlainTextEdit *bankplacementDescription_plainTextEdit;
    QDialogButtonBox *capacitorbankplacement_buttonBox;

    void setupUi(QDialog *CapacitorBankPlacement)
    {
        if (CapacitorBankPlacement->objectName().isEmpty())
            CapacitorBankPlacement->setObjectName(QStringLiteral("CapacitorBankPlacement"));
        CapacitorBankPlacement->resize(408, 559);
        verticalLayout = new QVBoxLayout(CapacitorBankPlacement);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(CapacitorBankPlacement);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        bankplacementSID_lineEdit = new QLineEdit(CapacitorBankPlacement);
        bankplacementSID_lineEdit->setObjectName(QStringLiteral("bankplacementSID_lineEdit"));

        horizontalLayout->addWidget(bankplacementSID_lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(CapacitorBankPlacement);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        bankplacementUID_lineEdit = new QLineEdit(CapacitorBankPlacement);
        bankplacementUID_lineEdit->setObjectName(QStringLiteral("bankplacementUID_lineEdit"));

        horizontalLayout_2->addWidget(bankplacementUID_lineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_12 = new QLabel(CapacitorBankPlacement);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_12->addWidget(label_12);

        name_lineEdit = new QLineEdit(CapacitorBankPlacement);
        name_lineEdit->setObjectName(QStringLiteral("name_lineEdit"));

        horizontalLayout_12->addWidget(name_lineEdit);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(CapacitorBankPlacement);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        bankplacementAlias_lineEdit = new QLineEdit(CapacitorBankPlacement);
        bankplacementAlias_lineEdit->setObjectName(QStringLiteral("bankplacementAlias_lineEdit"));

        horizontalLayout_3->addWidget(bankplacementAlias_lineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(CapacitorBankPlacement);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        bankplacementCatType_comboBox = new QComboBox(CapacitorBankPlacement);
        bankplacementCatType_comboBox->setObjectName(QStringLiteral("bankplacementCatType_comboBox"));

        horizontalLayout_4->addWidget(bankplacementCatType_comboBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(CapacitorBankPlacement);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        bankplacementBankType_comboBox = new QComboBox(CapacitorBankPlacement);
        bankplacementBankType_comboBox->setObjectName(QStringLiteral("bankplacementBankType_comboBox"));

        horizontalLayout_5->addWidget(bankplacementBankType_comboBox);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(CapacitorBankPlacement);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        bankplacementNLC_comboBox = new QComboBox(CapacitorBankPlacement);
        bankplacementNLC_comboBox->setObjectName(QStringLiteral("bankplacementNLC_comboBox"));

        horizontalLayout_6->addWidget(bankplacementNLC_comboBox);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(CapacitorBankPlacement);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        bankplacementBC_comboBox = new QComboBox(CapacitorBankPlacement);
        bankplacementBC_comboBox->setObjectName(QStringLiteral("bankplacementBC_comboBox"));

        horizontalLayout_7->addWidget(bankplacementBC_comboBox);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_8 = new QLabel(CapacitorBankPlacement);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_8->addWidget(label_8);

        bankplacementPC_comboBox = new QComboBox(CapacitorBankPlacement);
        bankplacementPC_comboBox->setObjectName(QStringLiteral("bankplacementPC_comboBox"));

        horizontalLayout_8->addWidget(bankplacementPC_comboBox);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_9 = new QLabel(CapacitorBankPlacement);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_9->addWidget(label_9);

        bankplacementNS_lineEdit = new QLineEdit(CapacitorBankPlacement);
        bankplacementNS_lineEdit->setObjectName(QStringLiteral("bankplacementNS_lineEdit"));

        horizontalLayout_9->addWidget(bankplacementNS_lineEdit);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_10 = new QLabel(CapacitorBankPlacement);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_10->addWidget(label_10);

        bankplacementLDM_comboBox = new QComboBox(CapacitorBankPlacement);
        bankplacementLDM_comboBox->setObjectName(QStringLiteral("bankplacementLDM_comboBox"));

        horizontalLayout_10->addWidget(bankplacementLDM_comboBox);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_11 = new QLabel(CapacitorBankPlacement);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_11->addWidget(label_11);


        verticalLayout->addLayout(horizontalLayout_11);

        bankplacementDescription_plainTextEdit = new QPlainTextEdit(CapacitorBankPlacement);
        bankplacementDescription_plainTextEdit->setObjectName(QStringLiteral("bankplacementDescription_plainTextEdit"));

        verticalLayout->addWidget(bankplacementDescription_plainTextEdit);

        capacitorbankplacement_buttonBox = new QDialogButtonBox(CapacitorBankPlacement);
        capacitorbankplacement_buttonBox->setObjectName(QStringLiteral("capacitorbankplacement_buttonBox"));
        capacitorbankplacement_buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(capacitorbankplacement_buttonBox);


        retranslateUi(CapacitorBankPlacement);

        QMetaObject::connectSlotsByName(CapacitorBankPlacement);
    } // setupUi

    void retranslateUi(QDialog *CapacitorBankPlacement)
    {
        CapacitorBankPlacement->setWindowTitle(QApplication::translate("CapacitorBankPlacement", "Dialog", 0));
        label_3->setText(QApplication::translate("CapacitorBankPlacement", "SystemID:", 0));
        label_2->setText(QApplication::translate("CapacitorBankPlacement", "ID:", 0));
        label_12->setText(QApplication::translate("CapacitorBankPlacement", "Name:", 0));
        label->setText(QApplication::translate("CapacitorBankPlacement", "Alias:", 0));
        label_4->setText(QApplication::translate("CapacitorBankPlacement", "Catalog Type:", 0));
        bankplacementCatType_comboBox->clear();
        bankplacementCatType_comboBox->insertItems(0, QStringList()
         << QApplication::translate("CapacitorBankPlacement", "CapBank -20 kV -500 kVAr", 0)
         << QApplication::translate("CapacitorBankPlacement", "CapBank -20 kV -250 kVAr", 0)
         << QApplication::translate("CapacitorBankPlacement", "CapBank -20 kV -1000 kVAr", 0)
         << QApplication::translate("CapacitorBankPlacement", "CapBank -20 kV -100 kVAr", 0)
         << QApplication::translate("CapacitorBankPlacement", "CapBank -20 kV -2500 kVAr", 0)
        );
        label_5->setText(QApplication::translate("CapacitorBankPlacement", "Bank Type: ", 0));
        bankplacementBankType_comboBox->clear();
        bankplacementBankType_comboBox->insertItems(0, QStringList()
         << QApplication::translate("CapacitorBankPlacement", "Shunt", 0)
         << QApplication::translate("CapacitorBankPlacement", "Serial", 0)
        );
        label_6->setText(QApplication::translate("CapacitorBankPlacement", "No Load Control: ", 0));
        bankplacementNLC_comboBox->clear();
        bankplacementNLC_comboBox->insertItems(0, QStringList()
         << QApplication::translate("CapacitorBankPlacement", "Yes", 0)
         << QApplication::translate("CapacitorBankPlacement", "No", 0)
        );
        label_7->setText(QApplication::translate("CapacitorBankPlacement", "Bank Control:", 0));
        bankplacementBC_comboBox->clear();
        bankplacementBC_comboBox->insertItems(0, QStringList()
         << QApplication::translate("CapacitorBankPlacement", "No control", 0)
         << QApplication::translate("CapacitorBankPlacement", "Volt/VAr control", 0)
         << QApplication::translate("CapacitorBankPlacement", "Voltage regulation", 0)
         << QApplication::translate("CapacitorBankPlacement", "Time switched control", 0)
        );
        label_8->setText(QApplication::translate("CapacitorBankPlacement", "Phase Code:", 0));
        bankplacementPC_comboBox->clear();
        bankplacementPC_comboBox->insertItems(0, QStringList()
         << QApplication::translate("CapacitorBankPlacement", "A", 0)
         << QApplication::translate("CapacitorBankPlacement", "B", 0)
         << QApplication::translate("CapacitorBankPlacement", "C", 0)
         << QApplication::translate("CapacitorBankPlacement", "AB", 0)
         << QApplication::translate("CapacitorBankPlacement", "AC", 0)
         << QApplication::translate("CapacitorBankPlacement", "BC", 0)
         << QApplication::translate("CapacitorBankPlacement", "ABC", 0)
        );
        label_9->setText(QApplication::translate("CapacitorBankPlacement", "Normal Section [1]:", 0));
        label_10->setText(QApplication::translate("CapacitorBankPlacement", "Load Demand Model:", 0));
        bankplacementLDM_comboBox->clear();
        bankplacementLDM_comboBox->insertItems(0, QStringList()
         << QApplication::translate("CapacitorBankPlacement", "Commercial", 0)
         << QApplication::translate("CapacitorBankPlacement", "Culture", 0)
         << QApplication::translate("CapacitorBankPlacement", "EDC", 0)
         << QApplication::translate("CapacitorBankPlacement", "Education", 0)
         << QApplication::translate("CapacitorBankPlacement", "EMB", 0)
         << QApplication::translate("CapacitorBankPlacement", "Goverment", 0)
         << QApplication::translate("CapacitorBankPlacement", "HLS", 0)
         << QApplication::translate("CapacitorBankPlacement", "Hospital", 0)
         << QApplication::translate("CapacitorBankPlacement", "IND", 0)
         << QApplication::translate("CapacitorBankPlacement", "Others", 0)
         << QApplication::translate("CapacitorBankPlacement", "R/C", 0)
         << QApplication::translate("CapacitorBankPlacement", "Recidential", 0)
         << QApplication::translate("CapacitorBankPlacement", "RES", 0)
         << QApplication::translate("CapacitorBankPlacement", "RLG", 0)
         << QApplication::translate("CapacitorBankPlacement", "Utility", 0)
         << QApplication::translate("CapacitorBankPlacement", "VIP", 0)
         << QApplication::translate("CapacitorBankPlacement", "AGR", 0)
         << QApplication::translate("CapacitorBankPlacement", "Undefined", 0)
         << QApplication::translate("CapacitorBankPlacement", "Generation", 0)
         << QApplication::translate("CapacitorBankPlacement", "Capacitor bank", 0)
        );
        label_11->setText(QApplication::translate("CapacitorBankPlacement", "Description:", 0));
    } // retranslateUi

};

namespace Ui {
    class CapacitorBankPlacement: public Ui_CapacitorBankPlacement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAPACITORBANKPLACEMENT_H
