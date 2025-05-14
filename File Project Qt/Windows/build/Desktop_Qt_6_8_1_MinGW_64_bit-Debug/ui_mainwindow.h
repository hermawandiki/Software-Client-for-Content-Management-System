/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page_setting;
    QLineEdit *textIP;
    QPushButton *btnSetIP;
    QPushButton *btnReset;
    QTableWidget *tableVideo;
    QTableWidget *tableSchedule;
    QTextEdit *keterangan;
    QListWidget *listEntertainment;
    QPushButton *btnExit;
    QLabel *background;
    QLabel *date;
    QLabel *time;
    QWidget *page_video;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(15);
        font.setStyleStrategy(QFont::NoAntialias);
        MainWindow->setFont(font);
        MainWindow->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 1920, 1080));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        page_setting = new QWidget();
        page_setting->setObjectName("page_setting");
        page_setting->setStyleSheet(QString::fromUtf8(""));
        textIP = new QLineEdit(page_setting);
        textIP->setObjectName("textIP");
        textIP->setGeometry(QRect(45, 135, 296, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setKerning(false);
        textIP->setFont(font1);
        textIP->setStyleSheet(QString::fromUtf8("color: rgb(0, 51, 122);\n"
"background-color: rgb(240, 242, 245);"));
        textIP->setFrame(false);
        textIP->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btnSetIP = new QPushButton(page_setting);
        btnSetIP->setObjectName("btnSetIP");
        btnSetIP->setGeometry(QRect(370, 130, 161, 51));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Franklin Gothic")});
        font2.setPointSize(15);
        font2.setBold(true);
        font2.setStyleStrategy(QFont::NoAntialias);
        font2.setHintingPreference(QFont::PreferNoHinting);
        btnSetIP->setFont(font2);
        btnSetIP->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnSetIP->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        btnSetIP->setAutoFillBackground(false);
        btnSetIP->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border-radius:10px;\n"
"	color: rgb(242, 242, 242);\n"
"	background-color: rgb(0, 51, 122);\n"
"	text-align: center;\n"
"}\n"
"QPushButton:Hover{\n"
"	background-color: rgb(0, 88, 204);\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: rgb(0, 29, 66);\n"
"}"));
        btnSetIP->setFlat(false);
        btnReset = new QPushButton(page_setting);
        btnReset->setObjectName("btnReset");
        btnReset->setGeometry(QRect(550, 130, 161, 51));
        btnReset->setFont(font2);
        btnReset->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnReset->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        btnReset->setAutoFillBackground(false);
        btnReset->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border-radius:10px;\n"
