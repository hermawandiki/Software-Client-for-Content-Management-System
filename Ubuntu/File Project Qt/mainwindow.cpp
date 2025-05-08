/*!
 * Author   : Diki Hermawan
 * Company  : PT. Rekaindo Global Jasa Engineer Team X Mechatronics PENS
 * Date     : 08/05/2025
 * Contact  : hermawansocmed@gmail.com
 * Note     : -
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->move(0, 0);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setWindowState(Qt::WindowFullScreen);

    // Video Table
    ui->tableVideo->setColumnWidth(0, 72);
    ui->tableVideo->setColumnWidth(1, 250);
    ui->tableVideo->setColumnWidth(2, 536);
    ui->tableVideo->setRowCount(0);
    ui->tableVideo->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // Schedule Table
    ui->tableSchedule->setColumnWidth(0, 246);
    ui->tableSchedule->setColumnWidth(1, 148);
    ui->tableSchedule->setColumnWidth(2, 148);
    ui->tableSchedule->setColumnWidth(3, 86);
    ui->tableSchedule->setColumnWidth(4, 230);
    ui->tableSchedule->setRowCount(0);
    ui->tableSchedule->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // Overlay Setup
    image = new QLabel(ui->page_video);
    QPixmap img("/home/hermawan/CMS/KAI.png");
    if (!img.isNull()) {
        image->setGeometry(0, 0, 1920, 1080);
        image->setPixmap(img.scaled(1920, 1080, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    image->hide();

    // Video Setup
    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::black);

    // Player Init
    player = new QMediaPlayer();
    video = new QGraphicsVideoItem;
    player->setVideoOutput(video);
    scene->addItem(video);
    player->setVideoOutput(video);

    video->setSize(QSizeF(1920,1080));
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFrameStyle(QFrame::NoFrame);
    ui->graphicsView->setAlignment(Qt::AlignCenter);

    // Audio Setup
    audio = new QAudioOutput();
    audio->setVolume(1);
    player->setAudioOutput(audio);

    // Network Init
    networkManager = new QNetworkAccessManager(this);

    // Shortcuts
    QShortcut *exitShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(exitShortcut, &QShortcut::activated, this, &MainWindow::on_btnExit_released);

    QShortcut *focusShortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(focusShortcut, &QShortcut::activated, this, &MainWindow::clearAllFocus);

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaFinished);

    QShortcut *shortcutP = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_P), this);
    connect(shortcutP, &QShortcut::activated, this, [=]() {
        int currentIndex = ui->stackedWidget->currentIndex();
        ui->stackedWidget->setCurrentIndex(currentIndex == 0 ? 1 : 0);
    });

    // Timer Main Loop
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::mainLoop);
    timer->start(10);

    // Timer Update Data
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateData);
    updateTimer->start(60000); // Periksa setiap 1 menit

    // Inisialisasi daftar file yang sudah ada
    QDir downloadDir("/home/hermawan/CMS/Downloaded");
    if (downloadDir.exists()) {
        for (const QString &file : downloadDir.entryList(QDir::Files)) {
            downloadedFiles.insert(file);
        }
    }
    QDir entertainmentDir("/home/hermawan/CMS/Entertainment");
    if (entertainmentDir.exists()) {
        for (const QString &file : entertainmentDir.entryList(QDir::Files)) {
            downloadedFiles.insert(file);
        }
    }

    QDir dir("/home/hermawan/CMS/Entertainment");
    if (!dir.exists()) return;
    entertainment = dir.entryList(QDir::Files);
    if (entertainment.isEmpty()) return;
    QStringList fullPaths;
    for (const QString &file : entertainment) {
        fullPaths << dir.absoluteFilePath(file);
    }
    ui->listEntertainment->addItems(fullPaths);

    // Final Init
    running = false;
    updatePlay = true;
    firstCall = true;
    index = 0;
    indexE = 0;
    lastIndex = -1;
    ui->keterangan->setReadOnly(true);
    clearAllFocus();

    QSettings settings("/home/hermawan/CMS/History/configCMS.ini", QSettings::IniFormat);
    QString savedIP = settings.value("Network/IP", "").toString();
    ui->textIP->setText(savedIP);

    // Tampilan Init adalah video
    ui->stackedWidget->setCurrentIndex(1);
    addLog("Aplikasi dijalankan!");
    on_btnSetIP_clicked();
    on_btnReset_released();
}

MainWindow::~MainWindow()
{
    if (player) {
        player->stop();
        player->deleteLater();
    }

    if (video) {
        video->deleteLater();
    }

    if (audio) {
        audio->deleteLater();
    }

    delete ui;

    addLog("Aplikasi ditutup - Sesi dihentikan!\n\n\n");
    player->stop();
    player->setSource(QUrl());

    QDir dir("/home/hermawan/CMS/Downloaded");
    if (!dir.exists()) {
        return;
    }

    QStringList files = dir.entryList(QDir::Files);
    for (const QString &file : files) {
        if (!dir.remove(file)) {
            qDebug() << "Failed to delete file:" << file;
        }
    }
}

/////////////////////////////////////////////////      USER CODE BEGIN UI Slots    /////////////////////////////////////////////////

void MainWindow::clearAllFocus()    // HILANGKAN SEMUA FOKUS INPUT
{
    ui->textIP->clearFocus();
    ui->tableSchedule->clearSelection();
    ui->tableVideo->clearSelection();
    ui->listEntertainment->clearSelection();
}

void MainWindow::on_btnExit_released()      // TOMBOL KELUAR APLIKASI
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this,
        "Konfirmasi Keluar",
        "Apakah Anda yakin ingin keluar dari aplikasi?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void MainWindow::on_btnReset_released()     // TOMBOL RESET ULANG DATA VIDEO DAN JADWAL
{
    if (!IP.isEmpty()) {
        ui->tableSchedule->selectionModel()->clearSelection();
        for (int i = 0; i < ui->listEntertainment->count(); i++) {
            ui->listEntertainment->item(i)->setBackground(i == indexE ? Qt::yellow : Qt::white);
        }

        player->stop();
        updatePlay = true;
        firstCall = true;
        fileReady = false;
        flagAdv = false;
        flagEntertainment = true;
        flagEnd = false;
        skipAdv = false;
        running = false;
        runMode = "DEFAULT";

        index = 0;

        updateStatus(0, "     ");
        updateStatus(1, "     ");
        downloadFile(0);
        fetchVideoList();
    } else {
        QMessageBox::warning(this, "IP Tidak Valid", "Masukkan alamat IP yang valid (misalnya: 192.168.1.1).");
    }
}

void MainWindow::onMediaFinished(QMediaPlayer::MediaStatus status)      // TRANSISI VIDEO
{
    if (status == QMediaPlayer::EndOfMedia && firstCall && fileReady) {
        firstCall = false;  // Hanya berubah setelah video pertama selesai
    }
}

void MainWindow::on_btnSetIP_clicked()  // SET ALAMAT IP
{
    if (!ui->textIP->text().isEmpty()) {
        IP = ui->textIP->text();
        ui->textIP->clearFocus();
        addLog("Sesi dibuka dengan IP: " + IP);
        QSettings settings("/home/hermawan/CMS/History/configCMS.ini", QSettings::IniFormat);
        settings.setValue("Network/IP", IP);
    } else {
        QMessageBox::warning(this, "IP Tidak Valid", "Masukkan alamat IP yang valid (misalnya: 192.168.1.1).");
    }
}

/////////////////////////////////////////////////      USER CODE END UI Slots    /////////////////////////////////////////////////




/////////////////////////////////////////////////      USER CODE BEGIN Network Functions    /////////////////////////////////////////////////

void MainWindow::updateStatus(int videoID, const QString &filename)     // UPDATE STATUS PEMUTARAN VIDEO
{
    if (filename.isEmpty()) return;

    // URL dengan API Key sebagai parameter
    QUrl url("http://" + IP + "/cms/api/upload_status.php?api_key=1ffa4f35131d91a3ff84a9dd20c77d88");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Buat JSON array
    QJsonArray jsonArray;
    QJsonObject jsonObj;
    jsonObj["id"] = videoID;
    jsonObj["filename"] = filename;
    jsonArray.append(jsonObj);

    QJsonDocument jsonDoc(jsonArray);
    QByteArray jsonData = jsonDoc.toJson();

    QNetworkReply *reply = networkManager->post(request, jsonData);
    connect(reply, &QNetworkReply::finished, this, [this, reply, filename, videoID]() {
        if (reply->error() == QNetworkReply::NoError) {
            QString logMessage = (videoID == 0)
            ? "Current Video  : " + filename
            : "Next Video     : " + filename;
            addLog("Status update berhasil: " + logMessage);
        } else {
            addLog("Gagal update status: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::fetchVideoList()       //  AMBIL DATA JSON LIST VIDEO DARI DATABASE
{
    QString urlString = "http://" + IP + "/cms/api/list_video.php?api_key=1ffa4f35131d91a3ff84a9dd20c77d88";

    QUrl url(urlString);
    QNetworkRequest request(url);

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            parseVideoList(responseData); // tampilkan ke tabel
            downloadAllVideos(); // unduh semua video
        } else {
            addLog("Gagal mengambil data: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::parseVideoList(const QByteArray &data)     // TAMPILKAN LIST VIDEO KE TABEL
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    if (!jsonDoc.isArray()) {
        qDebug() << "Format JSON tidak valid";
        return;
    }

    QJsonArray jsonArray = jsonDoc.array();
    ui->tableVideo->setRowCount(0); // Kosongkan tabel sebelum mengisi ulang

    QStringList validExtensions = {".mp4", ".avi", ".mkv", ".mov", ".flv", ".wmv"}; // Format yang diperbolehkan

    int row = 0;
    videoIDs.clear(); // Kosongkan daftar ID sebelum mengisi ulang

    for (const QJsonValue &value : jsonArray) {
        QJsonObject obj = value.toObject();
        int id = obj["id"].toString().toInt();
        QString filename = obj["filename"].toString();
        QString url = obj["url"].toString();

        if (id <= 0) {
            // jadwal csv
            continue;
        }

        // Cek apakah file memiliki ekstensi video yang valid
        bool isValid = false;
        for (const QString &ext : validExtensions) {
            if (filename.toLower().endsWith(ext)) {
                isValid = true;
                break;
            }
        }

        // Tambahkan ke tabel & daftar download jika valid
        if (isValid) {
            ui->tableVideo->insertRow(row);
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(id));
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableVideo->setItem(row, 0, item);
            ui->tableVideo->setItem(row, 1, new QTableWidgetItem(filename));
            ui->tableVideo->setItem(row, 2, new QTableWidgetItem(url));

            videoIDs.append(id);
            videoFileNames[id] = filename;
            videoURLs[id] = url;
            row++;
        }
    }
    addLog("List video telah diperbaharui.");
}

void MainWindow::downloadFile(int id)       // FUNGSI UNTUK UNDUH FILE DARI DATABASE
{
    QString urlString = "http://" + IP + "/cms/api/download.php?api_key=1ffa4f35131d91a3ff84a9dd20c77d88&id=" + QString::number(id);

    QUrl url(urlString);
    QNetworkRequest request(url);

    QString downloadDir = "/home/hermawan/CMS/Downloaded";
    QDir dir(downloadDir);
    if (!dir.exists()) {
        dir.mkpath(downloadDir);
    }

    QString fileName = (id == 0) ? "schedule.csv" : videoFileNames.value(id, "file_" + QString::number(id) + ".mp4");
    QString filePath = dir.filePath(fileName);

    // Hanya cek file lokal jika id != 0
    if (id != 0 && downloadedFiles.contains(fileName)) {
        addLog("File " + fileName + " sudah ada, tidak diunduh ulang.");
        onDownloadFinished();
        return;
    }

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, id, filePath]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();

            // Ambil nama file dari header Content-Disposition sebagai variabel lokal
            QString contentDisposition = reply->rawHeader("Content-Disposition");
            QString localFileName;
            if (contentDisposition.contains("filename=")) {
                localFileName = contentDisposition.split("filename=").last().replace("\"", "").trimmed();
            } else {
                // localFileName = (id == 0) ? "schedule.csv" : videoFileNames.value(id, "file_" + QString::number(id) + ".mp4");
            }

            // Tentukan filePath berdasarkan localFileName
            QString downloadDir = "/home/hermawan/CMS/Downloaded";
            QString updatedFilePath = QDir(downloadDir).filePath(localFileName);

            QFile file(updatedFilePath);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(responseData);
                file.close();
                addLog("File berhasil diunduh: " + updatedFilePath);
                downloadedFiles.insert(localFileName); // Tandai sebagai sudah diunduh

                if (localFileName.endsWith(".csv", Qt::CaseInsensitive)) {
                    parseCSV(updatedFilePath);
                } else {
                    onDownloadFinished();
                }
            } else {
                // addLog("File jadwal tidak tersedia.");
                vFilePath.clear();
                vStartTime.clear();
                vEndTime.clear();
                vLoop.clear();
                vDate.clear();
                vRemaining.clear();
                ui->tableSchedule->setRowCount(0);
            }
        } else {
            addLog("Gagal mengunduh file ID " + QString::number(id) + ": " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::parseCSV(const QString &filePath)      // TAMPILKAN JADWAL KE TABEL
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        addLog("Gagal membuka file CSV");
        return;
    }

    QTextStream in(&file);
    QStringList headers;
    bool isFirstLine = true;

    vFilePath.clear();
    vStartTime.clear();
    vEndTime.clear();
    vLoop.clear();
    vDate.clear();
    vRemaining.clear();

    ui->tableSchedule->setRowCount(0);
    int row = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList values = line.split(',');

        if (isFirstLine) {
            headers = values;
            isFirstLine = false;
            continue;
        }

        vFilePath.append("/home/hermawan/CMS/Downloaded/" + values[0]);
        vStartTime.append(QTime::fromString(values[1], "HH:mm:ss"));
        vEndTime.append(QTime::fromString(values[2], "HH:mm:ss"));
        vLoop.append(values[3].toInt());
        vRemaining.append(values[3].toInt());
        vDate.append(QDate::fromString(values[4], "dd/MM/yyyy"));


        // vFilePath.append("D:/CMS/Downloaded/" + values[0]);
        // vStartTime.append(QTime::fromString(values[1], "HH:mm:ss"));
        // vLoop.append(values[2].toInt());
        // vRemaining.append(values[2].toInt());
        // vDate.append(QDate::fromString(values[3], "dd/MM/yyyy"));

        ui->tableSchedule->insertRow(row);
        for (int col = 0; col < values.size(); ++col) {
            ui->tableSchedule->setItem(row, col, new QTableWidgetItem(values[col]));
        }

        // ui->tableSchedule->setItem(row, 0, new QTableWidgetItem(values[0]));
        // ui->tableSchedule->setItem(row, 1, new QTableWidgetItem(values[1]));
        // ui->tableSchedule->setItem(row, 3, new QTableWidgetItem(values[2]));
        // ui->tableSchedule->setItem(row, 4, new QTableWidgetItem(values[3]));

        row++;
    }

    if(!vLoop.isEmpty() && vLoop[0] != 0) {
        runMode = "MODE_A";
    } else if (!vEndTime.isEmpty() && vEndTime[0].isValid() && vEndTime[0] != QTime(0, 0, 0)) {
        runMode = "MODE_B";
    } else {
        runMode = "DEFAULT";
    } qDebug() << runMode;

    if(!vFilePath.isEmpty()){
        addLog("Jadwal telah diperbaharui.");
        checkSchedule(QDateTime(vDate[0], vStartTime[0]), QDateTime(vDate[vDate.size()-1], vStartTime[vStartTime.size()-1]));
    } else {
        addLog("Jadwal tidak tersedia.");
    }
    file.close();
}

void MainWindow::downloadAllVideos() {
    if (videoIDs.isEmpty()) {
        // addLog("Tidak ada video untuk diunduh.");
        fileReady = true;
        return;
    }

    totalDownloads = 0;
    completedDownloads = 0;

    for (int id : videoIDs) {
        QString fileName = videoFileNames.value(id, "file_" + QString::number(id) + ".mp4");
        if (!downloadedFiles.contains(fileName)) {
            totalDownloads++;
            downloadFile(id);
        } else {
            addLog("Video " + fileName + " sudah ada, tidak diunduh ulang.");
            onDownloadFinished();
        }
    }

    if (totalDownloads == 0) {
        // addLog("Semua video sudah ada, tidak ada yang perlu diunduh.");
        fileReady = true;
    }
}

/////////////////////////////////////////////////      USER CODE END Network Functions    /////////////////////////////////////////////////




/////////////////////////////////////////////////      USER CODE BEGIN Functions    /////////////////////////////////////////////////

void MainWindow::checkSchedule(const QDateTime &first, const QDateTime &last)       // CEK JADWAL PERTAMA DAN TERAKHIR
{
    QDateTime startTime[2] = { first, last };
    QDateTime currentDateTime = QDateTime::currentDateTime();
    qint64 msecsToStart[2];
    qint64 dateTime[2][4];

    for(int i=0; i<2; i++){
        msecsToStart[i] = currentDateTime.msecsTo(startTime[i]);
        dateTime[i][0] = msecsToStart[i] / 86400000;                // day
        dateTime[i][1] = (msecsToStart[i] % 86400000) / 3600000;    // hour
        dateTime[i][2] = (msecsToStart[i] % 3600000) / 60000;       // minute
        dateTime[i][3] = (msecsToStart[i] % 60000) / 1000;          // second
    }

    if(dateTime[1][3] < 0){
        QString pastMessage = QString("Hari sudah terlewat untuk jadwal %1")
        .arg(startTime[1].toString("yyyy-MM-dd HH:mm:ss"));
        addLog(pastMessage);
        flagEnd = true;
    } else {
        // Log informasi jadwal
        QString logMessage = QString("Sistem akan berjalan pada %1 dalam %2 hari %3 jam %4 menit %5 detik")
                                 .arg(startTime[0].toString("yyyy-MM-dd HH:mm:ss"))
                                 .arg(dateTime[0][0])
                                 .arg(dateTime[0][1])
                                 .arg(dateTime[0][2])
                                 .arg(dateTime[0][3]);
        addLog(logMessage);
        flagEnd = false;
    }
}

void MainWindow::onDownloadFinished()       // FLAG SELESAI UNDUH
{
    completedDownloads++; // Tambah counter unduhan yang selesai

    // Jika semua unduhan selesai, tandai fileReady dan beri notifikasi
    if (completedDownloads >= totalDownloads) {
        // addLog("Semua video telah diunduh.");
        fileReady = true;
        qDebug() << "Ready lur";
    }
}

void MainWindow::updateData()       // UPDATE DATA JADWAL DAN VIDEO
{
    if (!running) {
        addLog("Memperbarui data sebelum pemutaran iklan dimulai...");

        updatePlay = true;
        firstCall = true;
        fileReady = false;
        flagAdv = false;
        flagEntertainment = true;
        flagEnd = false;
        skipAdv = false;
        running = false;
        runMode = "DEFAULT";

        index = 0;

        downloadFile(0);
        fetchVideoList();
    }
}

void MainWindow::playVideo(const QString &filePath)     // FUNGSI UNTUK PEMUTARAN VIDEO
{
    if (player->isPlaying()) {
        return;
    }
    QUrl fileUrl(filePath);
    currentVideo = fileUrl.fileName();

    if (filePath.startsWith("http://") || filePath.startsWith("https://")) {
        player->setSource(QUrl(filePath));
    }
    else if (QFile::exists(filePath)) {
        player->setSource(QUrl::fromLocalFile(filePath));
    } else {
        addLog("Video file tidak ditemukan!");
        return;
    }
    player->setPlaybackRate(1.0);
    player->play();
}

void MainWindow::playSelectedVideo()        // FUNGSI UNTUK PEMUTARAN VIDEO DARI TABEL (TIDAK DIPAKAI)
{
    // Dapatkan baris yang dipilih
    QModelIndexList selectedRows = ui->tableVideo->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        addLog("Tidak ada baris yang dipilih!");
        return;
    }

    // Ambil baris pertama yang dipilih
    int selectedRow = selectedRows.first().row();

    // Ambil URL video dari kolom ke-2 (Index 2)
    QString filename = ui->tableVideo->item(selectedRow, 1)->text();
    QString videoUrl = "/home/hermawan/CMS/Downloaded/" + filename;

    if (videoUrl.isEmpty()) {
        addLog("URL video kosong!");
        return;
    }

    // Atur video ke player dan mulai pemutaran
    playVideo(videoUrl);
}

void MainWindow::addLog(const QString &message)     // FUNGSI UNTUK MENAMPILKAN DATA LOG
{
    QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    // Format log dengan timestamp
    QString logEntry = QString("[%1] %2").arg(timeStamp, message);
    // Tambahkan pesan ke daftar log
    logs.append(logEntry);
    // Jika jumlah log lebih dari 10, hapus yang paling lama
    if (logs.size() > 10) {
        logs.removeFirst();
    }
    // Gabungkan semua log dengan newline dan tampilkan di QTextEdit
    ui->keterangan->setPlainText(logs.join("\n"));
    ui->keterangan->verticalScrollBar()->setValue(ui->keterangan->verticalScrollBar()->maximum());
    // Tentukan nama file log berdasarkan tanggal saat ini
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");  // Format tanggal (contoh: 2025-05-03)
    QString logFilePath = QString("/home/hermawan/CMS/History/LogCMS_%1.txt").arg(currentDate);  // Membuat file log berdasarkan tanggal

    // Pastikan folder ada
    QDir logDir = QFileInfo(logFilePath).absoluteDir();
    if (!logDir.exists()) {
        logDir.mkpath(".");  // Buat folder jika belum ada
    }

    // Simpan log ke file
    QFile file(logFilePath);

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << logEntry << "\n";  // Tulis log ke file
        file.close();  // Jangan lupa tutup file setelah menulis
    } else {
        qWarning() << "Tidak dapat membuka file untuk menulis log.";
    }
}

/////////////////////////////////////////////////      USER CODE END Functions    /////////////////////////////////////////////////




/////////////////////////////////////////////////      USER CODE BEGIN Main Systen    /////////////////////////////////////////////////

void MainWindow::mainLoop()     // LOOPING UTAMA PEMILIHAN RUNMODE
{
    QDateTime now = QDateTime::currentDateTime();
    ui->date->setText(now.toString("dddd, dd MMMM yyyy"));
    ui->time->setText(now.toString("HH:mm:ss"));

    if(runMode == "MODE_A"){
        runModeA();
    } else if(runMode == "MODE_B"){
        runModeB();
    } else {
        runModeDefault();
    }
}

void MainWindow::runModeA()     // MODE A : DENGAN STARTTIME DAN JUMLAH LOOP
{
    if(firstCall){
        playVideo("/home/hermawan/CMS/Entertainment/" + entertainment[indexE]);
        ui->listEntertainment->item(indexE)->setBackground(Qt::yellow);
        flagEntertainment = true;
    } else {
        if(updatePlay){
            if(!flagEnd && QTime::currentTime() >= vStartTime[index] && QDate::currentDate() == vDate[index] && vRemaining[index] > 0) {
                // player->stop();
                if(player->isPlaying()) return;
                playVideo(vFilePath[index]);
                running = true;
                updatePlay = false;
                flagAdv = true;
                skipAdv = false;
                flagEntertainment = false;
                updateStatus(0, currentVideo);
                ui->tableSchedule->selectionModel()->clearSelection();
                ui->tableSchedule->selectRow(index);

                if(vRemaining[index] > 0 ){
                    vRemaining[index]--;
                }

                ui->tableSchedule->setItem(index, 3, new QTableWidgetItem(QString::number(vRemaining[index])));
                qDebug() << "Current   : " << index;
                index++; // Mulai dari indeks berikutnya
                while (index < vRemaining.size() && vRemaining[index] <= 0) {
                    index++;
                }
                qDebug() << "Cek1" << index;
                if(index >= vFilePath.size()){  // index terakhir, kembali ke index dengan vRemaining > 0
                    for(int i=0; i<vFilePath.size(); i++){
                        if(vRemaining[i] > 0){
                            index = i;
                            break;
                        }
                    }
                    if(index >= vFilePath.size()){
                        index = 0;
                    }
                }
                qDebug() << "Cek2" << index;
                if(QTime::currentTime() < vStartTime[index] || QDate::currentDate() != vDate[index]){
                    for(int i=0; i<index; i++){
                        if(vRemaining[i] > 0){
                            index = i;
                            break;
                        }
                    }
                }
                qDebug() << "Cek3" << index;

                qint8 sum = std::accumulate(vRemaining.begin(), vRemaining.end(), 0);
                QUrl fileUrl(vFilePath[index]);
                nextVideo = fileUrl.fileName();
                if(sum <= 0){
                    updateStatus(1, "     ");
                    updatePlay = false;
                } else{
                    updateStatus(1, nextVideo);
                }
            } else {
                skipAdv = true;
            }
        }

        if(player->mediaStatus() == QMediaPlayer::EndOfMedia){
            qint8 sum = std::accumulate(vRemaining.begin(), vRemaining.end(), 0);
            if(!flagEnd){
                if (sum <= 0) {
                    updateStatus(0, "     ");
                    updatePlay = false;
                    running = false;
                    ui->tableSchedule->selectionModel()->clearSelection();
                    flagEnd = true;
                    index = 0;
                }
            }

            if (flagEntertainment && !skipAdv){
                updatePlay = true;
                // SKIP ENTERTAINMENT INI DIK
            } else if (flagAdv || skipAdv) {
                indexE = (indexE+1) % entertainment.size();
                playVideo("/home/hermawan/CMS/Entertainment/" + entertainment[indexE]);
                flagEntertainment = true;
                for (int i = 0; i < ui->listEntertainment->count(); i++) {
                    ui->listEntertainment->item(i)->setBackground(i == indexE ? Qt::yellow : Qt::white);
                }
            }
        }
    }
}

void MainWindow::runModeB()     // MODE B : DENGAN STARTTIME DAN ENDTIME
{
    if(firstCall){
        playVideo("/home/hermawan/CMS/Entertainment/" + entertainment[indexE]);
        ui->listEntertainment->item(indexE)->setBackground(Qt::yellow);
    } else {
        if(updatePlay){
            if(QTime::currentTime() >= vStartTime[index] && QTime::currentTime() <= vEndTime[index] && QDate::currentDate() == vDate[index]) {
                player->stop();
                playVideo(vFilePath[index]);
                running = true;
                updatePlay = false;
                flagAdv = true;

                if(index != lastIndex){
                    updateStatus(0, currentVideo);
                    ui->tableSchedule->selectionModel()->clearSelection();
                    ui->tableSchedule->selectRow(index);
                    if (index + 1 < vFilePath.size() && !vFilePath[index + 1].isEmpty() && QFileInfo(vFilePath[index + 1]).exists()) {
                        QUrl fileUrl(vFilePath[index + 1]);
                        nextVideo = fileUrl.fileName();
                        updateStatus(1, nextVideo);
                    } else {
                        nextVideo = "     ";
                        updateStatus(1, nextVideo);
                    }
                }

                lastIndex = index;
            } else {
                if(flagAdv) index++;
                if(running && index >= vFilePath.size()) {
                    running = false;
                    index = 0;
                    updateStatus(0, "     ");
                    ui->tableSchedule->selectionModel()->clearSelection();
                }
                flagAdv = false;
            }
        }

        if(flagAdv && QTime::currentTime() >= vEndTime[index]){
            player->stop();
        }

        // qDebug() << player->mediaStatus() << flagAdv;
        if(player->mediaStatus() == QMediaPlayer::EndOfMedia || player->mediaStatus() == QMediaPlayer::LoadedMedia){
            if (flagAdv){
                updatePlay = true;
            } else {
                indexE = (indexE+1) % entertainment.size();
                playVideo("/home/hermawan/CMS/Entertainment/" + entertainment[indexE]);
                for (int i = 0; i < ui->listEntertainment->count(); i++) {
                    ui->listEntertainment->item(i)->setBackground(i == indexE ? Qt::yellow : Qt::white);
                }
            }
        }
    }
}

void MainWindow::runModeDefault()       // MODE DEFAULT : KETIKA JADWAL DAN VIDEO TIDAK TERSEDIA
{
    if(firstCall){
        playVideo("/home/hermawan/CMS/Entertainment/" + entertainment[indexE]);
        ui->listEntertainment->item(indexE)->setBackground(Qt::yellow);
    } else {
        if(player->mediaStatus() == QMediaPlayer::EndOfMedia){
            indexE = (indexE+1) % entertainment.size();
            playVideo("/home/hermawan/CMS/Entertainment/" + entertainment[indexE]);
            for (int i = 0; i < ui->listEntertainment->count(); i++) {
                ui->listEntertainment->item(i)->setBackground(i == indexE ? Qt::yellow : Qt::white);
            }
        }
    }
}

/////////////////////////////////////////////////      USER CODE END Main System    /////////////////////////////////////////////////

// END OF PROGRAM
// Created by PT. Rekaindo GLobal Jasa Engineer Team and Mechatronics PENS
// Copyright 2025
