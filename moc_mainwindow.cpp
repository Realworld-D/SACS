/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      26,   11,   11,   11, 0x0a,
      39,   11,   11,   11, 0x08,
      58,   50,   11,   11, 0x08,
      77,   11,   11,   11, 0x08,
     100,   11,   11,   11, 0x08,
     123,   11,   11,   11, 0x08,
     146,   11,   11,   11, 0x08,
     169,   11,   11,   11, 0x08,
     192,   11,   11,   11, 0x08,
     215,   11,   11,   11, 0x08,
     238,   11,   11,   11, 0x08,
     269,   11,   11,   11, 0x08,
     305,  299,   11,   11, 0x08,
     353,   11,   11,   11, 0x08,
     391,   11,   11,   11, 0x08,
     424,   11,   11,   11, 0x08,
     457,   11,   11,   11, 0x08,
     489,   11,   11,   11, 0x08,
     522,   11,   11,   11, 0x08,
     552,   11,   11,   11, 0x08,
     583,   11,   11,   11, 0x08,
     614,   11,   11,   11, 0x08,
     647,   11,   11,   11, 0x08,
     677,   11,   11,   11, 0x08,
     708,   11,   11,   11, 0x08,
     738,   11,   11,   11, 0x08,
     766,  299,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0updateImage()\0updatetime()\0"
    "initForm()\0qssFile\0loadStyle(QString)\0"
    "on_action1_triggered()\0on_action2_triggered()\0"
    "on_action3_triggered()\0on_action4_triggered()\0"
    "on_action5_triggered()\0on_action6_triggered()\0"
    "on_action7_triggered()\0"
    "on_pushButton_camera_clicked()\0"
    "on_pushButton_photo_clicked()\0index\0"
    "on_comboBox_confidence_currentIndexChanged(int)\0"
    "on_pushButton_setconfidence_clicked()\0"
    "on_pushButton_camera_2_clicked()\0"
    "on_pushButton_getphoto_clicked()\0"
    "on_pushButton_photo_2_clicked()\0"
    "on_pushButton_register_clicked()\0"
    "on_pushButton_query_clicked()\0"
    "on_pushButton_delete_clicked()\0"
    "on_pushButton_update_clicked()\0"
    "on_pushButton_queryall_clicked()\0"
    "on_pushButton_today_clicked()\0"
    "on_pushButton_people_clicked()\0"
    "on_pushButton_green_clicked()\0"
    "on_pushButton_red_clicked()\0"
    "on_tableView_2_doubleClicked(QModelIndex)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->updateImage(); break;
        case 1: _t->updatetime(); break;
        case 2: _t->initForm(); break;
        case 3: _t->loadStyle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_action1_triggered(); break;
        case 5: _t->on_action2_triggered(); break;
        case 6: _t->on_action3_triggered(); break;
        case 7: _t->on_action4_triggered(); break;
        case 8: _t->on_action5_triggered(); break;
        case 9: _t->on_action6_triggered(); break;
        case 10: _t->on_action7_triggered(); break;
        case 11: _t->on_pushButton_camera_clicked(); break;
        case 12: _t->on_pushButton_photo_clicked(); break;
        case 13: _t->on_comboBox_confidence_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_pushButton_setconfidence_clicked(); break;
        case 15: _t->on_pushButton_camera_2_clicked(); break;
        case 16: _t->on_pushButton_getphoto_clicked(); break;
        case 17: _t->on_pushButton_photo_2_clicked(); break;
        case 18: _t->on_pushButton_register_clicked(); break;
        case 19: _t->on_pushButton_query_clicked(); break;
        case 20: _t->on_pushButton_delete_clicked(); break;
        case 21: _t->on_pushButton_update_clicked(); break;
        case 22: _t->on_pushButton_queryall_clicked(); break;
        case 23: _t->on_pushButton_today_clicked(); break;
        case 24: _t->on_pushButton_people_clicked(); break;
        case 25: _t->on_pushButton_green_clicked(); break;
        case 26: _t->on_pushButton_red_clicked(); break;
        case 27: _t->on_tableView_2_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
