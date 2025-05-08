<?php
define("API_KEY", "1ffa4f35131d91a3ff84a9dd20c77d88");

function authenticate_api() {
    if (!isset($_GET['api_key']) || $_GET['api_key'] !== API_KEY) {
        http_response_code(401); // Unauthorized
        echo json_encode(["status" => "error", "message" => "Invalid API Key"]);
        exit;
    }
}

// Autentikasi API Key
authenticate_api();

// Include file endpoint yang relevan
$request_method = $_SERVER['REQUEST_METHOD'];

if ($request_method === 'POST' && $_SERVER['REQUEST_URI'] === '/cms/api/upload.php') {
    include('upload.php');
} elseif ($request_method === 'GET' && $_SERVER['REQUEST_URI'] === '/cms/api/list.php') {
    include('list.php');
} elseif ($request_method === 'GET' && $_SERVER['REQUEST_URI'] === '/cms/api/download.php') {
    include('download.php');
} elseif ($request_method === 'DELETE' && $_SERVER['REQUEST_URI'] === '/cms/api/delete.php') {
    include('delete.php');
} else {
    http_response_code(405); // Method Not Allowed
    echo json_encode(["status" => "error", "message" => "Invalid request method"]);
}
?>