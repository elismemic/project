/********************************************************************************
** Form generated from reading UI file 'searchwindowconductor.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHWINDOWCONDUCTOR_H
#define UI_SEARCHWINDOWCONDUCTOR_H

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

class Ui_SearchWindowConductor
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *searchPhrase_lineEdit;
    QLabel *label_2;
    QComboBox *comboBox;
    QTableView *conductor_tableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *new_pushButton;
    QPushButton *edit_pushButton;
    QPushButton *delete_pushButton;
    QPushButton *cancel_pushButton;

    void setupUi(QDialog *SearchWindowConductor)
    {
        if (SearchWindowConductor->objectName().isEmpty())
            SearchWindowConductor->setObjectName(QStringLiteral("SearchWindowConductor"));
        SearchWindowConductor->resize(338, 359);
        verticalLayout = new QVBoxLayout(SearchWindowConductor);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(SearchWindowConductor);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        searchPhrase_lineEdit = new QLineEdit(SearchWindowConductor);
        searchPhrase_lineEdit->setObjectName(QStringLiteral("searchPhrase_lineEdit"));
        searchPhrase_lineEdit->setClearButtonEnabled(false);

        horizontalLayout->addWidget(searchPhrase_lineEdit);

        label_2 = new QLabel(SearchWindowConductor);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox = new QComboBox(SearchWindowConductor);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        conductor_tableView = new QTableView(SearchWindowConductor);
        conductor_tableView->setObjectName(QStringLiteral("conductor_tableView"));

        verticalLayout->addWidget(conductor_tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        new_pushButton = new QPushButton(SearchWindowConductor);
        new_pushButton->setObjectName(QStringLiteral("new_pushButton"));

        horizontalLayout_2->addWidget(new_pushButton);

        edit_pushButton = new QPushButton(SearchWindowConductor);
        edit_pushButton->setObjectName(QStringLiteral("edit_pushButton"));

        horizontalLayout_2->addWidget(edit_pushButton);

        delete_pushButton = new QPushButton(SearchWindowConductor);
        delete_pushButton->setObjectName(QStringLiteral("delete_pushButton"));

        horizontalLayout_2->addWidget(delete_pushButton);

        cancel_pushButton = new QPushButton(SearchWindowConductor);
        cancel_pushButton->setObjectName(QStringLiteral("cancel_pushButton"));

        horizontalLayout_2->addWidget(cancel_pushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(SearchWindowConductor);

        QMetaObject::connectSlotsByName(SearchWindowConductor);
    } // setupUi

    void retranslateUi(QDialog *SearchWindowConductor)
    {
        SearchWindowConductor->setWindowTitle(QApplication::translate("SearchWindowConductor", "Dialog", 0));
        label->setText(QApplication::translate("SearchWindowConductor", "Search Phrase:", 0));
        label_2->setText(QApplication::translate("SearchWindowConductor", "Search By:", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("SearchWindowConductor", "ID", 0)
         << QApplication::translate("SearchWindowConductor", "Name", 0)
         << QApplication::translate("SearchWindowConductor", "JobID", 0)
        );
        new_pushButton->setText(QApplication::translate("SearchWindowConductor", "New", 0));
        edit_pushButton->setText(QApplication::translate("SearchWindowConductor", "Edit", 0));
        delete_pushButton->setText(QApplication::translate("SearchWindowConductor", "Delete", 0));
        cancel_pushButton->setText(QApplication::translate("SearchWindowConductor", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class SearchWindowConductor: public Ui_SearchWindowConductor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHWINDOWCONDUCTOR_H
