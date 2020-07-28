<?php

require_once("kon.php");

// action login
// Takes raw data from the request
$json = file_get_contents('php://input');

// Converts it into a PHP object
$data = json_decode($json, true);

$aksi = $data["action"];
$kodebarang = $data["kode"];


if( $aksi == "tampilbarangbykode" )
{
	$sql = "SELECT * FROM databarang WHERE kodebarang = '$kodebarang'";
	
	$result = mysqli_query($conn, $sql);
	
    $json_array = array();
	
    while($row = mysqli_fetch_assoc($result) )
		{  
			$json_array[] = $row;
        }  
    echo json_encode($json_array);
	
}elseif( $aksi == "tampilbarangbybrand" )
{
	$sql = "SELECT * FROM databarang WHERE brandbarang = '$kodebarang'";
	
	$result = mysqli_query($conn, $sql);
	
    $json_array = array();
	
    while($row = mysqli_fetch_assoc($result) )
		{  
			$json_array[] = $row;
        }  
    echo json_encode($json_array);
	
}elseif( $aksi == "tampilbarangbymodel" )
{
	$sql = "SELECT * FROM databarang WHERE modelbarang = '$kodebarang'";
	
	$result = mysqli_query($conn, $sql);
	
    $json_array = array();
	
    while($row = mysqli_fetch_assoc($result) )
		{  
			$json_array[] = $row;
        }  
    echo json_encode($json_array);
	
}elseif( $aksi == "tampilbarangemergency" )
{
	$sql = "SELECT * FROM databarang WHERE stokbarang < 2";
	
	$result = mysqli_query($conn, $sql);
	
    $json_array = array();
	
    while($row = mysqli_fetch_assoc($result) )
		{  
			$json_array[] = $row;
        }  
    echo json_encode($json_array);
	
}else{
	echo "test";
}

$conn->close();
?>