"	color: rgb(242, 242, 242);\n"
"	background-color: rgb(0, 51, 122);\n"
"	text-align: center;\n"
"}\n"
"QPushButton:Hover{\n"
"	background-color: rgb(0, 88, 204);\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: rgb(0, 29, 66);\n"
"}"));
        btnReset->setFlat(false);
        tableVideo = new QTableWidget(page_setting);
        if (tableVideo->columnCount() < 3)
            tableVideo->setColumnCount(3);
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setPointSize(15);
        font3.setBold(false);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font3);
        tableVideo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font3);
        tableVideo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font3);
        tableVideo->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableVideo->rowCount() < 1000)
            tableVideo->setRowCount(1000);
        tableVideo->setObjectName("tableVideo");
        tableVideo->setGeometry(QRect(60, 260, 860, 380));
        sizePolicy.setHeightForWidth(tableVideo->sizePolicy().hasHeightForWidth());
        tableVideo->setSizePolicy(sizePolicy);
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Arial")});
        font4.setPointSize(15);
        tableVideo->setFont(font4);
        tableVideo->setStyleSheet(QString::fromUtf8("QTableWidget{\n"
"	background-color: rgb(240, 242, 245);\n"
"	color: rgb(0, 4, 83);\n"
"	gridline-color: rgb(0, 0, 127);\n"
"	selection-background-color:blue;\n"
"	border:1px solid rgb(0, 0, 127);\n"
"}\n"
"QTableWidget::item::selected{\n"
"	color: rgb(0, 4, 83);\n"
"	background-color: rgb(0, 170, 255);\n"
"}\n"
"QHeaderView{\n"
"	background-color: rgb(240, 242, 245);\n"
"	color: rgb(0, 4, 83);\n"
"}\n"
"QHeaderView::section{\n"
"	background-color:orange;\n"
"	color: rgb(0, 4, 83);\n"
"	border:1px solid black;\n"
"}"));
        tableVideo->setFrameShape(QFrame::Shape::NoFrame);
        tableVideo->setFrameShadow(QFrame::Shadow::Sunken);
        tableVideo->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
        tableVideo->setAutoScrollMargin(1);
        tableVideo->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tableVideo->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableVideo->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableVideo->setRowCount(1000);
        tableVideo->setColumnCount(3);
        tableVideo->horizontalHeader()->setVisible(true);
        tableVideo->horizontalHeader()->setHighlightSections(false);
        tableVideo->verticalHeader()->setVisible(false);
        tableSchedule = new QTableWidget(page_setting);
        if (tableSchedule->columnCount() < 5)
            tableSchedule->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font3);
        tableSchedule->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font4);
        tableSchedule->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font3);
        tableSchedule->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font3);
        tableSchedule->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font3);
        tableSchedule->setHorizontalHeaderItem(4, __qtablewidgetitem7);
        if (tableSchedule->rowCount() < 1000)
            tableSchedule->setRowCount(1000);
        tableSchedule->setObjectName("tableSchedule");
        tableSchedule->setGeometry(QRect(1005, 260, 860, 380));
        sizePolicy.setHeightForWidth(tableSchedule->sizePolicy().hasHeightForWidth());
        tableSchedule->setSizePolicy(sizePolicy);
        tableSchedule->setFont(font4);
        tableSchedule->setStyleSheet(QString::fromUtf8("QTableWidget{\n"
"	background-color: rgb(240, 242, 245);\n"
"	color: rgb(0, 4, 83);\n"
"	gridline-color: rgb(0, 0, 127);\n"
"	selection-background-color:blue;\n"
"	border:1px solid rgb(0, 0, 127);\n"
"}\n"
"QTableWidget::item::selected{\n"
"	color: rgb(0, 4, 83);\n"
"	background-color: rgb(0, 170, 255);\n"
"}\n"
"QHeaderView{\n"
"	background-color: rgb(240, 242, 245);\n"
"	color: rgb(0, 4, 83);\n"
"}\n"
"QHeaderView::section{\n"
"	background-color:orange;\n"
"	color: rgb(0, 4, 83);\n"
"	border:1px solid black;\n"
"}"));
        tableSchedule->setFrameShape(QFrame::Shape::NoFrame);
        tableSchedule->setFrameShadow(QFrame::Shadow::Sunken);
        tableSchedule->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
        tableSchedule->setAutoScrollMargin(1);
        tableSchedule->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tableSchedule->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableSchedule->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableSchedule->setTextElideMode(Qt::TextElideMode::ElideRight);
        tableSchedule->setRowCount(1000);
        tableSchedule->setColumnCount(5);
        tableSchedule->horizontalHeader()->setVisible(true);
        tableSchedule->horizontalHeader()->setHighlightSections(false);
        tableSchedule->verticalHeader()->setVisible(false);
        keterangan = new QTextEdit(page_setting);
        keterangan->setObjectName("keterangan");
        keterangan->setGeometry(QRect(55, 725, 876, 266));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Franklin Gothic")});
        font5.setPointSize(12);
        font5.setBold(false);
        keterangan->setFont(font5);
        keterangan->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 242, 245);\n"
"color: rgb(0, 4, 83);\n"
"border:1px solid rgb(240, 242, 245);"));
        listEntertainment = new QListWidget(page_setting);
        listEntertainment->setObjectName("listEntertainment");
        listEntertainment->setGeometry(QRect(1005, 730, 871, 261));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Franklin Gothic")});
        font6.setPointSize(12);
        font6.setStyleStrategy(QFont::NoAntialias);
        font6.setHintingPreference(QFont::PreferNoHinting);
        listEntertainment->setFont(font6);
        listEntertainment->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        listEntertainment->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 242, 245);\n"
