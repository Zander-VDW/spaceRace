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
    QByteArrayData data[22];
    char stringdata0[319];
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
QT_MOC_LITERAL(7, 81, 21), // "changeBackgroundMusic"
QT_MOC_LITERAL(8, 103, 8), // "filePath"
QT_MOC_LITERAL(9, 112, 20), // "playButtonClickSound"
QT_MOC_LITERAL(10, 133, 21), // "removeBackgroundImage"
QT_MOC_LITERAL(11, 155, 12), // "acceptPlayer"
QT_MOC_LITERAL(12, 168, 6), // "player"
QT_MOC_LITERAL(13, 175, 12), // "rejectPlayer"
QT_MOC_LITERAL(14, 188, 26), // "onHandshakeRequestReceived"
QT_MOC_LITERAL(15, 215, 13), // "clientAddress"
QT_MOC_LITERAL(16, 229, 19), // "onHandshakeAccepted"
QT_MOC_LITERAL(17, 249, 8), // "codeword"
QT_MOC_LITERAL(18, 258, 19), // "onHandshakeRejected"
QT_MOC_LITERAL(19, 278, 17), // "onConnectionError"
QT_MOC_LITERAL(20, 296, 7), // "message"
QT_MOC_LITERAL(21, 304, 14) // "onDisconnected"

    },
    "MainWindow\0showMainMenu\0\0showMultiplayerMenu\0"
    "showHostMenu\0showJoinMenu\0startGame\0"
    "changeBackgroundMusic\0filePath\0"
    "playButtonClickSound\0removeBackgroundImage\0"
    "acceptPlayer\0player\0rejectPlayer\0"
    "onHandshakeRequestReceived\0clientAddress\0"
    "onHandshakeAccepted\0codeword\0"
    "onHandshakeRejected\0onConnectionError\0"
    "message\0onDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    1,   94,    2, 0x08 /* Private */,
       9,    0,   97,    2, 0x08 /* Private */,
      10,    0,   98,    2, 0x08 /* Private */,
      11,    1,   99,    2, 0x08 /* Private */,
      13,    1,  102,    2, 0x08 /* Private */,
      14,    1,  105,    2, 0x08 /* Private */,
      16,    1,  108,    2, 0x08 /* Private */,
      18,    0,  111,    2, 0x08 /* Private */,
      19,    1,  112,    2, 0x08 /* Private */,
      21,    1,  115,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::QString,   20,

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
        case 5: _t->changeBackgroundMusic((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->playButtonClickSound(); break;
        case 7: _t->removeBackgroundImage(); break;
        case 8: _t->acceptPlayer((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->rejectPlayer((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->onHandshakeRequestReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->onHandshakeAccepted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->onHandshakeRejected(); break;
        case 13: _t->onConnectionError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->onDisconnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
