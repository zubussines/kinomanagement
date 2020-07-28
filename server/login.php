<?php

require_once("kon.php");

// action login
// Takes raw data from the request
$json = file_get_contents('php://input');

// Converts it into a PHP object
$data = json_decode($json, true);

$aksi = $data["action"];
$username = $data["username"];
$hwid = $data["hwid"];


if( $aksi == "login" )
{
	$sql = "SELECT * FROM datauser WHERE username=? AND hwid=?";
	
	$stmt = $conn->prepare( $sql );
	$stmt->bind_param( "ss", $username, $hwid );
	
	
	
	$stmt->execute();
	
	$stmt->store_result();
	
	if( $stmt->num_rows > 0 )
	{
		echo "success";
	}else{
		echo "failed";
	}
}else{
	echo "test";
}

$conn->close();
?>