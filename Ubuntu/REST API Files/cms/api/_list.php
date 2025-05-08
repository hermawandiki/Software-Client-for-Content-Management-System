<?php
require_once '../db.php';

header('Content-Type: application/json');

// Fungsi untuk autentikasi API key
function authenticate_api() {
    // Ambil API key dari header Authorization
    $headers = getallheaders();
    $api_key = isset($headers['Authorization']) ? $headers['Authorization'] : '';
    $valid_api_key = '1ffa4f35131d91a3ff84a9dd20c77d88';  // Ganti dengan API key yang valid

    // Validasi format API key (Bearer Token)
    if (strpos($api_key, 'Bearer ') === 0) {
        $api_key = substr($api_key, 7); // Hapus prefix "Bearer "
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

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $conn = getDBConnection();

    $sql = "SELECT id, filename, filepath FROM videos";
    $result = $conn->query($sql);

    $videos = [];
    while ($row = $result->fetch_assoc()) {
        $videos[] = [
            "id" => $row['id'],
            "filename" => $row['filename'],
            "url" => "http://localhost/cms/uploaded/" . basename($row['filepath'])
        ];
    }

    echo json_encode(["status" => "success", "data" => $videos]);

    $conn->close();
} else {
    http_response_code(405);  // Method Not Allowed
    echo json_encode(["status" => "error", "message" => "Invalid request method"]);
}
?>
