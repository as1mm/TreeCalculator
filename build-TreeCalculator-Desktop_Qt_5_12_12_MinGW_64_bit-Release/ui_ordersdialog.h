/********************************************************************************
** Form generated from reading UI file 'ordersdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERSDIALOG_H
#define UI_ORDERSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrdersDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tblOrders;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnCreate;
    QPushButton *btnOpen;
    QPushButton *btnDelete;
    QPushButton *btnClose;

    void setupUi(QDialog *OrdersDialog)
    {
        if (OrdersDialog->objectName().isEmpty())
            OrdersDialog->setObjectName(QString::fromUtf8("OrdersDialog"));
        OrdersDialog->resize(435, 323);
        widget = new QWidget(OrdersDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 10, 381, 291));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tblOrders = new QTableWidget(widget);
        if (tblOrders->columnCount() < 3)
            tblOrders->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblOrders->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblOrders->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblOrders->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tblOrders->setObjectName(QString::fromUtf8("tblOrders"));

        verticalLayout->addWidget(tblOrders);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnCreate = new QPushButton(widget);
        btnCreate->setObjectName(QString::fromUtf8("btnCreate"));

        horizontalLayout->addWidget(btnCreate);

        btnOpen = new QPushButton(widget);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));

        horizontalLayout->addWidget(btnOpen);

        btnDelete = new QPushButton(widget);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));

        horizontalLayout->addWidget(btnDelete);

        btnClose = new QPushButton(widget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        horizontalLayout->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(OrdersDialog);

        QMetaObject::connectSlotsByName(OrdersDialog);
    } // setupUi

    void retranslateUi(QDialog *OrdersDialog)
    {
        OrdersDialog->setWindowTitle(QApplication::translate("OrdersDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tblOrders->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("OrdersDialog", "\320\227\320\260\320\272\320\260\320\267\321\207\320\270\320\272", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tblOrders->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("OrdersDialog", "\320\224\320\260\321\202\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tblOrders->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("OrdersDialog", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
        btnCreate->setText(QApplication::translate("OrdersDialog", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        btnOpen->setText(QApplication::translate("OrdersDialog", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        btnDelete->setText(QApplication::translate("OrdersDialog", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        btnClose->setText(QApplication::translate("OrdersDialog", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrdersDialog: public Ui_OrdersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERSDIALOG_H
