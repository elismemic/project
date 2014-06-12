/********************************************************************************
** Form generated from reading UI file 'capacitor.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAPACITOR_H
#define UI_CAPACITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Capacitor
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *capacitor_Name_label;
    QLabel *capacitor_Alias_label;
    QLabel *capacitor_Id_label;
    QLineEdit *capacitorID_lineEdit;
    QLineEdit *capacitorName_lineEdit;
    QLineEdit *capacitorAlias_lineEdit;
    QGridLayout *gridLayout_2;
    QLabel *label_18;
    QComboBox *capacitorRatedVoltage_comboBox;
    QLabel *label_4;
    QLineEdit *capacitorMaxVoltage_lineEdit;
    QLabel *label_19;
    QComboBox *capacitorNumberOfPhasescomboBox;
    QLabel *label_5;
    QLineEdit *capacitorMinVoltage_lineEdit;
    QLabel *label_6;
    QComboBox *capacitorConnectionType_comboBox;
    QLabel *label_7;
    QLineEdit *capacitorNominalSection_lineEdit;
    QLabel *label_8;
    QPlainTextEdit *capacitorDescription_plainTextEdit;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout;
    QLabel *label_9;
    QLineEdit *capacitorReactivePower_lineEdit;
    QLabel *label_10;
    QLineEdit *capacitorActivePowerLoss_lineEdit;
    QDialogButtonBox *capacitor_buttonBox;

    void setupUi(QDialog *Capacitor)
    {
        if (Capacitor->objectName().isEmpty())
            Capacitor->setObjectName(QStringLiteral("Capacitor"));
        Capacitor->resize(456, 542);
        verticalLayout = new QVBoxLayout(Capacitor);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setHorizontalSpacing(65);
        gridLayout->setVerticalSpacing(16);
        capacitor_Name_label = new QLabel(Capacitor);
        capacitor_Name_label->setObjectName(QStringLiteral("capacitor_Name_label"));

        gridLayout->addWidget(capacitor_Name_label, 1, 0, 1, 2);

        capacitor_Alias_label = new QLabel(Capacitor);
        capacitor_Alias_label->setObjectName(QStringLiteral("capacitor_Alias_label"));

        gridLayout->addWidget(capacitor_Alias_label, 2, 0, 1, 2);

        capacitor_Id_label = new QLabel(Capacitor);
        capacitor_Id_label->setObjectName(QStringLiteral("capacitor_Id_label"));

        gridLayout->addWidget(capacitor_Id_label, 0, 0, 1, 2);

        capacitorID_lineEdit = new QLineEdit(Capacitor);
        capacitorID_lineEdit->setObjectName(QStringLiteral("capacitorID_lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(capacitorID_lineEdit->sizePolicy().hasHeightForWidth());
        capacitorID_lineEdit->setSizePolicy(sizePolicy);
        capacitorID_lineEdit->setMaximumSize(QSize(130, 16777215));
        capacitorID_lineEdit->setLayoutDirection(Qt::LeftToRight);
        capacitorID_lineEdit->setInputMethodHints(Qt::ImhNone);
        capacitorID_lineEdit->setFrame(true);
        capacitorID_lineEdit->setEchoMode(QLineEdit::Normal);
        capacitorID_lineEdit->setDragEnabled(false);
        capacitorID_lineEdit->setReadOnly(false);
        capacitorID_lineEdit->setClearButtonEnabled(false);

        gridLayout->addWidget(capacitorID_lineEdit, 0, 2, 1, 1);

        capacitorName_lineEdit = new QLineEdit(Capacitor);
        capacitorName_lineEdit->setObjectName(QStringLiteral("capacitorName_lineEdit"));
        capacitorName_lineEdit->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(capacitorName_lineEdit, 1, 2, 1, 1);

        capacitorAlias_lineEdit = new QLineEdit(Capacitor);
        capacitorAlias_lineEdit->setObjectName(QStringLiteral("capacitorAlias_lineEdit"));
        capacitorAlias_lineEdit->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(capacitorAlias_lineEdit, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_18 = new QLabel(Capacitor);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_2->addWidget(label_18, 0, 0, 1, 1);

        capacitorRatedVoltage_comboBox = new QComboBox(Capacitor);
        capacitorRatedVoltage_comboBox->setObjectName(QStringLiteral("capacitorRatedVoltage_comboBox"));
        capacitorRatedVoltage_comboBox->setEditable(false);

        gridLayout_2->addWidget(capacitorRatedVoltage_comboBox, 0, 1, 1, 1);

        label_4 = new QLabel(Capacitor);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 0, 2, 1, 1);

        capacitorMaxVoltage_lineEdit = new QLineEdit(Capacitor);
        capacitorMaxVoltage_lineEdit->setObjectName(QStringLiteral("capacitorMaxVoltage_lineEdit"));

        gridLayout_2->addWidget(capacitorMaxVoltage_lineEdit, 0, 3, 1, 1);

        label_19 = new QLabel(Capacitor);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_2->addWidget(label_19, 1, 0, 1, 1);

        capacitorNumberOfPhasescomboBox = new QComboBox(Capacitor);
        capacitorNumberOfPhasescomboBox->setObjectName(QStringLiteral("capacitorNumberOfPhasescomboBox"));
        capacitorNumberOfPhasescomboBox->setDuplicatesEnabled(false);
        capacitorNumberOfPhasescomboBox->setFrame(true);

        gridLayout_2->addWidget(capacitorNumberOfPhasescomboBox, 1, 1, 1, 1);

        label_5 = new QLabel(Capacitor);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 1, 2, 1, 1);

        capacitorMinVoltage_lineEdit = new QLineEdit(Capacitor);
        capacitorMinVoltage_lineEdit->setObjectName(QStringLiteral("capacitorMinVoltage_lineEdit"));

        gridLayout_2->addWidget(capacitorMinVoltage_lineEdit, 1, 3, 1, 1);

        label_6 = new QLabel(Capacitor);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        capacitorConnectionType_comboBox = new QComboBox(Capacitor);
        capacitorConnectionType_comboBox->setObjectName(QStringLiteral("capacitorConnectionType_comboBox"));

        gridLayout_2->addWidget(capacitorConnectionType_comboBox, 2, 1, 1, 1);

        label_7 = new QLabel(Capacitor);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 2, 2, 1, 1);

        capacitorNominalSection_lineEdit = new QLineEdit(Capacitor);
        capacitorNominalSection_lineEdit->setObjectName(QStringLiteral("capacitorNominalSection_lineEdit"));

        gridLayout_2->addWidget(capacitorNominalSection_lineEdit, 2, 3, 1, 1);

        label_8 = new QLabel(Capacitor);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 3, 0, 1, 1);

        capacitorDescription_plainTextEdit = new QPlainTextEdit(Capacitor);
        capacitorDescription_plainTextEdit->setObjectName(QStringLiteral("capacitorDescription_plainTextEdit"));

        gridLayout_2->addWidget(capacitorDescription_plainTextEdit, 4, 0, 1, 4);


        verticalLayout->addLayout(gridLayout_2);

        groupBox = new QGroupBox(Capacitor);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        gridLayout_6 = new QGridLayout(groupBox);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout->addWidget(label_9);

        capacitorReactivePower_lineEdit = new QLineEdit(groupBox);
        capacitorReactivePower_lineEdit->setObjectName(QStringLiteral("capacitorReactivePower_lineEdit"));

        horizontalLayout->addWidget(capacitorReactivePower_lineEdit);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout->addWidget(label_10);

        capacitorActivePowerLoss_lineEdit = new QLineEdit(groupBox);
        capacitorActivePowerLoss_lineEdit->setObjectName(QStringLiteral("capacitorActivePowerLoss_lineEdit"));

        horizontalLayout->addWidget(capacitorActivePowerLoss_lineEdit);


        gridLayout_6->addLayout(horizontalLayout, 0, 0, 1, 2);


        verticalLayout->addWidget(groupBox);

        capacitor_buttonBox = new QDialogButtonBox(Capacitor);
        capacitor_buttonBox->setObjectName(QStringLiteral("capacitor_buttonBox"));
        capacitor_buttonBox->setOrientation(Qt::Horizontal);
        capacitor_buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Discard|QDialogButtonBox::Save);
        capacitor_buttonBox->setCenterButtons(false);

        verticalLayout->addWidget(capacitor_buttonBox);


        retranslateUi(Capacitor);

        QMetaObject::connectSlotsByName(Capacitor);
    } // setupUi

    void retranslateUi(QDialog *Capacitor)
    {
        Capacitor->setWindowTitle(QApplication::translate("Capacitor", "Capacitor", 0));
        capacitor_Name_label->setText(QApplication::translate("Capacitor", "Name:", 0));
        capacitor_Alias_label->setText(QApplication::translate("Capacitor", "Alias:", 0));
        capacitor_Id_label->setText(QApplication::translate("Capacitor", "UID:", 0));
        capacitorID_lineEdit->setInputMask(QString());
        label_18->setText(QApplication::translate("Capacitor", "Rated Voltage [kV]:", 0));
        capacitorRatedVoltage_comboBox->clear();
        capacitorRatedVoltage_comboBox->insertItems(0, QStringList()
         << QApplication::translate("Capacitor", "0.23", 0)
         << QApplication::translate("Capacitor", "0.40", 0)
         << QApplication::translate("Capacitor", "0.42", 0)
         << QApplication::translate("Capacitor", "0.52", 0)
         << QApplication::translate("Capacitor", "3.00", 0)
         << QApplication::translate("Capacitor", "6.00", 0)
         << QApplication::translate("Capacitor", "6.30", 0)
         << QApplication::translate("Capacitor", "10.00", 0)
         << QApplication::translate("Capacitor", "10.38", 0)
         << QApplication::translate("Capacitor", "10.50", 0)
         << QApplication::translate("Capacitor", "11.00", 0)
         << QApplication::translate("Capacitor", "13.00", 0)
         << QApplication::translate("Capacitor", "20.00", 0)
         << QApplication::translate("Capacitor", "20.50", 0)
         << QApplication::translate("Capacitor", "33.00", 0)
         << QApplication::translate("Capacitor", "35.00", 0)
         << QApplication::translate("Capacitor", "36.75", 0)
         << QApplication::translate("Capacitor", "66.00", 0)
         << QApplication::translate("Capacitor", "110.00", 0)
         << QApplication::translate("Capacitor", "132.00", 0)
         << QApplication::translate("Capacitor", "220.00", 0)
         << QApplication::translate("Capacitor", "400.00", 0)
        );
        capacitorRatedVoltage_comboBox->setCurrentText(QApplication::translate("Capacitor", "0.23", 0));
        label_4->setText(QApplication::translate("Capacitor", "Maximum Voltage [kV]:", 0));
        label_19->setText(QApplication::translate("Capacitor", "Number Of Phases:", 0));
        capacitorNumberOfPhasescomboBox->clear();
        capacitorNumberOfPhasescomboBox->insertItems(0, QStringList()
         << QApplication::translate("Capacitor", "Single Phase", 0)
         << QApplication::translate("Capacitor", "Two Phases", 0)
         << QApplication::translate("Capacitor", "Three Phases", 0)
        );
        label_5->setText(QApplication::translate("Capacitor", "Minumum Voltage [kV:]", 0));
        label_6->setText(QApplication::translate("Capacitor", "Connection Type:", 0));
        capacitorConnectionType_comboBox->clear();
        capacitorConnectionType_comboBox->insertItems(0, QStringList()
         << QApplication::translate("Capacitor", "Delta", 0)
         << QApplication::translate("Capacitor", "Wye", 0)
         << QApplication::translate("Capacitor", "Autotransformer", 0)
         << QApplication::translate("Capacitor", "Wye with ground", 0)
         << QApplication::translate("Capacitor", "Zigzag", 0)
        );
        label_7->setText(QApplication::translate("Capacitor", "Nominal Section  [1]:", 0));
        label_8->setText(QApplication::translate("Capacitor", "Description:", 0));
        groupBox->setTitle(QApplication::translate("Capacitor", "Reactive power per section", 0));
        label_9->setText(QApplication::translate("Capacitor", "Reactive Power [kVAr]:", 0));
        label_10->setText(QApplication::translate("Capacitor", "Active Power Loss [kW:]", 0));
    } // retranslateUi

};

namespace Ui {
    class Capacitor: public Ui_Capacitor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAPACITOR_H
