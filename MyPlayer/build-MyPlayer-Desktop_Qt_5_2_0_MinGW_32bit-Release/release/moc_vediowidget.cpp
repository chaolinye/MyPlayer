/****************************************************************************
** Meta object code from reading C++ file 'vediowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyPlayer/vediowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vediowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VedioWidget_t {
    QByteArrayData data[17];
    char stringdata[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_VedioWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_VedioWidget_t qt_meta_stringdata_VedioWidget = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 10),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 4),
QT_MOC_LITERAL(4, 29, 9),
QT_MOC_LITERAL(5, 39, 1),
QT_MOC_LITERAL(6, 41, 8),
QT_MOC_LITERAL(7, 50, 10),
QT_MOC_LITERAL(8, 61, 10),
QT_MOC_LITERAL(9, 72, 8),
QT_MOC_LITERAL(10, 81, 9),
QT_MOC_LITERAL(11, 91, 10),
QT_MOC_LITERAL(12, 102, 11),
QT_MOC_LITERAL(13, 114, 9),
QT_MOC_LITERAL(14, 124, 6),
QT_MOC_LITERAL(15, 131, 7),
QT_MOC_LITERAL(16, 139, 15)
    },
    "VedioWidget\0setSumTime\0\0time\0startPlay\0"
    "b\0fileName\0fullScreen\0startVedio\0"
    "fileOpen\0stopVedio\0pauseVedio\0resumeVedio\0"
    "setVolume\0volume\0setTime\0vedioChangeSize\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VedioWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06,
       4,    1,   72,    2, 0x06,
       6,    1,   75,    2, 0x06,
       7,    0,   78,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       8,    1,   79,    2, 0x0a,
      10,    0,   82,    2, 0x0a,
      11,    0,   83,    2, 0x0a,
      12,    0,   84,    2, 0x0a,
      13,    1,   85,    2, 0x0a,
      15,    1,   88,    2, 0x0a,
      16,    0,   91,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void VedioWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VedioWidget *_t = static_cast<VedioWidget *>(_o);
        switch (_id) {
        case 0: _t->setSumTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->startPlay((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->fileName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->fullScreen(); break;
        case 4: _t->startVedio((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->stopVedio(); break;
        case 6: _t->pauseVedio(); break;
        case 7: _t->resumeVedio(); break;
        case 8: _t->setVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->vedioChangeSize(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VedioWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VedioWidget::setSumTime)) {
                *result = 0;
            }
        }
        {
            typedef void (VedioWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VedioWidget::startPlay)) {
                *result = 1;
            }
        }
        {
            typedef void (VedioWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VedioWidget::fileName)) {
                *result = 2;
            }
        }
        {
            typedef void (VedioWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VedioWidget::fullScreen)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject VedioWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VedioWidget.data,
      qt_meta_data_VedioWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *VedioWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VedioWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VedioWidget.stringdata))
        return static_cast<void*>(const_cast< VedioWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int VedioWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void VedioWidget::setSumTime(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VedioWidget::startPlay(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VedioWidget::fileName(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VedioWidget::fullScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
