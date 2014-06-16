/********************************************************************************
** Form generated from reading UI file 'searchwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHWINDOW_H
#define UI_SEARCHWINDOW_H

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
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SearchWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *searchPhrase_lineEdit;
    QLabel *label_2;
    QComboBox *comboBox;
    QTableView *tableView;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SearchWindow)
    {
        if (SearchWindow->objectName().isEmpty())
            SearchWindow->setObjectName(QStringLiteral("SearchWindow"));
        SearchWindow->resize(416, 383);
        verticalLayout = new QVBoxLayout(SearchWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(SearchWindow);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        searchPhrase_lineEdit = new QLineEdit(SearchWindow);
        searchPhrase_lineEdit->setObjectName(QStringLiteral("searchPhrase_lineEdit"));
        searchPhrase_lineEdit->setClearButtonEnabled(false);

        horizontalLayout->addWidget(searchPhrase_lineEdit);

        label_2 = new QLabel(SearchWindow);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox = new QComboBox(SearchWindow);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(SearchWindow);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);

        buttonBox = new QDialogButtonBox(SearchWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Discard|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SearchWindow);

        QMetaObject::connectSlotsByName(SearchWindow);
    } // setupUi

    void retranslateUi(QDialog *SearchWindow)
    {
        SearchWindow->setWindowTitle(QApplication::translate("SearchWindow", "Dialog", 0));
        label->setText(QApplication::translate("SearchWindow", "Search Phrase:", 0));
        label_2->setText(QApplication::translate("SearchWindow", "Search By:", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("SearchWindow", "Name", 0)
         << QApplication::translate("SearchWindow", "Alias", 0)
         << QApplication::translate("SearchWindow", "ID", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class SearchWindow: public Ui_SearchWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHWINDOW_H
