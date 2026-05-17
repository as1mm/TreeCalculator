/********************************************************************************
** Form generated from reading UI file 'stockdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOCKDIALOG_H
#define UI_STOCKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StockDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tblStock;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnClose;

    void setupUi(QWidget *StockDialog)
    {
        if (StockDialog->objectName().isEmpty())
            StockDialog->setObjectName(QString::fromUtf8("StockDialog"));
        StockDialog->resize(459, 363);
        widget = new QWidget(StockDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(50, 20, 361, 311));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tblStock = new QTableWidget(widget);
        if (tblStock->columnCount() < 7)
            tblStock->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblStock->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblStock->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblStock->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tblStock->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tblStock->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tblStock->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tblStock->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tblStock->setObjectName(QString::fromUtf8("tblStock"));
        tblStock->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblStock->setSelectionMode(QAbstractItemView::SingleSelection);
        tblStock->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(tblStock);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnAdd = new QPushButton(widget);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        horizontalLayout->addWidget(btnAdd);

        btnDelete = new QPushButton(widget);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));

        horizontalLayout->addWidget(btnDelete);

        btnClose = new QPushButton(widget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        horizontalLayout->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(StockDialog);

        QMetaObject::connectSlotsByName(StockDialog);
    } // setupUi

    void retranslateUi(QWidget *StockDialog)
    {
        StockDialog->setWindowTitle(QApplication::translate("StockDialog", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tblStock->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("StockDialog", "\320\242\320\270\320\277", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tblStock->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("StockDialog", "\320\224\320\273\320\270\320\275\320\260 (\320\274\320\274)", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tblStock->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("StockDialog", "\320\250\320\270\321\200\320\270\320\275\320\260 (\320\274\320\274)", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tblStock->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("StockDialog", "\320\242\320\276\320\273\321\211\320\270\320\275\320\260 (\320\274\320\274)", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tblStock->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("StockDialog", "\320\236\320\261\321\212\321\221\320\274 \320\265\320\264. (\320\274\302\263)", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tblStock->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("StockDialog", "\320\232\320\276\320\273-\320\262\320\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tblStock->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("StockDialog", "\320\246\320\265\320\275\320\260 \320\267\320\260 \321\210\321\202", nullptr));
        btnAdd->setText(QApplication::translate("StockDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnDelete->setText(QApplication::translate("StockDialog", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        btnClose->setText(QApplication::translate("StockDialog", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StockDialog: public Ui_StockDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOCKDIALOG_H
