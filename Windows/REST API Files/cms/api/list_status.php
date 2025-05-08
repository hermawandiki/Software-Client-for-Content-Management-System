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

$conn = getDBConnection();
$sql = "SELECT id, filename, status, updated_at FROM status ORDER BY id ASC";
$result = $conn->query($sql);

$status_data = [];
if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        $status[] = [
            "id" => $row["id"],
            "filename" => basename($row["filename"]),
            // "status" => $row["status"],
            "updated_at" => $row["updated_at"]
        ];
    }
    echo json_encode($status);
} else {
    echo json_encode(["status" => "error", "message" => "No data found"]);
}

$conn->close();
?>
