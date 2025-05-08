<?php
require_once 'db.php';

// Fungsi untuk menghasilkan API Key secara acak
function generate_api_key() {
    return bin2hex(random_bytes(16)); // 32 karakter hexadecimal
}

// Membuat API Key baru
$api_key = generate_api_key();

// Simpan API Key ke dalam database
$conn = getDBConnection();
$stmt = $conn->prepare("INSERT INTO api_keys (api_key) VALUES (?)");
$stmt->bind_param("s", $api_key);
$stmt->execute();
$stmt->close();
$conn->close();

// Menampilkan API Key yang baru dibuat
echo "API Key yang baru: " . $api_key;
?>
