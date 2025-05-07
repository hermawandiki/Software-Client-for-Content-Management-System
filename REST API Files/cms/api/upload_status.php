<?php
require_once '../db.php';

header('Content-Type: application/json');

// Fungsi autentikasi API key
function authenticate_api() {
    $api_key = isset($_GET['api_key']) ? $_GET['api_key'] : '';
    $valid_api_key = '1ffa4f35131d91a3ff84a9dd20c77d88';

    if ($api_key !== $valid_api_key) {
        http_response_code(401);
        echo json_encode(["status" => "error", "message" => "Invalid API Key"]);
        exit;
    }
}

// Autentikasi API Key
authenticate_api();

// Baca JSON dari body request
$data = json_decode(file_get_contents("php://input"), true);

if (!is_array($data)) {
    echo json_encode(["status" => "error", "message" => "Invalid JSON format"]);
    exit;
}

$conn = getDBConnection();
$response = [];

foreach ($data as $entry) {
    if (!isset($entry['id']) || !isset($entry['filename'])) {
        $response[] = ["status" => "error", "message" => "Missing parameters"];
        continue;
    }

    $id = $entry['id'];
    $filename = $entry['filename'];

    // Validasi ID (0 atau 1 saja)
    if ($id !== 0 && $id !== 1) {
        $response[] = ["status" => "error", "message" => "Invalid ID"];
        continue;
    }

    // Update database
    $stmt = $conn->prepare("UPDATE status SET filename = ?, updated_at = NOW() WHERE id = ?");
    $stmt->bind_param("si", $filename, $id);

    if ($stmt->execute()) {
        $response[] = ["status" => "success", "message" => "Status updated successfully", "id" => $id];
    } else {
        $response[] = ["status" => "error", "message" => "Failed to update status", "id" => $id];
    }

    $stmt->close();
}

$conn->close();
echo json_encode($response);
?>
