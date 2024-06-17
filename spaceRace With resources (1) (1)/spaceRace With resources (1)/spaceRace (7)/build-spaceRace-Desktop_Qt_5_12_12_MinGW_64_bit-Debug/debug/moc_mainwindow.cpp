/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../spaceRace/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[340];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "showMainMenu"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 19), // "showMultiplayerMenu"
QT_MOC_LITERAL(4, 45, 12), // "showHostMenu"
QT_MOC_LITERAL(5, 58, 12), // "showJoinMenu"
QT_MOC_LITERAL(6, 71, 9), // "startGame"
QT_MOC_LITERAL(7, 81, 20), // "startMultiplayerGame"
QT_MOC_LITERAL(8, 102, 21), // "changeBackgroundMusic"
QT_MOC_LITERAL(9, 124, 8), // "filePath"
QT_MOC_LITERAL(10, 133, 20), // "playButtonClickSound"
QT_MOC_LITERAL(11, 154, 21), // "removeBackgroundImage"
QT_MOC_LITERAL(12, 176, 12), // "acceptPlayer"
QT_MOC_LITERAL(13, 189, 6), // "player"
QT_MOC_LITERAL(14, 196, 12), // "rejectPlayer"
QT_MOC_LITERAL(15, 209, 26), // "onHandshakeRequestReceived"
QT_MOC_LITERAL(16, 236, 13), // "clientAddress"
QT_MOC_LITERAL(17, 250, 19), // "onHandshakeAccepted"
QT_MOC_LITERAL(18, 270, 8), // "codeword"
QT_MOC_LITERAL(19, 279, 19), // "onHandshakeRejected"
QT_MOC_LITERAL(20, 299, 17), // "onConnectionError"
QT_MOC_LITERAL(21, 317, 7), // "message"
QT_MOC_LITERAL(22, 325, 14) // "onDisconnected"

    },
    "MainWindow\0showMainMenu\0\0showMultiplayerMenu\0"
    "showHostMenu\0showJoinMenu\0startGame\0"
    "startMultiplayerGame\0changeBackgroundMusic\0"
    "filePath\0playButtonClickSound\0"
    "removeBackgroundImage\0acceptPlayer\0"
    "player\0rejectPlayer\0onHandshakeRequestReceived\0"
    "clientAddress\0onHandshakeAccepted\0"
    "codeword\0onHandshakeRejected\0"
    "onConnectionError\0message\0onDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    1,  100,    2, 0x08 /* Private */,
      10,    0,  103,    2, 0x08 /* Private */,
      11,    0,  104,    2, 0x08 /* Private */,
      12,    1,  105,    2, 0x08 /* Private */,
      14,    1,  108,    2, 0x08 /* Private */,
      15,    1,  111,    2, 0x08 /* Private */,
      17,    1,  114,    2, 0x08 /* Private */,
      19,    0,  117,    2, 0x08 /* Private */,
      20,    1,  118,    2, 0x08 /* Private */,
      22,    1,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showMainMenu(); break;
        case 1: _t->showMultiplayerMenu(); break;
        case 2: _t->showHostMenu(); break;
        case 3: _t->showJoinMenu(); break;
        case 4: _t->startGame(); break;
        case 5: _t->startMultiplayerGame(); break;
        case 6: _t->changeBackgroundMusic((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->playButtonClickSound(); break;
        case 8: _t->removeBackgroundImage(); break;
        case 9: _t->acceptPlayer((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->rejectPlayer((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->onHandshakeRequestReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->onHandshakeAccepted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->onHandshakeRejected(); break;
        case 14: _t->onConnectionError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->onDisconnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
