<?php

require_once("kon.php");

// action login
// Takes raw data from the request
//$json = file_get_contents('php://input');

$json = '{
			"action" : "getdatamutasi",
			"tanggal" : "17",
			"bulan" : "7"
			}';

// Converts it into a PHP object
$data = json_decode($json, true);

$aksi = $data["action"];
$tgl = $data["tanggal"];
$bulan = $data["bulan"];
$pemasukanHariIni = 0;
$pemasukanBulanIni =0;
$pengeluaranHariIni = 0;
$pengeluaranBulanIni =0;
$hasilHarian = 0;
$hasilBulanan = 0;
$untungHarian = 0;
$untungBulanan= 0;
$untungBersihHariIni = 0;
$untungBersihBulanIni = 0;


if( $aksi == "getdatamutasi" )
{
	// pengeluaran
	$sql = "SELECT nominal FROM pengeluaran WHERE tanggal = '$tgl'";
	
	$result = mysqli_query($conn, $sql);
	
    while($row = mysqli_fetch_assoc($result) )
		{  
			$pengeluaranHariIni = $pengeluaranHariIni + $row["nominal"];
        }
	
	
	$sql = "SELECT nominal FROM pengeluaran WHERE bulan = '$bulan'";
	
	$result = mysqli_query($conn, $sql);
	
    while($row = mysqli_fetch_assoc($result) )
		{  
			$pengeluaranBulanIni = $pengeluaranBulanIni + $row["nominal"];
        }
	
	
	// pemasukan
	$sql = "SELECT nominal FROM pemasukan WHERE tanggal = '$tgl'";
	
	$result = mysqli_query($conn, $sql);
	
    while($row = mysqli_fetch_assoc($result) )
		{  
			$pemasukanHariIni = $pemasukanHariIni + $row["nominal"];
        }
		
	
	$sql = "SELECT nominal FROM pemasukan WHERE bulan = '$bulan'";
	
	$result = mysqli_query($conn, $sql);
	
    while($row = mysqli_fetch_assoc($result) )
		{  
			$pemasukanBulanIni = $pemasukanBulanIni + $row["nominal"];
        }
	
	
	// untung dan hasil
	$sql = "SELECT nominal, untung FROM mutasi WHERE tanggal = '$tgl'";
	
	$result = mysqli_query($conn, $sql);
	
    while($row = mysqli_fetch_assoc($result) )
		{  
			$untungHarian = $untungHarian + $row["untung"];
			$hasilHarian = $hasilHarian + $row["nominal"];
        }
	
	
	$sql = "SELECT nominal, untung FROM mutasi WHERE bulan = '$bulan'";
	
	$result = mysqli_query($conn, $sql);
	
    while($row = mysqli_fetch_assoc($result) )
		{  
			$untungBulanan = $untungBulanan + $row["untung"];
			$hasilBulanan = $hasilBulanan + $row["nominal"];
        }
	
	$untungBersihHariIni = $untungHarian - $pengeluaranHariIni + $pemasukanHariIni;
	$untungBersihBulanIni = $untungBulanan - $pengeluaranBulanIni + $pemasukanBulanIni;
	
	echo '{
		"hasilharian" : "'.$hasilHarian.'",
		"hasilbulanan" : "'.$hasilBulanan.'",
		"untungharian" : "'.$untungHarian.'",
		"untungbulanan" : "'.$untungBulanan.'",
		"pengeluaranharian" : "'.$pengeluaranHariIni.'",
		"pengeluaranbulanan" : "'.$pengeluaranBulanIni.'",
		"pemasukanharian" : "'.$pemasukanHariIni.'",
		"pemasukanbulanan" : "'.$pemasukanBulanIni.'",
		"untungbersihharian" : "'.$untungBersihHariIni.'",
		"untungbersihbulanan" : "'.$untungBersihBulanIni.'"
	}';
	
}else{
	echo "test";
}

$conn->close();
?>