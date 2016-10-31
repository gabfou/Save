<?php
include("function.php");
include("testconect.php");




try
{
	$req_pre = $bdd->prepare('SELECT refbool, questionbool, jour FROM project_'.htmlspecialchars($_SESSION['project']).'_project WHERE id = '.htmlspecialchars($_SESSION['id_client']).";"); // changer user		
	$req_pre->execute();
}
catch (PDOException $e)
{
	echo 'Error : '.$e->getMessage();
	die();
}
($tab = $req_pre->fetch());

if ($tab['refbool'] < 1 && $tab['questionbool'] < 1 && $tab['jour'] < 1)
{
	header("Location: error_no_question.php");
	echo "<html></html>";
	flush();
	ob_flush();
	die();
}

if ($tab['refbool'] < 1 && $tab['questionbool'] > 0 && $tab['jour'] < 1)
	$tab['jour'] = 1;
$debut = -1;
if ($tab['refbool'] > 0)
	$debut = 0;
if ($tab['questionbool'] > 0)
	$debut = $tab['jour'];

$_SESSION['max'] = $debut;

?>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<head>
	<link rel="stylesheet" href="style.css" />
	<title>etude muranoconseil</title>
	<!-- <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.97.7/css/materialize.min.css"> -->
</head>
<body>
	<div class="topbar">
		<img src="logo.jpeg" alt="logo murano" class = logo>
		<!-- <h1>MURANO</h1> -->
	</div>
	<div class="formulaire2">
		<p><h5>Selectioner le sondage que vous voulez remplir</h5></p>
<?php
$i = -1;
while (++$i <= $debut)
{
	echo '<h5><a href="form.php?it='.$i.'">jour '.$i.'</a></h5>';
}
while (++$i <= $debut + $tab['questionbool'])
{
	echo '<h5>jour '.$i.'</h5>';
}
?>

	</div>
</body>
