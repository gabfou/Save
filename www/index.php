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
	$req_pre = $bdd->prepare('SELECT refbool, questionbool, jour, sugestion, firstname, lastname FROM project_'.htmlspecialchars($_SESSION['project']).'_project WHERE id = '.htmlspecialchars($_SESSION['id_client']).";"); // changer user		
	$req_pre->execute();
}
catch (PDOException $e)
{
	echo 'Error';
	die();
}
($tab = $req_pre->fetch());

// if ($tab['refbool'] < 1 && $tab['questionbool'] < 1 && $tab['jour'] < 1)
// {
// 	header("Location: error_no_question.php");
// 	echo "<html></html>";
// 	flush();
// 	ob_flush();
// 	die();
// }
$firstname = $tab['firstname'];
$lastname = $tab['lastname'];
$sugestion = $tab['sugestion'];
if ($tab['refbool'] < 1 && $tab['questionbool'] > 0 && $tab['jour'] < 1)
	$tab['jour'] = 0;
$debut = -1;
if ($tab['refbool'] > 0)
	$debut = 0;
if ($tab['questionbool'] > 0 || ($tab['refbool'] < 1 && $tab['jour'] > 0))
	$debut = $tab['jour'];
if ($tab['jour'] > 0)
	$debut = $tab['jour'];

$_SESSION['max'] = ($tab['questionbool'] > $tab['jour']) ? $tab['jour'] + 1 : $tab['jour'];

?>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<head>
	<link rel="stylesheet" href="style.css" />
	<title><?php echo htmlspecialchars($_SESSION['project']);?></title>
	<!-- <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.97.7/css/materialize.min.css"> -->
</head>
<body>
	<div class="topbar">
		<a href="index.php"><img src="logonew.png" alt="logo murano" class = logo></a>
		<h1 class = titre><?php echo str_replace("_", " ", htmlspecialchars($_SESSION['project'])); ?></h1>
		<img src="Kérastase_logo.png" alt="logo murano" class = "logopetit logop1">
		<img src="L’Oréal-Logos-HD.jpg" alt="logo murano" class = "logopetit logop2">
		<img src="matrix_logo.png" alt="logo murano" class = "logopetit logop3">
		<img src="Redken-Logo.jpg" alt="logo murano" class = "logopetit logop4">
	</div>
	<div class="index">

<?php
$req_pre = $bdd->prepare('SELECT introindex FROM all_config WHERE project_name = "'.htmlspecialchars($_SESSION['project']).'";');
$req_pre->execute();
($tab2 = $req_pre->fetch());
$intro = $tab2['introindex'];
$intro = str_replace("__%nb__", $questionbool + $refbool, $intro);
$intro = str_replace("__%p__", $firstname, $intro);
$intro = str_replace("__%n__", $lastname, $intro);
echo $intro;
$i = -1;
while (++$i <= $tab['jour'])
{
	if ($i > 0)
		echo '<h5>Time Sheet Day '.$i.' <img src="Symbol_OK.svg" alt="ok" height="12px" width="12px"/></h5>';
	else if ($tab['refbool'] > 0 && $i == 0)
		echo '<h5><a href="form.php?it='.$i.'">Estimation </a></h5>';
}
$j = 0;
$i--;
while (++$i <= $tab['questionbool'])
{
	if ($i > 0)
	{
		if ($j == 0 && $tab['refbool'] == 0)
			echo '<h5><a href="form.php?it='.$i.'">Time Sheet Day '.$i.' </a></h5>';
		else
			echo '<h5>Time Sheet Day '.$i.'</h5>';
	}
	$j++;
}
?>

		<Br/>If you have some suggestions, ideas or best practices to share with us, please feel free to complete to the space provided below:
		<form method="post" action="index.php" id="formid">
			<textarea name="sugestionp" rows="5" cols="40" form="formid"><?php echo(htmlspecialchars($sugestion));?></textarea>
			<input type="submit" name="submit" value="Submit">
		</form>
		<p>If you encounter any difficulty or if you have any question, please contact me:<ul>
		<li><a href="mailto:anais.deframond@muranoconseil.com">anais.deframond@muranoconseil.com</a></li>
		<li>+33 770734938</li></ul></p>
	</div>
</body>

