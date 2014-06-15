/********************************************************************************
** Form generated from reading UI file 'searchwindowcapacitor.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHWINDOWCAPACITOR_H
#define UI_SEARCHWINDOWCAPACITOR_H

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

class Ui_SearchWindowCapacitor
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *Capacitor_searchPhrase_lineEdit;
    QLabel *label_2;
    QComboBox *Capacitor_searchBy_comboBox;
    QTableView *capacitor_tableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *new_pushButton;
    QPushButton *edit_pushButton;
    QPushButton *delete_pushButton;
    QPushButton *cancel_pushButton;

    void setupUi(QDialog *SearchWindowCapacitor)
    {
        if (SearchWindowCapacitor->objectName().isEmpty())
            SearchWindowCapacitor->setObjectName(QStringLiteral("SearchWindowCapacitor"));
        SearchWindowCapacitor->resize(338, 332);
        verticalLayout = new QVBoxLayout(SearchWindowCapacitor);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(SearchWindowCapacitor);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        Capacitor_searchPhrase_lineEdit = new QLineEdit(SearchWindowCapacitor);
        Capacitor_searchPhrase_lineEdit->setObjectName(QStringLiteral("Capacitor_searchPhrase_lineEdit"));
        Capacitor_searchPhrase_lineEdit->setClearButtonEnabled(false);

        horizontalLayout->addWidget(Capacitor_searchPhrase_lineEdit);

        label_2 = new QLabel(SearchWindowCapacitor);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        Capacitor_searchBy_comboBox = new QComboBox(SearchWindowCapacitor);
        Capacitor_searchBy_comboBox->setObjectName(QStringLiteral("Capacitor_searchBy_comboBox"));

        horizontalLayout->addWidget(Capacitor_searchBy_comboBox);


        verticalLayout->addLayout(horizontalLayout);

        capacitor_tableView = new QTableView(SearchWindowCapacitor);
        capacitor_tableView->setObjectName(QStringLiteral("capacitor_tableView"));

        verticalLayout->addWidget(capacitor_tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        new_pushButton = new QPushButton(SearchWindowCapacitor);
        new_pushButton->setObjectName(QStringLiteral("new_pushButton"));

        horizontalLayout_2->addWidget(new_pushButton);

        edit_pushButton = new QPushButton(SearchWindowCapacitor);
        edit_pushButton->setObjectName(QStringLiteral("edit_pushButton"));

        horizontalLayout_2->addWidget(edit_pushButton);

        delete_pushButton = new QPushButton(SearchWindowCapacitor);
        delete_pushButton->setObjectName(QStringLiteral("delete_pushButton"));

        horizontalLayout_2->addWidget(delete_pushButton);

        cancel_pushButton = new QPushButton(SearchWindowCapacitor);
        cancel_pushButton->setObjectName(QStringLiteral("cancel_pushButton"));

        horizontalLayout_2->addWidget(cancel_pushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(SearchWindowCapacitor);

        QMetaObject::connectSlotsByName(SearchWindowCapacitor);
    } // setupUi

    void retranslateUi(QDialog *SearchWindowCapacitor)
    {
        SearchWindowCapacitor->setWindowTitle(QApplication::translate("SearchWindowCapacitor", "Dialog", 0));
        label->setText(QApplication::translate("SearchWindowCapacitor", "Search Phrase:", 0));
        label_2->setText(QApplication::translate("SearchWindowCapacitor", "Search By:", 0));
        Capacitor_searchBy_comboBox->clear();
        Capacitor_searchBy_comboBox->insertItems(0, QStringList()
         << QApplication::translate("SearchWindowCapacitor", "ID", 0)
         << QApplication::translate("SearchWindowCapacitor", "Name", 0)
         << QApplication::translate("SearchWindowCapacitor", "JobID", 0)
        );
        new_pushButton->setText(QApplication::translate("SearchWindowCapacitor", "New", 0));
        edit_pushButton->setText(QApplication::translate("SearchWindowCapacitor", "Edit", 0));
        delete_pushButton->setText(QApplication::translate("SearchWindowCapacitor", "Delete", 0));
        cancel_pushButton->setText(QApplication::translate("SearchWindowCapacitor", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchWindowCapacitor: public Ui_SearchWindowCapacitor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHWINDOWCAPACITOR_H
