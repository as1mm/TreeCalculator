/********************************************************************************
** Form generated from reading UI file 'orderdetaildialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERDETAILDIALOG_H
#define UI_ORDERDETAILDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrderDetailDialog
{
public:
    QLabel *lblCustomerInfo;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tblItems;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAddItem;
    QPushButton *btnDeleteItem;
    QPushButton *btnAllocate;
    QPushButton *btnClose;

    void setupUi(QDialog *OrderDetailDialog)
    {
        if (OrderDetailDialog->objectName().isEmpty())
            OrderDetailDialog->setObjectName(QString::fromUtf8("OrderDetailDialog"));
        OrderDetailDialog->resize(515, 378);
        lblCustomerInfo = new QLabel(OrderDetailDialog);
        lblCustomerInfo->setObjectName(QString::fromUtf8("lblCustomerInfo"));
        lblCustomerInfo->setGeometry(QRect(220, 20, 61, 21));
        widget = new QWidget(OrderDetailDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 50, 490, 281));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tblItems = new QTableWidget(widget);
        if (tblItems->columnCount() < 7)
            tblItems->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblItems->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblItems->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblItems->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tblItems->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tblItems->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tblItems->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tblItems->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tblItems->setObjectName(QString::fromUtf8("tblItems"));

        verticalLayout->addWidget(tblItems);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnAddItem = new QPushButton(widget);
        btnAddItem->setObjectName(QString::fromUtf8("btnAddItem"));

        horizontalLayout->addWidget(btnAddItem);

        btnDeleteItem = new QPushButton(widget);
        btnDeleteItem->setObjectName(QString::fromUtf8("btnDeleteItem"));

        horizontalLayout->addWidget(btnDeleteItem);

        btnAllocate = new QPushButton(widget);
        btnAllocate->setObjectName(QString::fromUtf8("btnAllocate"));

        horizontalLayout->addWidget(btnAllocate);

        btnClose = new QPushButton(widget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        horizontalLayout->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(OrderDetailDialog);

        QMetaObject::connectSlotsByName(OrderDetailDialog);
    } // setupUi

    void retranslateUi(QDialog *OrderDetailDialog)
    {
        OrderDetailDialog->setWindowTitle(QApplication::translate("OrderDetailDialog", "Dialog", nullptr));
        lblCustomerInfo->setText(QApplication::translate("OrderDetailDialog", "TextLabel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tblItems->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("OrderDetailDialog", "\320\237\320\276\321\200\320\276\320\264\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tblItems->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("OrderDetailDialog", "\320\242\320\270\320\277", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tblItems->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("OrderDetailDialog", "\320\224\320\273\320\270\320\275\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tblItems->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("OrderDetailDialog", "\320\250\320\270\321\200\320\270\320\275\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tblItems->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("OrderDetailDialog", "\320\242\320\276\320\273\321\211\320\270\320\275\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tblItems->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("OrderDetailDialog", "\320\235\321\203\320\266\320\275\320\276 \320\274\302\263", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tblItems->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("OrderDetailDialog", "\320\222\321\213\320\264\320\265\320\273\320\265\320\275\320\276 \320\274\302\263", nullptr));
        btnAddItem->setText(QApplication::translate("OrderDetailDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\277\320\276\320\267\320\270\321\206\320\270\321\216", nullptr));
        btnDeleteItem->setText(QApplication::translate("OrderDetailDialog", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\276\320\267\320\270\321\206\320\270\321\216", nullptr));
        btnAllocate->setText(QApplication::translate("OrderDetailDialog", "\320\240\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\270\321\202\321\214 \321\201\320\276 \321\201\320\272\320\273\320\260\320\264\320\260", nullptr));
        btnClose->setText(QApplication::translate("OrderDetailDialog", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderDetailDialog: public Ui_OrderDetailDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERDETAILDIALOG_H
