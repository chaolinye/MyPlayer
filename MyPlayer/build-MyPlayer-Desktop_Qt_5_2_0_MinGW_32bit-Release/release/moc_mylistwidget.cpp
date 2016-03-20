/****************************************************************************
** Meta object code from reading C++ file 'mylistwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyPlayer/mylistwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mylistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyListWidget_t {
    QByteArrayData data[10];
    char stringdata[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MyListWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MyListWidget_t qt_meta_stringdata_MyListWidget = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 12),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 7),
QT_MOC_LITERAL(4, 35, 8),
QT_MOC_LITERAL(5, 44, 6),
QT_MOC_LITERAL(6, 51, 16),
QT_MOC_LITERAL(7, 68, 4),
QT_MOC_LITERAL(8, 73, 9),
QT_MOC_LITERAL(9, 83, 9)
    },
    "MyListWidget\0sendFileName\0\0addFile\0"
    "fileName\0click2\0QListWidgetItem*\0item\0"
    "deleteOne\0deleteAll\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyListWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       3,    1,   42,    2, 0x0a,
       5,    1,   45,    2, 0x0a,
       8,    0,   48,    2, 0x0a,
       9,    0,   49,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyListWidget *_t = static_cast<MyListWidget *>(_o);
        switch (_id) {
        case 0: _t->sendFileName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->addFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->click2((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->deleteOne(); break;
        case 4: _t->deleteAll(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyListWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyListWidget::sendFileName)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject MyListWidget::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_MyListWidget.data,
      qt_meta_data_MyListWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *MyListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyListWidget.stringdata))
        return static_cast<void*>(const_cast< MyListWidget*>(this));
    return QListWidget::qt_metacast(_clname);
}

int MyListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MyListWidget::sendFileName(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
