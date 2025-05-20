<?php
// Koneksi ke database
$host = "localhost";
$user = "root";
$password = "";
$dbname = "video_db";

$conn = new mysqli($host, $user, $password, $dbname);

// Periksa koneksi
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Hapus file jika ada permintaan
if (isset($_GET['delete_id'])) {
    $id = intval($_GET['delete_id']);
    
    // Ambil informasi file berdasarkan ID
    $sql = "SELECT filepath FROM videos WHERE id = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("i", $id);
    $stmt->execute();
    $result = $stmt->get_result();
    
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        $filepath = $row['filepath'];
        
        // Hapus file fisik
        if (file_exists($filepath)) {
            unlink($filepath);
        }
        
        // Hapus data dari database
        $deleteSql = "DELETE FROM videos WHERE id = ?";
        $deleteStmt = $conn->prepare($deleteSql);
        $deleteStmt->bind_param("i", $id);
        $deleteStmt->execute();
        
        echo "File berhasil dihapus.";
    } else {
        echo "File tidak ditemukan.";
    }
}

// Ambil semua data video
$sql = "SELECT id, filename, filepath FROM videos";
$result = $conn->query($sql);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Daftar Video</title>
</head>
<body>
    <h1>Daftar Video</h1>
    <table border="1">
        <tr>
            <th>Filename</th>
            <th>Aksi</th>
        </tr>
        <?php
        if ($result->num_rows > 0) {
            while ($row = $result->fetch_assoc()) {
                echo "<tr>";
                echo "<td>" . htmlspecialchars($row['filename']) . "</td>";
                echo "<td>";
                echo "<a href='" . htmlspecialchars($row['filepath']) . "' download>Download</a> | ";
                echo "<a href='?delete_id=" . $row['id'] . "' onclick='return confirm(\"Apakah Anda yakin ingin menghapus file ini?\")'>Hapus</a>";
                echo "</td>";
                echo "</tr>";
            }
        } else {
            echo "<tr><td colspan='2'>Tidak ada video tersedia.</td></tr>";
        }
        ?>
    </table>
</body>
</html>
