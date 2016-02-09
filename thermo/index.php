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
  $strProg= file_get_contents("./data/curTx");
  $strTemp = round($strTemp, 1);
  ?>
  <header class="text-center clearfix">
   <h1><span class="glyphicon glyphicon-home" aria-hidden="true"></span>&nbsp;&nbsp;Gestione Thermo</h1>
  </header>
  <div class="container page-content">

    <div class="col-xs-12 col-sm-6 col-md-4 text-center">
      <div class=" well well-lg">
         Current Temp.<br />
         <strong class="very-strong"><?php echo $strTemp; ?>°C</strong>
       </div>
    </div>
    <div class="col-xs-12 col-sm-6 col-md-4 text-center">
      <div class=" well well-lg">
         Status<br />
         <strong class="very-strong">
	<?php
	switch($strProg) {
		case "0" :
			echo "OFF";
			break;
		case "1" :
			echo "MAN/T1";
			break;
		case "2" :
			echo "MAN/T2";
			break;
		case "3" :
			echo "MAN/T3";
			break;
		case "9" :
			echo "Auto";
			break;
	}
	?>
	</strong><br/>
	 OFF/AUTO/MAN
      </div>
    </div>

    <div class="col-xs-12">
      <h3>Set mode:</h3>
      <div class="btn-group btn-group-justified" role="group" aria-label="gigi">
        <div class="btn-group" role="group">
          <button type="button" class="btn btn-default" onclick="$('#Temp input[name=status]').val('OFF');"><strong class="very-strong">OFF</strong></button>
        </div>
        <div class="btn-group" role="group">
          <button type="button" class="btn btn-default" onclick="$('#Temp input[name=status]').val('AUTO');"><strong class="very-strong">AUTO</strong></button>
        </div>
        <div class="btn-group" role="group">
          <button type="button" class="btn btn-default" onclick="$('#Temp input[name=status]').val('MAN');"><strong class="very-strong">MAN</strong></button>
        </div>      
      </div>

    <div class="col-xs-12">
      <h3>Set Temperature:</h3>
      <div class="btn-group btn-group-justified" role="group" aria-label="gigi">
        <div class="btn-group" role="group">
          <button type="button" class="btn btn-default" onclick="$('#Temp input[name=program]').val('1');"><strong class="very-strong">T1</strong><br />8.0&deg;C</button>
        </div>
        <div class="btn-group" role="group">
          <button type="button" class="btn btn-default" onclick="$('#Temp input[name=program]').val('2');"><strong class="very-strong">T2</strong><br />17.5&deg;C</button>
        </div>
        <div class="btn-group" role="group">
          <button type="button" class="btn btn-default" onclick="$('#Temp input[name=program]').val('3');"><strong class="very-strong">T3</strong><br />19.5&deg;C</button>
        </div>
      </div>

    </div>
 
    <div class="col-xs-12">   
		<form action="./data/writer.php" type="post" id="Temp">
			<input type="hidden" name="program" value="" />
			<input type="hidden" name="status" value="" />
			<button type="submit" class="btn btn-lg" value="save">save</button>
		</form>
   </div>
   
  </div><!-- / container page-content -->



    <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="js/bootstrap.min.js"></script>
  </body>
</html>
