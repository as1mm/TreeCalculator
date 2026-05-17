/********************************************************************************
** Form generated from reading UI file 'speciesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPECIESDIALOG_H
#define UI_SPECIESDIALOG_H

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

class Ui_SpeciesDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tblSpecies;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnReset;

    void setupUi(QDialog *SpeciesDialog)
    {
        if (SpeciesDialog->objectName().isEmpty())
            SpeciesDialog->setObjectName(QString::fromUtf8("SpeciesDialog"));
        SpeciesDialog->resize(434, 328);
        widget = new QWidget(SpeciesDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(31, 41, 373, 228));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tblSpecies = new QTableWidget(widget);
        if (tblSpecies->columnCount() < 2)
            tblSpecies->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        tblSpecies->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblSpecies->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tblSpecies->setObjectName(QString::fromUtf8("tblSpecies"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tblSpecies->sizePolicy().hasHeightForWidth());
        tblSpecies->setSizePolicy(sizePolicy);
        tblSpecies->setMinimumSize(QSize(371, 0));
        tblSpecies->setMaximumSize(QSize(16777215, 16777215));
        tblSpecies->setLayoutDirection(Qt::LeftToRight);
        tblSpecies->setAutoFillBackground(false);
        tblSpecies->setSelectionMode(QAbstractItemView::SingleSelection);
        tblSpecies->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblSpecies->setColumnCount(2);
        tblSpecies->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(tblSpecies);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnAdd = new QPushButton(widget);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnAdd->sizePolicy().hasHeightForWidth());
        btnAdd->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(btnAdd);

        btnDelete = new QPushButton(widget);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));
        sizePolicy1.setHeightForWidth(btnDelete->sizePolicy().hasHeightForWidth());
        btnDelete->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(btnDelete);

        btnReset = new QPushButton(widget);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));
        sizePolicy1.setHeightForWidth(btnReset->sizePolicy().hasHeightForWidth());
        btnReset->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(btnReset);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SpeciesDialog);

        QMetaObject::connectSlotsByName(SpeciesDialog);
    } // setupUi

    void retranslateUi(QDialog *SpeciesDialog)
    {
        SpeciesDialog->setWindowTitle(QApplication::translate("SpeciesDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tblSpecies->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SpeciesDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tblSpecies->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SpeciesDialog", "\320\222\320\270\320\264\320\276\320\262\320\276\320\265 \321\207\320\270\321\201\320\273\320\276", nullptr));
        btnAdd->setText(QApplication::translate("SpeciesDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnDelete->setText(QApplication::translate("SpeciesDialog", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        btnReset->setText(QApplication::translate("SpeciesDialog", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214 \320\264\320\276 \321\201\321\202\320\260\320\275\320\264\320\260\321\200\321\202\320\275\321\213\321\205", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpeciesDialog: public Ui_SpeciesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPECIESDIALOG_H
