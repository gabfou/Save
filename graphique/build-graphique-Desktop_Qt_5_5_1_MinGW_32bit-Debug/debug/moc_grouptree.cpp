/****************************************************************************
** Meta object code from reading C++ file 'grouptree.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../graphique/grouptree.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'grouptree.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_grouptree_t {
    QByteArrayData data[11];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_grouptree_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_grouptree_t qt_meta_stringdata_grouptree = {
    {
QT_MOC_LITERAL(0, 0, 9), // "grouptree"
QT_MOC_LITERAL(1, 10, 14), // "supgroupintree"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 17), // "contextmenuselect"
QT_MOC_LITERAL(4, 44, 14), // "addgroupintree"
QT_MOC_LITERAL(5, 59, 15), // "addgroupintree2"
QT_MOC_LITERAL(6, 75, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(7, 92, 4), // "item"
QT_MOC_LITERAL(8, 97, 6), // "column"
QT_MOC_LITERAL(9, 104, 15), // "addquestintree2"
QT_MOC_LITERAL(10, 120, 14) // "addquestintree"

    },
    "grouptree\0supgroupintree\0\0contextmenuselect\0"
    "addgroupintree\0addgroupintree2\0"
    "QTreeWidgetItem*\0item\0column\0"
    "addquestintree2\0addquestintree"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_grouptree[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    2,   47,    2, 0x08 /* Private */,
       9,    2,   52,    2, 0x08 /* Private */,
      10,    0,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    8,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    8,
    QMetaType::Void,

       0        // eod
};

void grouptree::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        grouptree *_t = static_cast<grouptree *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->supgroupintree(); break;
        case 1: _t->contextmenuselect(); break;
        case 2: _t->addgroupintree(); break;
        case 3: _t->addgroupintree2((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->addquestintree2((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->addquestintree(); break;
        default: ;
        }
    }
}

const QMetaObject grouptree::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_grouptree.data,
      qt_meta_data_grouptree,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *grouptree::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *grouptree::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_grouptree.stringdata0))
        return static_cast<void*>(const_cast< grouptree*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int grouptree::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
