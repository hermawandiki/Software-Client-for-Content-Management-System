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

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    if (!isset($_GET['id'])) {
        echo json_encode(["status" => "error", "message" => "No video ID provided"]);
        exit();
    }

    $videoId = $_GET['id'];

    $conn = getDBConnection();
    $stmt = $conn->prepare("SELECT filename, filetype, filepath FROM videos WHERE id = ?");
    $stmt->bind_param("i", $videoId);
    $stmt->execute();
    $stmt->bind_result($filename, $filetype, $filepath);

    if ($stmt->fetch()) {
        if (file_exists($filepath)) {
            header('Content-Description: File Transfer');
            header('Content-Type: ' . $filetype);
            header('Content-Disposition: attachment; filename="' . basename($filename) . '"');
            header('Expires: 0');
            header('Cache-Control: must-revalidate');
            header('Pragma: public');
            header('Content-Length: ' . filesize($filepath));
            readfile($filepath);
            exit();
        } else {
            echo json_encode(["status" => "error", "message" => "File not found"]);
        }
    } else {
        echo json_encode(["status" => "error", "message" => "No video found with this ID"]);
    }

    $stmt->close();
    $conn->close();
} else {
    echo json_encode(["status" => "error", "message" => "Invalid request method"]);
}
?>