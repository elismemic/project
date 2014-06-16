/********************************************************************************
** Form generated from reading UI file 'conductor.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONDUCTOR_H
#define UI_CONDUCTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Conductor
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout_3;
    QLabel *label_5;
    QLineEdit *conductorID_lineEdit_2;
    QLabel *label_6;
    QLineEdit *lineEdit_3;
    QLabel *label_21;
    QLineEdit *lineEdit_4;
    QLabel *label_22;
    QComboBox *conductorSectionTypecomboBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_19;
    QLineEdit *conductor_R_lineEdit;
    QLabel *label_18;
    QLabel *label_9;
    QLineEdit *conductor_G_lineEdit;
    QLineEdit *conductor_B_lineEdit;
    QLineEdit *conductorG0_lineEdit;
    QLineEdit *conductor_B0_lineEdit;
    QLabel *label_13;
    QLabel *label_14;
    QLineEdit *conductor_X0_lineEdit;
    QLabel *label_10;
    QLabel *label_12;
    QComboBox *conductorNumberOfPhasescomboBox;
    QLabel *label_11;
    QLineEdit *conductor_R0_lineEdit;
    QLineEdit *conductor_X_lineEdit;
    QLabel *label_7;
    QComboBox *conductorRatedVoltage_comboBox;
    QLabel *label_8;
    QFormLayout *formLayout_2;
    QLabel *label_15;
    QLineEdit *conductor_mediumrating_lineEdit;
    QLabel *label_16;
    QLineEdit *conductor_longrating_lineEdit;
    QLabel *label_17;
    QLineEdit *conductor_shortrating_lineEdit;
    QLabel *label_20;
    QPlainTextEdit *conductor_comment_plainTextEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Conductor)
    {
        if (Conductor->objectName().isEmpty())
            Conductor->setObjectName(QStringLiteral("Conductor"));
        Conductor->resize(426, 485);
        verticalLayout = new QVBoxLayout(Conductor);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_5 = new QLabel(Conductor);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_5);

        conductorID_lineEdit_2 = new QLineEdit(Conductor);
        conductorID_lineEdit_2->setObjectName(QStringLiteral("conductorID_lineEdit_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(conductorID_lineEdit_2->sizePolicy().hasHeightForWidth());
        conductorID_lineEdit_2->setSizePolicy(sizePolicy);
        conductorID_lineEdit_2->setMaximumSize(QSize(130, 16777215));
        conductorID_lineEdit_2->setLayoutDirection(Qt::LeftToRight);
        conductorID_lineEdit_2->setInputMethodHints(Qt::ImhNone);
        conductorID_lineEdit_2->setFrame(true);
        conductorID_lineEdit_2->setEchoMode(QLineEdit::Normal);
        conductorID_lineEdit_2->setDragEnabled(false);
        conductorID_lineEdit_2->setReadOnly(false);
        conductorID_lineEdit_2->setClearButtonEnabled(false);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, conductorID_lineEdit_2);

        label_6 = new QLabel(Conductor);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_6);

        lineEdit_3 = new QLineEdit(Conductor);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, lineEdit_3);

        label_21 = new QLabel(Conductor);
        label_21->setObjectName(QStringLiteral("label_21"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_21);

        lineEdit_4 = new QLineEdit(Conductor);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, lineEdit_4);

        label_22 = new QLabel(Conductor);
        label_22->setObjectName(QStringLiteral("label_22"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_22);

        conductorSectionTypecomboBox_2 = new QComboBox(Conductor);
        conductorSectionTypecomboBox_2->setObjectName(QStringLiteral("conductorSectionTypecomboBox_2"));
        conductorSectionTypecomboBox_2->setAcceptDrops(false);
        conductorSectionTypecomboBox_2->setLayoutDirection(Qt::RightToLeft);
        conductorSectionTypecomboBox_2->setAutoFillBackground(true);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, conductorSectionTypecomboBox_2);


        verticalLayout->addLayout(formLayout_3);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(23);
        label_19 = new QLabel(Conductor);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_2->addWidget(label_19, 0, 2, 1, 1);

        conductor_R_lineEdit = new QLineEdit(Conductor);
        conductor_R_lineEdit->setObjectName(QStringLiteral("conductor_R_lineEdit"));
        conductor_R_lineEdit->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(conductor_R_lineEdit, 2, 1, 1, 1);

        label_18 = new QLabel(Conductor);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_2->addWidget(label_18, 0, 0, 1, 1);

        label_9 = new QLabel(Conductor);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 8, 0, 1, 1);

        conductor_G_lineEdit = new QLineEdit(Conductor);
        conductor_G_lineEdit->setObjectName(QStringLiteral("conductor_G_lineEdit"));
        conductor_G_lineEdit->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(conductor_G_lineEdit, 8, 1, 1, 1);

        conductor_B_lineEdit = new QLineEdit(Conductor);
        conductor_B_lineEdit->setObjectName(QStringLiteral("conductor_B_lineEdit"));
        conductor_B_lineEdit->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(conductor_B_lineEdit, 11, 1, 1, 1);

        conductorG0_lineEdit = new QLineEdit(Conductor);
        conductorG0_lineEdit->setObjectName(QStringLiteral("conductorG0_lineEdit"));
        conductorG0_lineEdit->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(conductorG0_lineEdit, 8, 3, 1, 1);

        conductor_B0_lineEdit = new QLineEdit(Conductor);
        conductor_B0_lineEdit->setObjectName(QStringLiteral("conductor_B0_lineEdit"));
        conductor_B0_lineEdit->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(conductor_B0_lineEdit, 11, 3, 1, 1);

        label_13 = new QLabel(Conductor);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_2->addWidget(label_13, 11, 2, 1, 1);

        label_14 = new QLabel(Conductor);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_2->addWidget(label_14, 5, 2, 1, 1);

        conductor_X0_lineEdit = new QLineEdit(Conductor);
        conductor_X0_lineEdit->setObjectName(QStringLiteral("conductor_X0_lineEdit"));
        conductor_X0_lineEdit->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(conductor_X0_lineEdit, 5, 3, 1, 1);

        label_10 = new QLabel(Conductor);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 11, 0, 1, 1);

        label_12 = new QLabel(Conductor);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 2, 2, 1, 1);

        conductorNumberOfPhasescomboBox = new QComboBox(Conductor);
        conductorNumberOfPhasescomboBox->setObjectName(QStringLiteral("conductorNumberOfPhasescomboBox"));
        conductorNumberOfPhasescomboBox->setDuplicatesEnabled(false);
        conductorNumberOfPhasescomboBox->setFrame(true);

        gridLayout_2->addWidget(conductorNumberOfPhasescomboBox, 0, 3, 1, 1);

        label_11 = new QLabel(Conductor);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setLayoutDirection(Qt::LeftToRight);
        label_11->setAutoFillBackground(false);

        gridLayout_2->addWidget(label_11, 8, 2, 1, 1);

        conductor_R0_lineEdit = new QLineEdit(Conductor);
        conductor_R0_lineEdit->setObjectName(QStringLiteral("conductor_R0_lineEdit"));
        conductor_R0_lineEdit->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(conductor_R0_lineEdit, 2, 3, 1, 1);

        conductor_X_lineEdit = new QLineEdit(Conductor);
        conductor_X_lineEdit->setObjectName(QStringLiteral("conductor_X_lineEdit"));
        conductor_X_lineEdit->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(conductor_X_lineEdit, 5, 1, 1, 1);

        label_7 = new QLabel(Conductor);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        conductorRatedVoltage_comboBox = new QComboBox(Conductor);
        conductorRatedVoltage_comboBox->setObjectName(QStringLiteral("conductorRatedVoltage_comboBox"));
        conductorRatedVoltage_comboBox->setEditable(false);

        gridLayout_2->addWidget(conductorRatedVoltage_comboBox, 0, 1, 1, 1);

        label_8 = new QLabel(Conductor);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 5, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_15 = new QLabel(Conductor);
        label_15->setObjectName(QStringLiteral("label_15"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_15);

        conductor_mediumrating_lineEdit = new QLineEdit(Conductor);
        conductor_mediumrating_lineEdit->setObjectName(QStringLiteral("conductor_mediumrating_lineEdit"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, conductor_mediumrating_lineEdit);

        label_16 = new QLabel(Conductor);
        label_16->setObjectName(QStringLiteral("label_16"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_16);

        conductor_longrating_lineEdit = new QLineEdit(Conductor);
        conductor_longrating_lineEdit->setObjectName(QStringLiteral("conductor_longrating_lineEdit"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, conductor_longrating_lineEdit);

        label_17 = new QLabel(Conductor);
        label_17->setObjectName(QStringLiteral("label_17"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_17);

        conductor_shortrating_lineEdit = new QLineEdit(Conductor);
        conductor_shortrating_lineEdit->setObjectName(QStringLiteral("conductor_shortrating_lineEdit"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, conductor_shortrating_lineEdit);


        verticalLayout->addLayout(formLayout_2);

        label_20 = new QLabel(Conductor);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setLayoutDirection(Qt::LeftToRight);
        label_20->setFrameShadow(QFrame::Plain);
        label_20->setLineWidth(0);
        label_20->setTextFormat(Qt::RichText);
        label_20->setScaledContents(false);
        label_20->setWordWrap(true);
        label_20->setOpenExternalLinks(false);

        verticalLayout->addWidget(label_20);

        conductor_comment_plainTextEdit = new QPlainTextEdit(Conductor);
        conductor_comment_plainTextEdit->setObjectName(QStringLiteral("conductor_comment_plainTextEdit"));
        conductor_comment_plainTextEdit->setFocusPolicy(Qt::StrongFocus);
        conductor_comment_plainTextEdit->setAcceptDrops(false);
        conductor_comment_plainTextEdit->setAutoFillBackground(false);
        conductor_comment_plainTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        conductor_comment_plainTextEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        conductor_comment_plainTextEdit->setTabChangesFocus(false);
        conductor_comment_plainTextEdit->setReadOnly(false);
        conductor_comment_plainTextEdit->setOverwriteMode(false);
        conductor_comment_plainTextEdit->setBackgroundVisible(false);
        conductor_comment_plainTextEdit->setCenterOnScroll(false);

        verticalLayout->addWidget(conductor_comment_plainTextEdit);

        buttonBox = new QDialogButtonBox(Conductor);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Conductor);

        QMetaObject::connectSlotsByName(Conductor);
    } // setupUi

    void retranslateUi(QDialog *Conductor)
    {
        Conductor->setWindowTitle(QApplication::translate("Conductor", "Dialog", 0));
        label_5->setText(QApplication::translate("Conductor", "ID:", 0));
        conductorID_lineEdit_2->setInputMask(QString());
        label_6->setText(QApplication::translate("Conductor", "Name:", 0));
        label_21->setText(QApplication::translate("Conductor", "Alias:", 0));
        label_22->setText(QApplication::translate("Conductor", "Section Type:", 0));
        conductorSectionTypecomboBox_2->clear();
        conductorSectionTypecomboBox_2->insertItems(0, QStringList()
         << QApplication::translate("Conductor", "Overhead", 0)
         << QApplication::translate("Conductor", "Cable", 0)
        );
        label_19->setText(QApplication::translate("Conductor", "Number Of Phases:", 0));
        conductor_R_lineEdit->setText(QString());
        label_18->setText(QApplication::translate("Conductor", "Rated Voltage [kV]:", 0));
        label_9->setText(QApplication::translate("Conductor", "g  [uS/km]:", 0));
        label_13->setText(QApplication::translate("Conductor", "b0  [uS/km]:", 0));
        label_14->setText(QApplication::translate("Conductor", "x0 [Ohm/km]:", 0));
        label_10->setText(QApplication::translate("Conductor", "b  [uS/km]:", 0));
        label_12->setText(QApplication::translate("Conductor", "r0  [Ohm/km]:", 0));
        conductorNumberOfPhasescomboBox->clear();
        conductorNumberOfPhasescomboBox->insertItems(0, QStringList()
         << QApplication::translate("Conductor", "Single Phase", 0)
         << QApplication::translate("Conductor", "Two Phases", 0)
         << QApplication::translate("Conductor", "Three Phases", 0)
        );
        label_11->setText(QApplication::translate("Conductor", "g0  [uS/km]:", 0));
        label_7->setText(QApplication::translate("Conductor", "r  [Ohm/km]:", 0));
        conductorRatedVoltage_comboBox->clear();
        conductorRatedVoltage_comboBox->insertItems(0, QStringList()
         << QApplication::translate("Conductor", "0.23", 0)
         << QApplication::translate("Conductor", "0.40", 0)
         << QApplication::translate("Conductor", "0.42", 0)
         << QApplication::translate("Conductor", "0.52", 0)
         << QApplication::translate("Conductor", "3.00", 0)
         << QApplication::translate("Conductor", "6.00", 0)
         << QApplication::translate("Conductor", "6.30", 0)
         << QApplication::translate("Conductor", "10.00", 0)
         << QApplication::translate("Conductor", "10.38", 0)
         << QApplication::translate("Conductor", "10.50", 0)
         << QApplication::translate("Conductor", "11.00", 0)
         << QApplication::translate("Conductor", "13.00", 0)
         << QApplication::translate("Conductor", "20.00", 0)
         << QApplication::translate("Conductor", "20.50", 0)
         << QApplication::translate("Conductor", "33.00", 0)
         << QApplication::translate("Conductor", "35.00", 0)
         << QApplication::translate("Conductor", "36.75", 0)
         << QApplication::translate("Conductor", "66.00", 0)
         << QApplication::translate("Conductor", "110.00", 0)
         << QApplication::translate("Conductor", "132.00", 0)
         << QApplication::translate("Conductor", "220.00", 0)
         << QApplication::translate("Conductor", "400.00", 0)
        );
        conductorRatedVoltage_comboBox->setCurrentText(QApplication::translate("Conductor", "0.23", 0));
        label_8->setText(QApplication::translate("Conductor", "x [Ohm/km]:", 0));
        label_15->setText(QApplication::translate("Conductor", "Short term rating [A]:", 0));
        label_16->setText(QApplication::translate("Conductor", "Medium term rating [A]:", 0));
        label_17->setText(QApplication::translate("Conductor", "Long term rating [A]:", 0));
        label_20->setText(QApplication::translate("Conductor", "Comment:", 0));
    } // retranslateUi

};

namespace Ui {
    class Conductor: public Ui_Conductor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONDUCTOR_H
