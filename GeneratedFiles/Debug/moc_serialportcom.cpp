/****************************************************************************
** Meta object code from reading C++ file 'serialportcom.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../serialportcom.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialportcom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SerialPortCom[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   15,   14,   14, 0x05,
      44,   14,   14,   14, 0x05,
      61,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      81,   14,   14,   14, 0x08,
      94,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SerialPortCom[] = {
    "SerialPortCom\0\0my\0readyRead(SerialPortCom*)\0"
    "abnormalReturn()\0sendMsg(QByteArray)\0"
    "_readyRead()\0_timeOut()\0"
};

void SerialPortCom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SerialPortCom *_t = static_cast<SerialPortCom *>(_o);
        switch (_id) {
        case 0: _t->readyRead((*reinterpret_cast< SerialPortCom*(*)>(_a[1]))); break;
        case 1: _t->abnormalReturn(); break;
        case 2: _t->sendMsg((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->_readyRead(); break;
        case 4: _t->_timeOut(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SerialPortCom::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SerialPortCom::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SerialPortCom,
      qt_meta_data_SerialPortCom, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SerialPortCom::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SerialPortCom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SerialPortCom::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SerialPortCom))
        return static_cast<void*>(const_cast< SerialPortCom*>(this));
    return QObject::qt_metacast(_clname);
}

int SerialPortCom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SerialPortCom::readyRead(SerialPortCom * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SerialPortCom::abnormalReturn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SerialPortCom::sendMsg(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
