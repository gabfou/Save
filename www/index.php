<?php
include("function.php");
include("testconect.php");
try
{
if (isset($_POST['sugestionp']))
{
	$req_pre = $bdd->prepare('UPDATE project_'.htmlspecialchars($_SESSION['project']).'_project SET sugestion = "'.htmlspecialchars($_POST['sugestionp']).'" WHERE id = '.htmlspecialchars($_SESSION['id_client']).";"); // changer user
	$req_pre->execute();
}
}
catch (PDOException $e)
{
	echo 'Error';
	die();
}
try
{
	$req_pre = $bdd->prepare('SELECT refbool, questionbool, jour, sugestion FROM project_'.htmlspecialchars($_SESSION['project']).'_project WHERE id = '.htmlspecialchars($_SESSION['id_client']).";"); // changer user		
	$req_pre->execute();
}
catch (PDOException $e)
{
	echo 'Error';
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
$sugestion = $tab['sugestion'];
if ($tab['refbool'] < 1 && $tab['questionbool'] > 0 && $tab['jour'] < 1)
	$tab['jour'] = 1;
$debut = -1;
if ($tab['refbool'] > 0)
	$debut = 0;
if ($tab['questionbool'] > 0 || ($tab['refbool'] < 1 && $tab['jour'] > 0))
	$debut = $tab['jour'];
if ($tab['jour'] > 0)
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
		<a href="index.php"><img src="logonew.png" alt="logo murano" class = logo></a>
		<h1 class = titre><?php echo str_replace("_", " ", htmlspecialchars($_SESSION['project'])); ?></h1>
	</div>
	<div class="formulaire2">
		<p><h5>Selectioner le sondage que vous voulez remplir</h5></p>
<?php
$i = -1;
while (++$i <= $tab['jour'])
{
	if ($i > 0)
		echo '<h5><a href="form.php?it='.$i.'">day '.$i.' </a><img src="Symbol_OK.svg" alt="ok" height="12px" width="12px"/></h5>';
	else if ($tab['refbool'] > 0)
		echo '<h5><a href="form.php?it='.$i.'">estimate </a><img src="Symbol_OK.svg" alt="ok" height="12px" width="12px"/></h5>';
}
$j = 0;
$i--;
while (++$i <= $tab['questionbool'])
{
	if ($i > 0 || $tab['refbool'] > 0)
	{
		if ($j == 0 && $tab['jour'] > 0)
			echo '<h5><a href="form.php?it='.$i.'">day '.$i.' </a></h5>';
		else
			echo '<h5>day '.$i.'</h5>';
	}
	$j++;
}
?>
		<h5>Your personal input</h5>
		<form method="post" action="index.php" id="formid">
			<textarea name="sugestionp" rows="5" cols="40" form="formid"><?php echo(htmlspecialchars($sugestion));?></textarea>
			<input type="submit" name="submit" value="Submit">
		</form>
	</div>
</body>

