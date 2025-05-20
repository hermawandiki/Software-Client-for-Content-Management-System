<?php
// Koneksi ke database
$host = "localhost";
$user = "root";
$password = ""; // Password default Laragon biasanya kosong
$dbname = "video_db";

$conn = new mysqli($host, $user, $password, $dbname);

// Periksa koneksi
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Periksa apakah parameter ID diberikan
if (isset($_GET['id'])) {
    $id = intval($_GET['id']);

    // Query untuk mendapatkan informasi video
    $sql = "SELECT filename, filepath FROM videos WHERE id = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("i", $id);
    $stmt->execute();
    $result = $stmt->get_result();

    // Periksa apakah video ditemukan
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        $file = $row['filepath'];

        // Periksa apakah file ada di server
        if (file_exists($file)) {
            // Mengatur header untuk mendownload file
            header('Content-Description: File Transfer');
            header('Content-Type: application/octet-stream');
            header('Content-Disposition: attachment; filename="' . basename($file) . '"');
            header('Expires: 0');
            header('Cache-Control: must-revalidate');
            header('Pragma: public');
            header('Content-Length: ' . filesize($file));

            // Membaca dan mengirimkan file ke pengguna
            readfile($file);
            exit;
        } else {
            echo "File tidak ditemukan.";
        }
    } else {
        echo "Video tidak ditemukan di database.";
    }
} else {
    echo "ID video tidak diberikan.";
}
?>
