<?php

require_once("kon.php");

// action login
// Takes raw data from the request
$json = file_get_contents('php://input');

// Converts it into a PHP object
$data = json_decode($json, true);

$aksi = $data["action"];
$idmutasi = $data["id"];
$jam = $data["jam"];
$tanggal = $data["tanggal"];
$bulan = $data["bulan"];
$tahun = $data["tahun"];
$nominal = $data["nominal"];
$pelanggan = $data["pelanggan"];
$kembalian = $data["kembalian"];
$uangpelanggan = $data["uangpelanggan"];
$untung = $data["untung"];
$potongan = $data["potongan"];
$jenis = $data["jenis"];
$judultransaksi = $data["judul"];


if( $aksi == "updatemutasi" )
{
	$sql = "SELECT * FROM mutasi WHERE idmutasi=?";
	
	$stmt = $conn->prepare( $sql );
	$stmt->bind_param( "s", $kodeBarang );
	
	
	
	$stmt->execute();
	
	$stmt->store_result();
	
	if( $stmt->num_rows < 1 )
	{
		$sql2 = "INSERT INTO `mutasi` (`idmutasi`, `jam`, `tanggal`, `bulan`, `tahun`, `nominal`, `pelanggan`, `kembalian`, `uangpelanggan`, `untung`, `potongan`, `jenis`, `judultransaksi`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
	
		$stmt2 = $conn->prepare( $sql2 );
		$stmt2->bind_param("siiiiisiiiiss", $idmutasi, $jam, $tanggal, $bulan, $tahun, $nominal, $pelanggan, $kembalian, $uangpelanggan, $untung, $potongan, $jenis, $judultransaksi );
	
	
	
		$stmt2->execute();
	
		$stmt2->store_result();
	
		if( $conn->affected_rows > 0 )
			{
				echo "success";
			}else{
				echo "failed";
			}
	}else{
		echo "ready";
	}
	
	
}else{
	echo "test";
}

$conn->close();
?>