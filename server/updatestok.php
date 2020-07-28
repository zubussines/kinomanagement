<?php

require_once("kon.php");

// Takes raw data from the request
$json = file_get_contents('php://input');

// Converts it into a PHP object
$data = json_decode($json, true);

$aksi = $data["action"];
$dataSize = $data["size"];
$rowEfect = 0;

// Real Code
if( $aksi == "updatestok" )
{
	$sql = "UPDATE databarang SET stokbarang = stokbarang - ? WHERE kodebarang =?";
	
	$stmt = $conn->prepare( $sql );
	 
	for( $i = 0; $i < $dataSize; $i++ )
	{
		$stmt->bind_param( "is", $data["data".$i][1], $data["data".$i][0] );
		
		$stmt->execute();
	
		$stmt->store_result();
		
		if( $conn->affected_rows < 1 )
		{
			$rowEfect = 0;
		}else{
			$rowEfect++;
		}
	}
	if( $rowEfect == $dataSize )
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