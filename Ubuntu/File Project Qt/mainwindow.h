/*
 * Author   : PT. Rekaindo Global Jasa Engineer Team X Mechatronics PENS
 * Date     : 08/05/2025
 * Note     :
 * Contact  : 081235738756
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGuiApplication>
#include <QShortcut>
#include <QScreen>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QQueue>

#include <QVideoWidget>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QMediaPlayer>
#include <QVBoxLayout>

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <QFileInfo>
#include <QDateTime>
#include <QStringList>
#include <QScrollBar>
#include <QSet>
#include <QSettings>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

#include <QGraphicsVideoItem>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Video
    // QVideoWidget    *video;
    QGraphicsVideoItem *video;
    QMediaPlayer    *player;
    QAudioOutput    *audio;

    // Picture
    QLabel          *image;

    // Network API
    QNetworkAccessManager *networkManager;

    // Global Variable
    QTimer *timer, *updateTimer;
    QString currentVideo, nextVideo;
    QVector<int> videoIDs;
    QMap<int, QString> videoFileNames;
    QMap<int, QString> videoURLs;

    int totalDownloads = 999;
    int completedDownloads = 0;
    QStringList logs;
    QString ket, IP;

    // Main System
    QList<QString> vFilePath;
    QList<QTime> vStartTime, vEndTime;
    QList<qint8> vLoop, vRemaining;
    QList<QDate> vDate;

    QList<QString> entertainment;
    QSet<QString> downloadedFiles;

    int index, indexE, lastIndex;
    bool updatePlay = true;
    bool firstCall = true;
    bool fileReady = false;
    bool flagAdv = false;
    bool flagEntertainment = true;
    bool flagEnd = false;
    bool skipAdv = false;
    bool running = false;
    QString runMode = "DEFAULT";

private slots:
    // UI Slots
    void clearAllFocus();
    void on_btnExit_released();
    void on_btnReset_released();
    void on_btnSetIP_clicked();
    void onMediaFinished(QMediaPlayer::MediaStatus status);

    // Network Functions
    void updateStatus(int videoID, const QString &filename);
    void fetchVideoList();
    void parseVideoList(const QByteArray &data);
    void downloadFile(int id);
    void parseCSV(const QString &filePath);
    void downloadAllVideos();

    // Functions
    void playVideo(const QString &filepath);
    void playSelectedVideo();
    void onDownloadFinished();
    void checkSchedule(const QDateTime &first, const QDateTime &last);
    void updateData();
    void addLog(const QString &message);

    // Main System
    void mainLoop();
    void runModeA();
    void runModeB();
    void runModeDefault();
};
#endif // MAINWINDOW_H

// END OF PROGRAM
// Created by PT. Rekaindo GLobal Jasa Engineer Team and Mechatronics PENS
// Copyright 2025
