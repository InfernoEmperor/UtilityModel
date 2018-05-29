/********************************************************************************
** Form generated from reading UI file 'project.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECT_H
#define UI_PROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ProjectClass
{
public:
    void setupUi(QDialog *ProjectClass)
    {
        if (ProjectClass->objectName().isEmpty())
            ProjectClass->setObjectName(QStringLiteral("ProjectClass"));
        ProjectClass->setFixedSize(1240, 600);
        retranslateUi(ProjectClass);
        QMetaObject::connectSlotsByName(ProjectClass);
    } // setupUi

    void retranslateUi(QDialog *ProjectClass)
    {
        ProjectClass->setWindowTitle(QApplication::translate("ProjectClass", "Control", 0));
    } // retranslateUi

};

namespace Ui {
    class ProjectClass: public Ui_ProjectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECT_H
