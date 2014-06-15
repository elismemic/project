/********************************************************************************
** Form generated from reading UI file 'project.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECT_H
#define UI_PROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Project
{
public:
    QAction *actionConductor;
    QAction *actionCapacitor;
    QAction *actionCapacitor_Bank_Placement;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QMenuBar *menuBar;
    QMenu *menuCatalogs;
    QMenu *menuPlacements;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Project)
    {
        if (Project->objectName().isEmpty())
            Project->setObjectName(QStringLiteral("Project"));
        Project->resize(338, 313);
        actionConductor = new QAction(Project);
        actionConductor->setObjectName(QStringLiteral("actionConductor"));
        actionCapacitor = new QAction(Project);
        actionCapacitor->setObjectName(QStringLiteral("actionCapacitor"));
        actionCapacitor_Bank_Placement = new QAction(Project);
        actionCapacitor_Bank_Placement->setObjectName(QStringLiteral("actionCapacitor_Bank_Placement"));
        centralWidget = new QWidget(Project);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        horizontalLayout_2->addLayout(horizontalLayout);

        Project->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Project);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 338, 21));
        menuCatalogs = new QMenu(menuBar);
        menuCatalogs->setObjectName(QStringLiteral("menuCatalogs"));
        menuPlacements = new QMenu(menuBar);
        menuPlacements->setObjectName(QStringLiteral("menuPlacements"));
        Project->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Project);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Project->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Project);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Project->setStatusBar(statusBar);

        menuBar->addAction(menuCatalogs->menuAction());
        menuBar->addAction(menuPlacements->menuAction());
        menuCatalogs->addAction(actionConductor);
        menuCatalogs->addAction(actionCapacitor);
        menuPlacements->addAction(actionCapacitor_Bank_Placement);

        retranslateUi(Project);

        QMetaObject::connectSlotsByName(Project);
    } // setupUi

    void retranslateUi(QMainWindow *Project)
    {
        Project->setWindowTitle(QApplication::translate("Project", "Project", 0));
        actionConductor->setText(QApplication::translate("Project", "Conductor", 0));
        actionCapacitor->setText(QApplication::translate("Project", "Capacitor", 0));
        actionCapacitor_Bank_Placement->setText(QApplication::translate("Project", "Capacitor Bank Placement", 0));
        label->setText(QApplication::translate("Project", "JobID:", 0));
        menuCatalogs->setTitle(QApplication::translate("Project", "Catalogs", 0));
        menuPlacements->setTitle(QApplication::translate("Project", "Placements", 0));
    } // retranslateUi

};

namespace Ui {
    class Project: public Ui_Project {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECT_H
