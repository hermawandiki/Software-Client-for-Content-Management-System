<?php
require_once '../db.php';

header('Content-Type: application/json');

// Fungsi untuk autentikasi API key
function authenticate_api() {
    $api_key = isset($_GET['api_key']) ? $_GET['api_key'] : '';
    $valid_api_key = '1ffa4f35131d91a3ff84a9dd20c77d88';  // Ganti dengan API key yang valid

    if ($api_key !== $valid_api_key) {
        http_response_code(401);  // Unauthorized
        echo json_encode(["status" => "error", "message" => "Invalid API Key"]);
        exit;
    }
}

// Autentikasi API Key
authenticate_api();

// Pastikan request adalah POST
if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    echo json_encode(["status" => "error", "message" => "Invalid request method"]);
    exit;
}

// Pastikan parameter ID tersedia
if (!isset($_POST['id']) || !is_numeric($_POST['id'])) {
    echo json_encode(["status" => "error", "message" => "Missing or invalid ID"]);
    exit;
}

$videoID = intval($_POST['id']);  // Konversi ke integer

// Periksa apakah file diunggah
if (!isset($_FILES['file']) || $_FILES['file']['error'] !== UPLOAD_ERR_OK) {
    echo json_encode(["status" => "error", "message" => "No file uploaded or upload error"]);
    exit;
}

$file = $_FILES['file'];
$uploadDir = '../uploaded/';
$filePath = $uploadDir . basename($file['name']);

if (!is_dir($uploadDir)) {
    mkdir($uploadDir, 0777, true);
}

// Pindahkan file ke folder tujuan
if (!move_uploaded_file($file['tmp_name'], $filePath)) {
    echo json_encode(["status" => "error", "message" => "Failed to move uploaded file"]);
    exit;
}

// Simpan atau update ke database
$conn = getDBConnection();

// Cek apakah ID sudah ada
$checkStmt = $conn->prepare("SELECT id FROM videos WHERE id = ?");
$checkStmt->bind_param("i", $videoID);
$checkStmt->execute();
$checkStmt->store_result();

if ($checkStmt->num_rows > 0) {
    // Jika ID sudah ada, perbarui data
    $stmt = $conn->prepare("UPDATE videos SET filename = ?, filepath = ?, filetype = ?, uploaded_at = NOW() WHERE id = ?");
    $stmt->bind_param("sssi", $file['name'], $filePath, $file['type'], $videoID);
    $message = "File updated successfully";
} else {
    // Jika ID belum ada, buat data baru
    $stmt = $conn->prepare("INSERT INTO videos (id, filename, filepath, filetype, uploaded_at) VALUES (?, ?, ?, ?, NOW())");
    $stmt->bind_param("isss", $videoID, $file['name'], $filePath, $file['type']);
    $message = "File uploaded successfully";
}

if ($stmt->execute()) {
    echo json_encode(["status" => "success", "message" => $message]);
} else {
    echo json_encode(["status" => "error", "message" => "Database error"]);
}

$stmt->close();
$checkStmt->close();
$conn->close();
?>
