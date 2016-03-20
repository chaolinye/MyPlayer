/****************************************************************************
** Meta object code from reading C++ file 'controlwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyPlayer/controlwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ControlWidget_t {
    QByteArrayData data[18];
    char stringdata[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ControlWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ControlWidget_t qt_meta_stringdata_ControlWidget = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 4),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 5),
QT_MOC_LITERAL(4, 26, 4),
QT_MOC_LITERAL(5, 31, 4),
QT_MOC_LITERAL(6, 36, 4),
QT_MOC_LITERAL(7, 41, 6),
QT_MOC_LITERAL(8, 48, 13),
QT_MOC_LITERAL(9, 62, 10),
QT_MOC_LITERAL(10, 73, 9),
QT_MOC_LITERAL(11, 83, 5),
QT_MOC_LITERAL(12, 89, 17),
QT_MOC_LITERAL(13, 107, 6),
QT_MOC_LITERAL(14, 114, 8),
QT_MOC_LITERAL(15, 123, 10),
QT_MOC_LITERAL(16, 134, 14),
QT_MOC_LITERAL(17, 149, 1)
    },
    "ControlWidget\0play\0\0pause\0stop\0fast\0"
    "time\0rewind\0currentVolume\0startVedio\0"
    "stopVedio\0quiet\0setTimeSliderLong\0"
    "timing\0sendFast\0sendRewind\0setWidgetState\0"
    "b\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06,
       3,    0,   85,    2, 0x06,
       4,    0,   86,    2, 0x06,
       5,    1,   87,    2, 0x06,
       7,    1,   90,    2, 0x06,
       8,    1,   93,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       9,    0,   96,    2, 0x0a,
      10,    0,   97,    2, 0x0a,
      11,    0,   98,    2, 0x0a,
      12,    1,   99,    2, 0x0a,
      13,    0,  102,    2, 0x0a,
      14,    0,  103,    2, 0x0a,
      15,    0,  104,    2, 0x0a,
      16,    1,  105,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   17,

       0        // eod
};

void ControlWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ControlWidget *_t = static_cast<ControlWidget *>(_o);
        switch (_id) {
        case 0: _t->play(); break;
        case 1: _t->pause(); break;
        case 2: _t->stop(); break;
        case 3: _t->fast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->rewind((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->currentVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->startVedio(); break;
        case 7: _t->stopVedio(); break;
        case 8: _t->quiet(); break;
        case 9: _t->setTimeSliderLong((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->timing(); break;
        case 11: _t->sendFast(); break;
        case 12: _t->sendRewind(); break;
        case 13: _t->setWidgetState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ControlWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlWidget::play)) {
                *result = 0;
            }
        }
        {
            typedef void (ControlWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlWidget::pause)) {
                *result = 1;
            }
        }
        {
            typedef void (ControlWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlWidget::stop)) {
                *result = 2;
            }
        }
        {
            typedef void (ControlWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlWidget::fast)) {
                *result = 3;
            }
        }
        {
            typedef void (ControlWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlWidget::rewind)) {
                *result = 4;
            }
        }
        {
            typedef void (ControlWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlWidget::currentVolume)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject ControlWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ControlWidget.data,
      qt_meta_data_ControlWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *ControlWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ControlWidget.stringdata))
        return static_cast<void*>(const_cast< ControlWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ControlWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void ControlWidget::play()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ControlWidget::pause()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ControlWidget::stop()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ControlWidget::fast(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ControlWidget::rewind(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ControlWidget::currentVolume(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
