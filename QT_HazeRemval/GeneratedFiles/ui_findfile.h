/********************************************************************************
** Form generated from reading UI file 'findfile.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDFILE_H
#define UI_FINDFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_findFile
{
public:
    QPushButton *pushButton;
    QLabel *test;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;

    void setupUi(QFileDialog *findFile)
    {
        if (findFile->objectName().isEmpty())
            findFile->setObjectName(QStringLiteral("findFile"));
        findFile->resize(400, 300);
        pushButton = new QPushButton(findFile);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 250, 75, 23));
        test = new QLabel(findFile);
        test->setObjectName(QStringLiteral("test"));
        test->setEnabled(true);
        test->setGeometry(QRect(150, 110, 171, 16));
        lineEdit = new QLineEdit(findFile);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(180, 110, 113, 20));
        pushButton_2 = new QPushButton(findFile);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(250, 260, 75, 23));

        retranslateUi(findFile);

        QMetaObject::connectSlotsByName(findFile);
    } // setupUi

    void retranslateUi(QFileDialog *findFile)
    {
        findFile->setWindowTitle(QApplication::translate("findFile", "findFile", nullptr));
        pushButton->setText(QApplication::translate("findFile", "\347\241\256\345\256\232", nullptr));
        test->setText(QApplication::translate("findFile", "\346\222\222\346\227\246", nullptr));
        pushButton_2->setText(QApplication::translate("findFile", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class findFile: public Ui_findFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDFILE_H