"color: rgb(0, 4, 83);\n"
"border:1px solid rgb(240, 242, 245);"));
        listEntertainment->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        listEntertainment->setProperty("showDropIndicator", QVariant(false));
        listEntertainment->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
        btnExit = new QPushButton(page_setting);
        btnExit->setObjectName("btnExit");
        btnExit->setGeometry(QRect(1835, 25, 56, 61));
        QFont font7;
        font7.setPointSize(15);
        font7.setBold(true);
        font7.setStyleStrategy(QFont::NoAntialias);
        font7.setHintingPreference(QFont::PreferNoHinting);
        btnExit->setFont(font7);
        btnExit->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnExit->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        btnExit->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border-radius:10px;\n"
"	background-color: rgb(211, 0, 0);\n"
"	image: url(:/img_exit.png);\n"
"}\n"
"QPushButton:Hover{\n"
"	background-color: rgb(255, 121, 121);\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: rgb(162, 0, 0);\n"
"}"));
        btnExit->setAutoDefault(false);
        background = new QLabel(page_setting);
        background->setObjectName("background");
        background->setGeometry(QRect(0, 0, 1920, 1080));
        background->setStyleSheet(QString::fromUtf8("image: url(:/background_setting.png);"));
        date = new QLabel(page_setting);
        date->setObjectName("date");
        date->setGeometry(QRect(1495, 115, 386, 41));
        QFont font8;
        font8.setPointSize(15);
        font8.setBold(true);
        date->setFont(font8);
        date->setStyleSheet(QString::fromUtf8("color: rgb(5, 4, 83);\n"
"background-color: rgb(241, 241, 241);"));
        date->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        time = new QLabel(page_setting);
        time->setObjectName("time");
        time->setGeometry(QRect(1715, 150, 166, 41));
        QFont font9;
        font9.setPointSize(25);
        font9.setBold(true);
        time->setFont(font9);
        time->setStyleSheet(QString::fromUtf8("color: rgb(5, 4, 83);\n"
"background-color: rgb(241, 241, 241);"));
        time->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        stackedWidget->addWidget(page_setting);
        background->raise();
        textIP->raise();
        btnSetIP->raise();
        btnReset->raise();
        tableVideo->raise();
        tableSchedule->raise();
        keterangan->raise();
        listEntertainment->raise();
        btnExit->raise();
        date->raise();
        time->raise();
        page_video = new QWidget();
        page_video->setObjectName("page_video");
        stackedWidget->addWidget(page_video);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        btnSetIP->setDefault(true);
        btnReset->setDefault(true);
        btnExit->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Advertising Panel", nullptr));
#if QT_CONFIG(tooltip)
        textIP->setToolTip(QCoreApplication::translate("MainWindow", "IP Address", nullptr));
#endif // QT_CONFIG(tooltip)
        textIP->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
#if QT_CONFIG(tooltip)
        btnSetIP->setToolTip(QCoreApplication::translate("MainWindow", "Set IP", nullptr));
#endif // QT_CONFIG(tooltip)
        btnSetIP->setText(QCoreApplication::translate("MainWindow", "SET IP", nullptr));
#if QT_CONFIG(tooltip)
        btnReset->setToolTip(QCoreApplication::translate("MainWindow", "Reset", nullptr));
#endif // QT_CONFIG(tooltip)
        btnReset->setText(QCoreApplication::translate("MainWindow", "RESET", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableVideo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableVideo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "File Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableVideo->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "File Path", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableSchedule->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "File Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableSchedule->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Start Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableSchedule->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "End Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableSchedule->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Loop", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableSchedule->horizontalHeaderItem(4);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
#if QT_CONFIG(tooltip)
        btnExit->setToolTip(QCoreApplication::translate("MainWindow", "Exit", nullptr));
#endif // QT_CONFIG(tooltip)
        btnExit->setText(QString());
        background->setText(QString());
        date->setText(QCoreApplication::translate("MainWindow", "dddd, dd MMMM yyyy", nullptr));
        time->setText(QCoreApplication::translate("MainWindow", "HH:mm:ss", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
