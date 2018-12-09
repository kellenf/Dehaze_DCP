/********************************************************************************
** Form generated from reading UI file 'QT_HazeRemval.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_HAZEREMVAL_H
#define UI_QT_HAZEREMVAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QT_HazeRemvalClass
{
public:
    QWidget *centralWidget;
    QPushButton *open_file;
    QPushButton *save_file;
    QLineEdit *open_path;
    QLineEdit *save_path;
    QFrame *line;
    QLabel *image0;
    QLabel *image1;
    QLabel *label;
    QLineEdit *patch_r;
    QLabel *T0_show;
    QSlider *T0;
    QLabel *show_T0;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *r;
    QLabel *show_W0;
    QLabel *label_7;
    QSlider *W0;
    QLabel *W0_show;
    QProgressBar *progressBar;
    QLabel *label_9;
    QPushButton *start;
    QPushButton *cancel;
    QCheckBox *one;
    QCheckBox *many;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *QT_HazeRemvalClass)
    {
        if (QT_HazeRemvalClass->objectName().isEmpty())
            QT_HazeRemvalClass->setObjectName(QStringLiteral("QT_HazeRemvalClass"));
        QT_HazeRemvalClass->resize(825, 627);
        centralWidget = new QWidget(QT_HazeRemvalClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        open_file = new QPushButton(centralWidget);
        open_file->setObjectName(QStringLiteral("open_file"));
        open_file->setEnabled(true);
        open_file->setGeometry(QRect(9, 19, 75, 23));
        save_file = new QPushButton(centralWidget);
        save_file->setObjectName(QStringLiteral("save_file"));
        save_file->setGeometry(QRect(9, 49, 75, 23));
        open_path = new QLineEdit(centralWidget);
        open_path->setObjectName(QStringLiteral("open_path"));
        open_path->setGeometry(QRect(90, 20, 321, 20));
        save_path = new QLineEdit(centralWidget);
        save_path->setObjectName(QStringLiteral("save_path"));
        save_path->setGeometry(QRect(90, 50, 321, 20));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 90, 851, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        image0 = new QLabel(centralWidget);
        image0->setObjectName(QStringLiteral("image0"));
        image0->setGeometry(QRect(20, 110, 380, 310));
        image0->setPixmap(QPixmap(QString::fromUtf8("C:/Users/kellen/Pictures/London-Wallpapers-HD-A46.jpg")));
        image0->setScaledContents(true);
        image1 = new QLabel(centralWidget);
        image1->setObjectName(QStringLiteral("image1"));
        image1->setGeometry(QRect(420, 110, 380, 310));
        image1->setPixmap(QPixmap(QString::fromUtf8("C:/Users/kellen/Pictures/London-Wallpapers-HD-A46.jpg")));
        image1->setScaledContents(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(21, 442, 81, 16));
        patch_r = new QLineEdit(centralWidget);
        patch_r->setObjectName(QStringLiteral("patch_r"));
        patch_r->setGeometry(QRect(110, 441, 51, 20));
        T0_show = new QLabel(centralWidget);
        T0_show->setObjectName(QStringLiteral("T0_show"));
        T0_show->setGeometry(QRect(22, 471, 91, 16));
        T0 = new QSlider(centralWidget);
        T0->setObjectName(QStringLiteral("T0"));
        T0->setGeometry(QRect(160, 471, 84, 22));
        T0->setAutoFillBackground(true);
        T0->setMaximum(100);
        T0->setValue(0);
        T0->setOrientation(Qt::Horizontal);
        show_T0 = new QLabel(centralWidget);
        show_T0->setObjectName(QStringLiteral("show_T0"));
        show_T0->setGeometry(QRect(130, 470, 31, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(250, 470, 21, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(420, 440, 91, 16));
        r = new QLineEdit(centralWidget);
        r->setObjectName(QStringLiteral("r"));
        r->setGeometry(QRect(520, 440, 51, 20));
        show_W0 = new QLabel(centralWidget);
        show_W0->setObjectName(QStringLiteral("show_W0"));
        show_W0->setGeometry(QRect(518, 469, 31, 20));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(638, 469, 21, 16));
        W0 = new QSlider(centralWidget);
        W0->setObjectName(QStringLiteral("W0"));
        W0->setGeometry(QRect(548, 470, 84, 22));
        W0->setAutoFillBackground(true);
        W0->setMaximum(100);
        W0->setValue(95);
        W0->setOrientation(Qt::Horizontal);
        W0_show = new QLabel(centralWidget);
        W0_show->setObjectName(QStringLiteral("W0_show"));
        W0_show->setGeometry(QRect(420, 470, 91, 16));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(420, 540, 381, 23));
        progressBar->setValue(0);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(420, 510, 54, 12));
        start = new QPushButton(centralWidget);
        start->setObjectName(QStringLiteral("start"));
        start->setGeometry(QRect(100, 510, 81, 31));
        cancel = new QPushButton(centralWidget);
        cancel->setObjectName(QStringLiteral("cancel"));
        cancel->setGeometry(QRect(250, 510, 81, 31));
        one = new QCheckBox(centralWidget);
        one->setObjectName(QStringLiteral("one"));
        one->setGeometry(QRect(651, 20, 71, 16));
        one->setChecked(false);
        many = new QCheckBox(centralWidget);
        many->setObjectName(QStringLiteral("many"));
        many->setGeometry(QRect(651, 50, 71, 16));
        many->setChecked(true);
        QT_HazeRemvalClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(QT_HazeRemvalClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QT_HazeRemvalClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QT_HazeRemvalClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QT_HazeRemvalClass->setStatusBar(statusBar);
        toolBar = new QToolBar(QT_HazeRemvalClass);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        QT_HazeRemvalClass->addToolBar(Qt::TopToolBarArea, toolBar);
        menuBar = new QMenuBar(QT_HazeRemvalClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 825, 23));
        QT_HazeRemvalClass->setMenuBar(menuBar);

        retranslateUi(QT_HazeRemvalClass);

        QMetaObject::connectSlotsByName(QT_HazeRemvalClass);
    } // setupUi

    void retranslateUi(QMainWindow *QT_HazeRemvalClass)
    {
        QT_HazeRemvalClass->setWindowTitle(QApplication::translate("QT_HazeRemvalClass", "QT_HazeRemval", nullptr));
        open_file->setText(QApplication::translate("QT_HazeRemvalClass", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", nullptr));
        save_file->setText(QApplication::translate("QT_HazeRemvalClass", "\344\277\235\345\255\230\346\226\207\344\273\266\345\244\271", nullptr));
        image0->setText(QString());
        image1->setText(QString());
        label->setText(QApplication::translate("QT_HazeRemvalClass", "\346\273\221\345\212\250\347\252\227\345\215\212\345\276\204(R)", nullptr));
        patch_r->setText(QApplication::translate("QT_HazeRemvalClass", "3", nullptr));
        T0_show->setText(QApplication::translate("QT_HazeRemvalClass", "\346\234\200\344\275\216\351\200\217\345\260\204\347\216\207\357\274\210T0)", nullptr));
        show_T0->setText(QApplication::translate("QT_HazeRemvalClass", "0.10", nullptr));
        label_4->setText(QApplication::translate("QT_HazeRemvalClass", "1", nullptr));
        label_5->setText(QApplication::translate("QT_HazeRemvalClass", "\345\257\274\345\220\221\346\273\244\346\263\242\345\215\212\345\276\204(r)", nullptr));
        r->setText(QApplication::translate("QT_HazeRemvalClass", "40", nullptr));
        show_W0->setText(QApplication::translate("QT_HazeRemvalClass", "0.95", nullptr));
        label_7->setText(QApplication::translate("QT_HazeRemvalClass", "1", nullptr));
        W0_show->setText(QApplication::translate("QT_HazeRemvalClass", "\351\233\276\345\255\230\351\207\217\357\274\210W0)", nullptr));
        label_9->setText(QApplication::translate("QT_HazeRemvalClass", "\345\244\204\347\220\206\350\277\233\345\272\246", nullptr));
        start->setText(QApplication::translate("QT_HazeRemvalClass", "\345\274\200\345\247\213", nullptr));
        cancel->setText(QApplication::translate("QT_HazeRemvalClass", "\345\217\226\346\266\210", nullptr));
        one->setText(QApplication::translate("QT_HazeRemvalClass", "\345\215\225\345\274\240\345\244\204\347\220\206", nullptr));
        many->setText(QApplication::translate("QT_HazeRemvalClass", "\346\211\271\351\207\217\345\244\204\347\220\206", nullptr));
        toolBar->setWindowTitle(QApplication::translate("QT_HazeRemvalClass", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QT_HazeRemvalClass: public Ui_QT_HazeRemvalClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_HAZEREMVAL_H
