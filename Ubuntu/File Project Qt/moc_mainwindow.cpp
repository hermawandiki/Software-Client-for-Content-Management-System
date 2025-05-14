/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10MainWindowE = QtMocHelpers::stringData(
    "MainWindow",
    "clearAllFocus",
    "",
    "on_btnExit_released",
    "on_btnReset_released",
    "on_btnSetIP_clicked",
    "onMediaFinished",
    "QMediaPlayer::MediaStatus",
    "status",
    "updateStatus",
    "videoID",
    "filename",
    "fetchVideoList",
    "parseVideoList",
    "data",
    "downloadFile",
    "id",
    "parseCSV",
    "filePath",
    "downloadAllVideos",
    "playVideo",
    "filepath",
    "playSelectedVideo",
    "onDownloadFinished",
    "checkSchedule",
    "first",
    "last",
    "updateData",
    "addLog",
    "message",
    "mainLoop",
    "runModeA",
    "runModeB",
    "runModeDefault"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10MainWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  140,    2, 0x08,    1 /* Private */,
       3,    0,  141,    2, 0x08,    2 /* Private */,
       4,    0,  142,    2, 0x08,    3 /* Private */,
       5,    0,  143,    2, 0x08,    4 /* Private */,
       6,    1,  144,    2, 0x08,    5 /* Private */,
       9,    2,  147,    2, 0x08,    7 /* Private */,
      12,    0,  152,    2, 0x08,   10 /* Private */,
      13,    1,  153,    2, 0x08,   11 /* Private */,
      15,    1,  156,    2, 0x08,   13 /* Private */,
      17,    1,  159,    2, 0x08,   15 /* Private */,
      19,    0,  162,    2, 0x08,   17 /* Private */,
      20,    1,  163,    2, 0x08,   18 /* Private */,
      22,    0,  166,    2, 0x08,   20 /* Private */,
      23,    0,  167,    2, 0x08,   21 /* Private */,
      24,    2,  168,    2, 0x08,   22 /* Private */,
      27,    0,  173,    2, 0x08,   25 /* Private */,
      28,    1,  174,    2, 0x08,   26 /* Private */,
      30,    0,  177,    2, 0x08,   28 /* Private */,
      31,    0,  178,    2, 0x08,   29 /* Private */,
      32,    0,  179,    2, 0x08,   30 /* Private */,
      33,    0,  180,    2, 0x08,   31 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDateTime, QMetaType::QDateTime,   25,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN10MainWindowE.offsetsAndSizes,
    qt_meta_data_ZN10MainWindowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10MainWindowE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'clearAllFocus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnExit_released'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnReset_released'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnSetIP_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMediaFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMediaPlayer::MediaStatus, std::false_type>,
        // method 'updateStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'fetchVideoList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'parseVideoList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'downloadFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'parseCSV'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'downloadAllVideos'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playVideo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'playSelectedVideo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDownloadFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkSchedule'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDateTime &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDateTime &, std::false_type>,
        // method 'updateData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addLog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'mainLoop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'runModeA'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'runModeB'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'runModeDefault'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->clearAllFocus(); break;
        case 1: _t->on_btnExit_released(); break;
        case 2: _t->on_btnReset_released(); break;
        case 3: _t->on_btnSetIP_clicked(); break;
        case 4: _t->onMediaFinished((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 5: _t->updateStatus((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->fetchVideoList(); break;
        case 7: _t->parseVideoList((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 8: _t->downloadFile((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->parseCSV((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->downloadAllVideos(); break;
        case 11: _t->playVideo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->playSelectedVideo(); break;
        case 13: _t->onDownloadFinished(); break;
        case 14: _t->checkSchedule((*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QDateTime>>(_a[2]))); break;
        case 15: _t->updateData(); break;
        case 16: _t->addLog((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->mainLoop(); break;
        case 18: _t->runModeA(); break;
        case 19: _t->runModeB(); break;
        case 20: _t->runModeDefault(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10MainWindowE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 21;
    }
    return _id;
}
QT_WARNING_POP
