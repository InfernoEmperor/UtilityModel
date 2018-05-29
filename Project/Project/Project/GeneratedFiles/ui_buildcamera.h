/********************************************************************************
** Form generated from reading UI file 'buildcamera.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUILDCAMERA_H
#define UI_BUILDCAMERA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuildCamera
{
public:

    void setupUi(QWidget *BuildCamera)
    {
        if (BuildCamera->objectName().isEmpty())
            BuildCamera->setObjectName(QStringLiteral("BuildCamera"));
        BuildCamera->resize(400, 300);

        retranslateUi(BuildCamera);

        QMetaObject::connectSlotsByName(BuildCamera);
    } // setupUi

    void retranslateUi(QWidget *BuildCamera)
    {
        BuildCamera->setWindowTitle(QApplication::translate("BuildCamera", "BuildCamera", 0));
    } // retranslateUi

};

namespace Ui {
    class BuildCamera: public Ui_BuildCamera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUILDCAMERA_H
