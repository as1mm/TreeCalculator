/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QComboBox *cmbSpecies;
    QDoubleSpinBox *sbDiameter;
    QLabel *label_3;
    QDoubleSpinBox *sbHeight;
    QPushButton *btnCalculate;
    QLabel *lblResult;
    QTableWidget *tblRecords;
    QPushButton *btnAddToReport;
    QPushButton *btnDeleteRecord;
    QLabel *lblTotal;
    QLabel *label_2;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(803, 559);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 30, 43, 16));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setAlignment(Qt::AlignCenter);
        cmbSpecies = new QComboBox(centralwidget);
        cmbSpecies->setObjectName(QString::fromUtf8("cmbSpecies"));
        cmbSpecies->setGeometry(QRect(110, 60, 75, 24));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cmbSpecies->sizePolicy().hasHeightForWidth());
        cmbSpecies->setSizePolicy(sizePolicy2);
        cmbSpecies->setLayoutDirection(Qt::LeftToRight);
        sbDiameter = new QDoubleSpinBox(centralwidget);
        sbDiameter->setObjectName(QString::fromUtf8("sbDiameter"));
        sbDiameter->setGeometry(QRect(350, 60, 64, 25));
        sizePolicy2.setHeightForWidth(sbDiameter->sizePolicy().hasHeightForWidth());
        sbDiameter->setSizePolicy(sizePolicy2);
        sbDiameter->setDecimals(1);
        sbDiameter->setMaximum(300.000000000000000);
        sbDiameter->setSingleStep(0.500000000000000);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(580, 30, 58, 16));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setAlignment(Qt::AlignCenter);
        sbHeight = new QDoubleSpinBox(centralwidget);
        sbHeight->setObjectName(QString::fromUtf8("sbHeight"));
        sbHeight->setGeometry(QRect(580, 60, 64, 25));
        sizePolicy2.setHeightForWidth(sbHeight->sizePolicy().hasHeightForWidth());
        sbHeight->setSizePolicy(sizePolicy2);
        sbHeight->setDecimals(1);
        sbHeight->setSingleStep(0.500000000000000);
        btnCalculate = new QPushButton(centralwidget);
        btnCalculate->setObjectName(QString::fromUtf8("btnCalculate"));
        btnCalculate->setGeometry(QRect(340, 100, 80, 25));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnCalculate->sizePolicy().hasHeightForWidth());
        btnCalculate->setSizePolicy(sizePolicy3);
        lblResult = new QLabel(centralwidget);
        lblResult->setObjectName(QString::fromUtf8("lblResult"));
        lblResult->setGeometry(QRect(370, 140, 16, 16));
        sizePolicy1.setHeightForWidth(lblResult->sizePolicy().hasHeightForWidth());
        lblResult->setSizePolicy(sizePolicy1);
        lblResult->setAlignment(Qt::AlignCenter);
        tblRecords = new QTableWidget(centralwidget);
        if (tblRecords->columnCount() < 6)
            tblRecords->setColumnCount(6);
        tblRecords->setObjectName(QString::fromUtf8("tblRecords"));
        tblRecords->setGeometry(QRect(240, 180, 256, 192));
        tblRecords->setRowCount(0);
        tblRecords->setColumnCount(6);
        btnAddToReport = new QPushButton(centralwidget);
        btnAddToReport->setObjectName(QString::fromUtf8("btnAddToReport"));
        btnAddToReport->setGeometry(QRect(90, 410, 143, 25));
        sizePolicy3.setHeightForWidth(btnAddToReport->sizePolicy().hasHeightForWidth());
        btnAddToReport->setSizePolicy(sizePolicy3);
        btnDeleteRecord = new QPushButton(centralwidget);
        btnDeleteRecord->setObjectName(QString::fromUtf8("btnDeleteRecord"));
        btnDeleteRecord->setGeometry(QRect(520, 420, 140, 25));
        sizePolicy3.setHeightForWidth(btnDeleteRecord->sizePolicy().hasHeightForWidth());
        btnDeleteRecord->setSizePolicy(sizePolicy3);
        lblTotal = new QLabel(centralwidget);
        lblTotal->setObjectName(QString::fromUtf8("lblTotal"));
        lblTotal->setGeometry(QRect(310, 460, 115, 16));
        sizePolicy1.setHeightForWidth(lblTotal->sizePolicy().hasHeightForWidth());
        lblTotal->setSizePolicy(sizePolicy1);
        lblTotal->setFocusPolicy(Qt::NoFocus);
        lblTotal->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(350, 30, 73, 16));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 803, 25));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\320\276\320\264\320\260", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\201\320\276\321\202\320\260, \320\274", nullptr));
        btnCalculate->setText(QApplication::translate("MainWindow", "\320\240\320\260\321\201\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
        lblResult->setText(QString());
        btnAddToReport->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\262 \320\262\320\265\320\264\320\276\320\274\320\276\321\201\321\202\321\214", nullptr));
        btnDeleteRecord->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\270\320\267 \320\262\320\265\320\264\320\276\320\274\320\276\321\201\321\202\320\270", nullptr));
        lblTotal->setText(QApplication::translate("MainWindow", "\320\236\320\261\321\211\320\270\320\271 \320\276\320\261\321\212\321\221\320\274: 0 \320\274\302\263", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\224\320\270\320\260\320\274\320\265\321\202\321\200, \321\201\320\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
