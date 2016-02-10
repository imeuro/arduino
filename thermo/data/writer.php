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
// recuperone
if ( isset($_POST['mode']) && !empty($_POST['mode']) ) :
  $mode=$_POST['mode'];
endif;
if ( isset($_POST['program']) && !empty($_POST['program']) ) :
  $program=$_POST['program'];
endif;

// scrivone su file (why???)
if (isset($mode)) :
	$fp = fopen("curMode","w") or die("Sorry, unable to open file!");
	fwrite($fp,$mode);
	fclose($fp);
endif;

if (isset($program)) :
	$fp = fopen("curProgram","w") or die("Sorry, unable to open file!");
	fwrite($fp,$program);
	fclose($fp);
endif;

// e invione a Arduino via serial port
 $serialPort = "/dev/ttyACM0";

if (isset($mode)) {
  switch ($mode) {
    case OFF:
      $fp =fopen($serialPort, "w") or die("Sorry, unable to communicate Mode via serial port");
      fwrite($fp, 0); /* this is the number that it will write */
      fclose($fp);
    break;
    case AUTO:
      $fp =fopen($serialPort, "w") or die("Sorry, unable to communicate Mode via serial port");
      fwrite($fp, 9); /* this is the number that it will write */
      fclose($fp);
    break;
    case MAN:
        $fp =fopen($serialPort, "w") or die("Sorry, unable to communicate Mode via serial port");
      if (isset($program)) {
        fwrite($fp, $program); /* this is the number that it will write */
      } else {
        fwrite($fp, 1);
        echo 'arbitrarily sticking to T1, come back and tell me what program you need';
      }
        fclose($fp);
    break;
    default:
      die('Crap, something went wrong...');
  }
}




?>

  <header class="text-center clearfix">
   <h1><span class="glyphicon glyphicon-home" aria-hidden="true"></span>&nbsp;&nbsp;Gestione Thermo</h1>
  </header>
  <div class="container page-content">

    <div class="col-xs-12 col-sm-6 col-sm-push-3 text-center">
      <?php 
      if ( isset($mode) ) : 
        echo '<h4 class="alert alert-success" role="success">';
        echo '<span class="glyphicon glyphicon-ok-sign"></span> <b>Done!</b></h4>';
        echo '<p>MODE is set to <h2>'.$mode.'</h2></p><br />';
      endif;
      if ( isset($program) ) : 
        echo '<h4 class="alert alert-success" role="success">';
        echo '<span class="glyphicon glyphicon-ok-sign"></span> <b>Done!</b></h4>';
        echo '<p>PROGRAM is set to <h2>'.$program.'</h2></p><br />';
      endif;
      if ( !isset($mode) && !isset($program)  ):
        echo '<h4 class="alert alert-warning" role="warning">';
        echo '<span class="glyphicon glyphicon-remove-circle"></span> Error!</h4>';
        echo 'Nothing has changed so far...<br />';
      endif;
      ?>
      <br />
      <hr class="col-xs-12" />
      <p class="clearfix"><a href="../" class="btn btn-default"><span class="glyphicon glyphicon-chevron-left"></span> Back to the previous page</a></p>
    </div>

  </div><!-- / container page-content -->





    <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="../js/bootstrap.min.js"></script>
  </body>
</html>
