/********************************************************************************
** Form generated from reading UI file 'customersdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMERSDIALOG_H
#define UI_CUSTOMERSDIALOG_H

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

class Ui_CustomersDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tblCustomers;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnClose;

    void setupUi(QDialog *CustomersDialog)
    {
        if (CustomersDialog->objectName().isEmpty())
            CustomersDialog->setObjectName(QString::fromUtf8("CustomersDialog"));
        CustomersDialog->resize(420, 332);
        widget = new QWidget(CustomersDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 30, 350, 261));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tblCustomers = new QTableWidget(widget);
        if (tblCustomers->columnCount() < 3)
            tblCustomers->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblCustomers->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblCustomers->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblCustomers->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tblCustomers->setObjectName(QString::fromUtf8("tblCustomers"));

        verticalLayout->addWidget(tblCustomers);

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


        retranslateUi(CustomersDialog);

        QMetaObject::connectSlotsByName(CustomersDialog);
    } // setupUi

    void retranslateUi(QDialog *CustomersDialog)
    {
        CustomersDialog->setWindowTitle(QApplication::translate("CustomersDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tblCustomers->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CustomersDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tblCustomers->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CustomersDialog", "\320\223\320\276\321\200\320\276\320\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tblCustomers->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("CustomersDialog", "\320\220\320\264\321\200\320\265\321\201", nullptr));
        btnAdd->setText(QApplication::translate("CustomersDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnDelete->setText(QApplication::translate("CustomersDialog", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        btnClose->setText(QApplication::translate("CustomersDialog", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomersDialog: public Ui_CustomersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMERSDIALOG_H
