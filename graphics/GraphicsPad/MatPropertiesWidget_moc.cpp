/****************************************************************************
** Meta object code from reading C++ file 'MatPropertiesWidget.h'
**
** Created: Mon Apr 23 18:40:24 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MatPropertiesWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MatPropertiesWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MatPropertiesWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x08,
      34,   20,   20,   20, 0x08,
      47,   20,   20,   20, 0x08,
      60,   20,   20,   20, 0x08,
      73,   20,   20,   20, 0x08,
      89,   20,   20,   20, 0x08,
     105,   20,   20,   20, 0x08,
     121,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MatPropertiesWidget[] = {
    "MatPropertiesWidget\0\0_KaChanged()\0"
    "_KdChanged()\0_KsChanged()\0_NsChanged()\0"
    "_mapKaChanged()\0_mapKdChanged()\0"
    "_mapKsChanged()\0_ShaderChanged()\0"
};

void MatPropertiesWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MatPropertiesWidget *_t = static_cast<MatPropertiesWidget *>(_o);
        switch (_id) {
        case 0: _t->_KaChanged(); break;
        case 1: _t->_KdChanged(); break;
        case 2: _t->_KsChanged(); break;
        case 3: _t->_NsChanged(); break;
        case 4: _t->_mapKaChanged(); break;
        case 5: _t->_mapKdChanged(); break;
        case 6: _t->_mapKsChanged(); break;
        case 7: _t->_ShaderChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MatPropertiesWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MatPropertiesWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MatPropertiesWidget,
      qt_meta_data_MatPropertiesWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MatPropertiesWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MatPropertiesWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MatPropertiesWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MatPropertiesWidget))
        return static_cast<void*>(const_cast< MatPropertiesWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MatPropertiesWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
