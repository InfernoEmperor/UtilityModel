/****************************************************************************
** Meta object code from reading C++ file 'buildsensor.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../buildsensor.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buildsensor.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BuildSensor_t {
    QByteArrayData data[11];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BuildSensor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BuildSensor_t qt_meta_stringdata_BuildSensor = {
    {
QT_MOC_LITERAL(0, 0, 11), // "BuildSensor"
QT_MOC_LITERAL(1, 12, 9), // "AddSensor"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "DeleteSensor"
QT_MOC_LITERAL(4, 36, 8), // "Btncombo"
QT_MOC_LITERAL(5, 45, 5), // "UrlOk"
QT_MOC_LITERAL(6, 51, 7), // "OpenHis"
QT_MOC_LITERAL(7, 59, 9), // "DeleteHis"
QT_MOC_LITERAL(8, 69, 8), // "DataSave"
QT_MOC_LITERAL(9, 78, 10), // "UpdateData"
QT_MOC_LITERAL(10, 89, 8) // "SetTimer"

    },
    "BuildSensor\0AddSensor\0\0DeleteSensor\0"
    "Btncombo\0UrlOk\0OpenHis\0DeleteHis\0"
    "DataSave\0UpdateData\0SetTimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BuildSensor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BuildSensor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BuildSensor *_t = static_cast<BuildSensor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddSensor(); break;
        case 1: _t->DeleteSensor(); break;
        case 2: _t->Btncombo(); break;
        case 3: _t->UrlOk(); break;
        case 4: _t->OpenHis(); break;
        case 5: _t->DeleteHis(); break;
        case 6: _t->DataSave(); break;
        case 7: _t->UpdateData(); break;
        case 8: _t->SetTimer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject BuildSensor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BuildSensor.data,
      qt_meta_data_BuildSensor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BuildSensor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BuildSensor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BuildSensor.stringdata0))
        return static_cast<void*>(const_cast< BuildSensor*>(this));
    return QWidget::qt_metacast(_clname);
}

int BuildSensor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
