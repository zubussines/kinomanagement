<?php

require_once("kon.php");

// action login
// Takes raw data from the request
$json = file_get_contents('php://input');

// Converts it into a PHP object
$data = json_decode($json, true);

$aksi = $data["action"];
$namaBarang = $data["barang"];
$kodeBarang = $data["kode"];
$stokBarang = $data["stok"];
$distributorBarang = $data["distributor"];
$alamatDistributor = $data["alamatdistrib"];
$kordinatBarang = $data["kordinat"];
$deskripsiBarang = $data["deskripsi"];
$hargaBeliBarang = $data["hargabeli"];
$hargaJualBarang = $data["hargajual"];
$satuanBarang = $data["satuan"];
$brandBarang = $data["brand"];
$modelBarang = $data["model"];


if( $aksi == "inputbarang" )
{
	$sql = "SELECT * FROM databarang WHERE kodebarang=?";
	
	$stmt = $conn->prepare( $sql );
	$stmt->bind_param( "s", $kodeBarang );
	
	
	
	$stmt->execute();
	
	$stmt->store_result();
	
	if( $stmt->num_rows < 1 )
	{
		$sql2 = "INSERT INTO `databarang` (`kodebarang`, `namabarang`, `stokbarang`, `distributorbarang`, `alamatdistributor`, `kordinatbarang`, `deskripsibarang`, `hargabelibarang`, `hargajualbarang`, `satuanbarang`, `brandbarang`, `modelbarang`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
	
		$stmt2 = $conn->prepare( $sql2 );
		$stmt2->bind_param( "ssissssiisss", $kodeBarang, $namaBarang, $stokBarang, $distributorBarang, $alamatDistributor, $kordinatBarang, $deskripsiBarang, $hargaBeliBarang, $hargaJualBarang, $satuanBarang, $brandBarang, $modelBarang );
	
	
	
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