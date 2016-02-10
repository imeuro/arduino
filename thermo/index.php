<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Gestione Thermo</title>

    <link href="css/reset.css" rel="stylesheet">
    <!-- Bootstrap -->
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <link href="css/thermo.css" rel="stylesheet">

    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>
  <body>
  <?php
  $strTemp= file_get_contents("./data/curTemp"); 
  $strMode= file_get_contents("./data/curMode");
  $strProg= file_get_contents("./data/curProgram");
  $strTemp = round($strTemp, 1);
  ?>
  <header class="text-center clearfix">
   <h1><span class="glyphicon glyphicon-home" aria-hidden="true"></span>&nbsp;&nbsp;Gestione Thermo</h1>
  </header>
  <div class="container page-content">

    <div class="col-xs-12 col-sm-6 col-md-4 col-md-push-2 text-center margin-bottom">
      <div class=" well well-lg">
         Current Temp.<br />
         <strong class="very-strong"><?php echo $strTemp; ?>°C</strong>
       </div>
    </div>
    <div class="col-xs-12 col-sm-6 col-md-4 col-md-push-2 text-center margin-bottom">
      <div class=" well well-lg">Status<br />
        <strong class="very-strong">
      	<?php echo $strMode; ?>
      	</strong>
      </div>
    </div>

    <div class="col-xs-12 margin-bottom" id="setMode">

      <h4>Set Mode:</h4>
      <div class="btn-group btn-group-justified" data-toggle="buttons">
        <label class="btn btn-danger">
          <input type="radio" name="mode" autocomplete="off" id="off" value="OFF" /><strong class="fairly-strong">OFF</strong>
        </label>
        <label class="btn btn-warning">
          <input type="radio" name="mode" autocomplete="off" id="man" value="MAN"><strong class="fairly-strong">MAN</strong>
        </label> 
        <label class="btn btn-success">
          <input type="radio" name="mode" autocomplete="off" id="auto" value="AUTO" /><strong class="fairly-strong">AUTO</strong>
        </label>
      </div>

    </div>

    <div class="col-xs-12 hidden margin-bottom" id="setProg">

      <h4>Set Program:</h4>
      <div class="btn-group btn-group-justified" data-toggle="buttons">
        <label class="btn btn-primary btn-warning">
          <input type="radio" name="program" autocomplete="off" id="1" value="T1"><strong class="fairly-strong">T1</strong><br />8.0&deg;C
        </label>
        <label class="btn btn-primary btn-warning">
          <input type="radio" name="program" autocomplete="off" id="2" value="T2"><strong class="fairly-strong">T2</strong><br />17.5&deg;C
        </label>
        <label class="btn btn-primary btn-warning">
          <input type="radio" name="program" autocomplete="off" id="3" value="T3"><strong class="fairly-strong">T3</strong><br />19.5&deg;C
        </label>
      </div>

    </div>
 
    <div class="col-xs-12 margin-bottom"> 

  		<form action="./data/writer.php" method="POST" id="Temp" class="row">
        <input type="hidden" name="mode" value="" />
  			<input type="hidden" name="program" value="" />
  			<br />
  			<button type="submit" class="btn btn-lg btn-default col-xs-12 col-sm-6 col-sm-push-3 col-md-4 col-md-push-4" value="save"><span class="glyphicon glyphicon-floppy-disk"></span> CONFIRM</button>
  		</form>

    </div>
   
  </div><!-- / container page-content -->



    <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="js/bootstrap.min.js"></script>
    <script src="js/thermo.js"></script>
  </body>
</html>
