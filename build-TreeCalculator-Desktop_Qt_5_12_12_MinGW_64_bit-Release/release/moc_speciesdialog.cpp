/****************************************************************************
** Meta object code from reading C++ file 'speciesdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TreeCalculator/speciesdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'speciesdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SpeciesDialog_t {
    QByteArrayData data[10];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpeciesDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpeciesDialog_t qt_meta_stringdata_SpeciesDialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SpeciesDialog"
QT_MOC_LITERAL(1, 14, 14), // "speciesChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 14), // "btnAdd_clicked"
QT_MOC_LITERAL(4, 45, 17), // "btnDelete_clicked"
QT_MOC_LITERAL(5, 63, 16), // "btnReset_clicked"
QT_MOC_LITERAL(6, 80, 11), // "cellChanged"
QT_MOC_LITERAL(7, 92, 3), // "row"
QT_MOC_LITERAL(8, 96, 6), // "column"
QT_MOC_LITERAL(9, 103, 16) // "loadSpeciesTable"

    },
    "SpeciesDialog\0speciesChanged\0\0"
    "btnAdd_clicked\0btnDelete_clicked\0"
    "btnReset_clicked\0cellChanged\0row\0"
    "column\0loadSpeciesTable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpeciesDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    2,   48,    2, 0x08 /* Private */,
       9,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void,

       0        // eod
};

void SpeciesDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SpeciesDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->speciesChanged(); break;
        case 1: _t->btnAdd_clicked(); break;
        case 2: _t->btnDelete_clicked(); break;
        case 3: _t->btnReset_clicked(); break;
        case 4: _t->cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->loadSpeciesTable(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SpeciesDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SpeciesDialog::speciesChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SpeciesDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_SpeciesDialog.data,
    qt_meta_data_SpeciesDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SpeciesDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpeciesDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SpeciesDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SpeciesDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SpeciesDialog::speciesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
