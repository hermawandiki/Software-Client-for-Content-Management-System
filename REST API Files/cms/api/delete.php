<?php
require_once '../db.php';

header('Content-Type: application/json');

// Autentikasi API key
if (!isset($_GET['api_key']) || $_GET['api_key'] !== '1ffa4f35131d91a3ff84a9dd20c77d88') {
    http_response_code(401); // Unauthorized
    echo json_encode(["status" => "error", "message" => "Invalid API Key"]);
    exit;
}

// Periksa apakah id video diberikan
if (!isset($_GET['id'])) {
    echo json_encode(["status" => "error", "message" => "No video ID provided"]);
    exit();
}

$videoId = $_GET['id'];

// Menghubungkan ke database
$conn = getDBConnection();

// Pertama, ambil filepath video untuk menghapus file dari server
$stmt = $conn->prepare("SELECT filepath FROM videos WHERE id = ?");
$stmt->bind_param("i", $videoId);
$stmt->execute();
$stmt->bind_result($filepath);
$stmt->fetch();
$stmt->close();

// Jika video ditemukan, hapus dari database dan file
if ($filepath) {
    // Hapus file dari server
    if (file_exists($filepath)) {
        unlink($filepath); // Menghapus file dari server
    }

    // Hapus data video dari database
    $stmt = $conn->prepare("DELETE FROM videos WHERE id = ?");
    $stmt->bind_param("i", $videoId);
    if ($stmt->execute()) {
        echo json_encode(["status" => "success", "message" => "Video deleted successfully"]);
    } else {
        echo json_encode(["status" => "error", "message" => "Failed to delete video"]);
    }
    $stmt->close();
} else {
    echo json_encode(["status" => "error", "message" => "Video not found"]);
}

$conn->close();
?>
