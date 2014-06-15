/********************************************************************************
** Form generated from reading UI file 'searchwindowbankplacement.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHWINDOWBANKPLACEMENT_H
#define UI_SEARCHWINDOWBANKPLACEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SearchWindowBankPlacement
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *Placement_searchPhrase_lineEdit;
    QLabel *label_2;
    QComboBox *Placement_searchBy_comboBox;
    QTableView *capacitor_tableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *new_pushButton;
    QPushButton *edit_pushButton;
    QPushButton *delete_pushButton;
    QPushButton *cancel_pushButton;

    void setupUi(QDialog *SearchWindowBankPlacement)
    {
        if (SearchWindowBankPlacement->objectName().isEmpty())
            SearchWindowBankPlacement->setObjectName(QStringLiteral("SearchWindowBankPlacement"));
        SearchWindowBankPlacement->resize(338, 343);
        verticalLayout = new QVBoxLayout(SearchWindowBankPlacement);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(SearchWindowBankPlacement);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        Placement_searchPhrase_lineEdit = new QLineEdit(SearchWindowBankPlacement);
        Placement_searchPhrase_lineEdit->setObjectName(QStringLiteral("Placement_searchPhrase_lineEdit"));
        Placement_searchPhrase_lineEdit->setClearButtonEnabled(false);

        horizontalLayout->addWidget(Placement_searchPhrase_lineEdit);

        label_2 = new QLabel(SearchWindowBankPlacement);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        Placement_searchBy_comboBox = new QComboBox(SearchWindowBankPlacement);
        Placement_searchBy_comboBox->setObjectName(QStringLiteral("Placement_searchBy_comboBox"));

        horizontalLayout->addWidget(Placement_searchBy_comboBox);


        verticalLayout->addLayout(horizontalLayout);

        capacitor_tableView = new QTableView(SearchWindowBankPlacement);
        capacitor_tableView->setObjectName(QStringLiteral("capacitor_tableView"));

        verticalLayout->addWidget(capacitor_tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        new_pushButton = new QPushButton(SearchWindowBankPlacement);
        new_pushButton->setObjectName(QStringLiteral("new_pushButton"));

        horizontalLayout_2->addWidget(new_pushButton);

        edit_pushButton = new QPushButton(SearchWindowBankPlacement);
        edit_pushButton->setObjectName(QStringLiteral("edit_pushButton"));

        horizontalLayout_2->addWidget(edit_pushButton);

        delete_pushButton = new QPushButton(SearchWindowBankPlacement);
        delete_pushButton->setObjectName(QStringLiteral("delete_pushButton"));

        horizontalLayout_2->addWidget(delete_pushButton);

        cancel_pushButton = new QPushButton(SearchWindowBankPlacement);
        cancel_pushButton->setObjectName(QStringLiteral("cancel_pushButton"));

        horizontalLayout_2->addWidget(cancel_pushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(SearchWindowBankPlacement);

        QMetaObject::connectSlotsByName(SearchWindowBankPlacement);
    } // setupUi

    void retranslateUi(QDialog *SearchWindowBankPlacement)
    {
        SearchWindowBankPlacement->setWindowTitle(QApplication::translate("SearchWindowBankPlacement", "Dialog", 0));
        label->setText(QApplication::translate("SearchWindowBankPlacement", "Search Phrase:", 0));
        label_2->setText(QApplication::translate("SearchWindowBankPlacement", "Search By:", 0));
        Placement_searchBy_comboBox->clear();
        Placement_searchBy_comboBox->insertItems(0, QStringList()
         << QApplication::translate("SearchWindowBankPlacement", "ID", 0)
         << QApplication::translate("SearchWindowBankPlacement", "Name", 0)
         << QApplication::translate("SearchWindowBankPlacement", "JobID", 0)
        );
        new_pushButton->setText(QApplication::translate("SearchWindowBankPlacement", "New", 0));
        edit_pushButton->setText(QApplication::translate("SearchWindowBankPlacement", "Edit", 0));
        delete_pushButton->setText(QApplication::translate("SearchWindowBankPlacement", "Delete", 0));
        cancel_pushButton->setText(QApplication::translate("SearchWindowBankPlacement", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchWindowBankPlacement: public Ui_SearchWindowBankPlacement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHWINDOWBANKPLACEMENT_H
