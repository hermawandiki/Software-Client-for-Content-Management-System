<?php
require_once '../db.php';

header('Content-Type: application/json');

// Fungsi untuk autentikasi API key
function authenticate_api() {
    // Ambil API key dari header Authorization
    $headers = getallheaders();
    $authorization = isset($headers['Authorization']) ? $headers['Authorization'] : '';
    $valid_api_key = '1ffa4f35131d91a3ff84a9dd20c77d88';  // Ganti dengan API key yang valid

    // Periksa apakah Authorization header menggunakan format Bearer
    if (strpos($authorization, 'Bearer ') === 0) {
        $api_key = substr($authorization, 7); // Hapus prefix "Bearer "
    } else {
        http_response_code(401);  // Unauthorized
        echo json_encode(["status" => "error", "message" => "Invalid Authorization header format"]);
        exit;
    }

    // Periksa apakah API key valid
    if ($api_key !== $valid_api_key) {
        http_response_code(401);  // Unauthorized
        echo json_encode(["status" => "error", "message" => "Invalid API Key"]);
        exit;
    }
}

// Autentikasi API Key
authenticate_api();

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (!isset($_FILES['video']) || $_FILES['video']['error'] !== UPLOAD_ERR_OK) {
        echo json_encode(["status" => "error", "message" => "No file uploaded or upload error"]);
        exit;
    }

    $file = $_FILES['video'];
    $uploadDir = '../uploaded/';
    $filePath = $uploadDir . basename($file['name']);

    if (!is_dir($uploadDir)) {
        mkdir($uploadDir, 0777, true);
    }

    if (move_uploaded_file($file['tmp_name'], $filePath)) {
        $conn = getDBConnection();
        $stmt = $conn->prepare("INSERT INTO videos (filename, filepath, filetype, uploaded_at) VALUES (?, ?, ?, NOW())");
        $stmt->bind_param("sss", $file['name'], $filePath, $file['type']);

        if ($stmt->execute()) {
            echo json_encode(["status" => "success", "message" => "File uploaded successfully"]);
        } else {
            echo json_encode(["status" => "error", "message" => "Failed to save file information to database"]);
        }

        $stmt->close();
        $conn->close();
    } else {
        echo json_encode(["status" => "error", "message" => "Failed to move uploaded file"]);
    }
} else {
    http_response_code(405); // Method Not Allowed
    echo json_encode(["status" => "error", "message" => "Invalid request method"]);
}
?>
