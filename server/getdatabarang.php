<?php

require_once("kon.php");

// action login
// Takes raw data from the request
$json = file_get_contents('php://input');

// Converts it into a PHP object
$data = json_decode($json, true);

$aksi = $data["action"];
$kodebarang = $data["kode"];


if( $aksi == "getdatabarang" )
{
	$sql = "SELECT * FROM databarang WHERE kodebarang = '$kodebarang'";
	
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