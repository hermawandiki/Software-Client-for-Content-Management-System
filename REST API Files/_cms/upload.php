<?php
// Konfigurasi database
$host = "localhost";
$user = "root";
$password = "";
$dbname = "video_db";

// Koneksi ke database
$conn = new mysqli($host, $user, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Periksa apakah file telah diunggah
if (isset($_FILES['video']) && $_FILES['video']['error'] === 0) {
    $video = $_FILES['video'];
    $uploadDir = 'videos/';
    $fileName = $video['name'];
    $fileTmp = $video['tmp_name'];
    $fileSize = $video['size'];
    $fileType = mime_content_type($fileTmp);
    $fileExt = strtolower(pathinfo($fileName, PATHINFO_EXTENSION));
    $allowedExt = ['mp4', 'mkv', 'avi'];

    // Validasi file
    if (in_array($fileExt, $allowedExt) && $fileSize <= 50 * 1024 * 1024) { // Max 50MB
        // Pastikan folder uploads ada
        if (!is_dir($uploadDir)) {
            mkdir($uploadDir, 0777, true);
        }

        // Simpan file ke folder uploads
        $newFileName = time() . '_' . uniqid() . '.' . $fileExt;
        $filePath = $uploadDir . $newFileName;
        if (move_uploaded_file($fileTmp, $filePath)) {
            // Simpan metadata ke database
            $stmt = $conn->prepare("INSERT INTO videos (filename, filepath, filetype) VALUES (?, ?, ?)");
            $stmt->bind_param("sss", $fileName, $filePath, $fileType);
            if ($stmt->execute()) {
                echo "Video uploaded successfully: $fileName";
            } else {
                echo "Database error: " . $stmt->error;
            }
            $stmt->close();
        } else {
            echo "Failed to upload video.";
        }
    } else {
        echo "Invalid file type or file size too large.";
    }
} else {
    echo "No file uploaded or an error occurred.";
}

$conn->close();
?>
