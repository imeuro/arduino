<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Gestione Thermo</title>

    <link href="../css/reset.css" rel="stylesheet">
    <!-- Bootstrap -->
    <link href="../css/bootstrap.min.css" rel="stylesheet">
    <link href="../css/thermo.css" rel="stylesheet">

    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>
  <body>
	<script type="text/javascript">
	//window.setTimeout(function() {
	//	location.href = '../index.php';
	//}, 2000);
	</script>

<?php
$status=$_POST['status'];
$program=$_POST['program'];

if  ($status) :
	$fp = fopen('curStatus',w);
	fwrite($fp,$status);
	fclose();
endif;

if  ($program) :
	$fp = fopen('curTx',w);
	fwrite($fp,$program);
	fclose();
endif;
?>

  <header class="text-center clearfix">
   <h1><span class="glyphicon glyphicon-home" aria-hidden="true"></span>&nbsp;&nbsp;Gestione Thermo</h1>
  </header>
  <div class="container page-content">

    <div class="col-xs-12 text-center">
      Updating...
    </div>

  </div><!-- / container page-content -->





    <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="../js/bootstrap.min.js"></script>
  </body>
</html>
