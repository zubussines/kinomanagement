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
	$sql = "SELECT * FROM datauser WHERE username = '".$username."' AND hwid = '".$hwid."'";
	
	$hasil = conn->query($sql);
	
	if( hasil->num_rows > 0 )
	{
		echo "success";
	}else{
		echo "failed";
	}
}
?>