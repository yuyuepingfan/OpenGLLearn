/********************************************************************************
** Form generated from reading UI file 'OpenGLLearn.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENGLLEARN_H
#define UI_OPENGLLEARN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpenGLLearnClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OpenGLLearnClass)
    {
        if (OpenGLLearnClass->objectName().isEmpty())
            OpenGLLearnClass->setObjectName(QString::fromUtf8("OpenGLLearnClass"));
        OpenGLLearnClass->resize(600, 400);
        menuBar = new QMenuBar(OpenGLLearnClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        OpenGLLearnClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OpenGLLearnClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        OpenGLLearnClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(OpenGLLearnClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        OpenGLLearnClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OpenGLLearnClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        OpenGLLearnClass->setStatusBar(statusBar);

        retranslateUi(OpenGLLearnClass);

        QMetaObject::connectSlotsByName(OpenGLLearnClass);
    } // setupUi

    void retranslateUi(QMainWindow *OpenGLLearnClass)
    {
        OpenGLLearnClass->setWindowTitle(QApplication::translate("OpenGLLearnClass", "OpenGLLearn", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OpenGLLearnClass: public Ui_OpenGLLearnClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENGLLEARN_H
