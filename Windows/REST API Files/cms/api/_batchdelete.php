<?php
// Include file koneksi database
require_once '../db.php';

// Set response header
header('Content-Type: application/json');

// Fungsi untuk autentikasi API key dari header Authorization
function authenticate_api() {
    $headers = getallheaders();
    $authorization = isset($headers['Authorization']) ? $headers['Authorization'] : '';

    $valid_api_key = '1ffa4f35131d91a3ff84a9dd20c77d88';  // Ganti dengan API key yang valid

    // Periksa apakah header Authorization menggunakan format Bearer
    if (strpos($authorization, 'Bearer ') === 0) {
        $api_key = substr($authorization, 7); // Hapus prefix "Bearer "
    } else {
        http_response_code(401);  // Unauthorized
        echo json_encode(["status" => "error", "message" => "Invalid Authorization header format"]);
        exit();
    }

    // Periksa apakah API key valid
    if ($api_key !== $valid_api_key) {
        http_response_code(401);  // Unauthorized
        echo json_encode(["status" => "error", "message" => "Invalid API Key"]);
        exit();
    }
}

// Autentikasi API Key
authenticate_api();

// Ambil data JSON dari body request
$inputData = json_decode(file_get_contents('php://input'), true);

// Validasi apakah JSON berhasil dibaca
if (!$inputData) {
    echo json_encode(["status" => "error", "message" => "No data received"]);
    exit();
}

// Validasi parameter 'ids'
if (!isset($inputData['ids']) || !is_array($inputData['ids']) || count($inputData['ids']) === 0) {
    echo json_encode(["status" => "error", "message" => "Parameter 'ids' must be a non-empty array"]);
    exit();
}

// Ambil ID video dari input
$videoIds = $inputData['ids'];

// Koneksi ke database
$conn = getDBConnection();

// Siapkan query untuk mengambil file paths dari ID yang diberikan
$placeholders = implode(',', array_fill(0, count($videoIds), '?'));
$query = "SELECT id, filepath FROM videos WHERE id IN ($placeholders)";
$stmt = $conn->prepare($query);
$stmt->bind_param(str_repeat('i', count($videoIds)), ...$videoIds);
$stmt->execute();
$result = $stmt->get_result();

// Ambil semua file paths yang sesuai
$filesToDelete = [];
while ($row = $result->fetch_assoc()) {
    $filesToDelete[$row['id']] = $row['filepath'];
}
$stmt->close();

// Jika tidak ada file yang ditemukan
if (count($filesToDelete) === 0) {
    echo json_encode(["status" => "error", "message" => "No videos found for the given IDs"]);
    exit();
}

// Hapus file dari server
$deletedFiles = [];
foreach ($filesToDelete as $id => $filepath) {
    if (file_exists($filepath)) {
        if (unlink($filepath)) {
            $deletedFiles[] = $filepath;
        }
    }
}

// Hapus data dari database
$query = "DELETE FROM videos WHERE id IN ($placeholders)";
$stmt = $conn->prepare($query);
$stmt->bind_param(str_repeat('i', count($videoIds)), ...$videoIds);

if ($stmt->execute()) {
    echo json_encode([
        "status" => "success",
        "message" => "Videos deleted successfully",
        "deleted_files" => $deletedFiles
    ]);
} else {
    echo json_encode(["status" => "error", "message" => "Failed to delete videos from database"]);
}

$stmt->close();
$conn->close();
?>
