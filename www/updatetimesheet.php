<?php
include("function.php");
include("testconect.php");
try
{
	new PDO('mysql:host=mysql1.paris1.alwaysdata.com;dbname=etudemurano_project;charset=utf8', '127008_johann', 't4x5akda');
	// $bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_WARNING);
}
catch(Exception $e)
{
	die('Erreur : '.$e->getMessage());
}
try
{
	$req_pre = $bdd->prepare('SELECT questionbool, refbool FROM project_'.htmlspecialchars($_SESSION['project']).'_project WHERE id = '.htmlspecialchars($_SESSION['id_client']).";"); // changer user		  
	$req_pre->execute();
}
catch (PDOException $e)
{
	echo 'Error : '.$e->getMessage();
	//die();
}
($tab = $req_pre->fetch());

function getrepname($arg_1)
{
	$i = -1;
	$ret = "";

	while (isset($arg_1[++$i]) && $arg_1[$i] != '_')
		$ret .= $arg_1[$i];
	return ($ret);
}

{$bdd->exec('CREATE TABLE IF NOT EXISTS project_'.htmlspecialchars($_SESSION['project']).'_reponse (id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT, idperson INTEGER, name VARCHAR(100), time INTEGER,  note INTEGER, date_info datetime, iteration INTEGER);');}
//echo 'Le jeu a bien été ajouté !';
$tab = array();
foreach ($_POST as $key => $value)
{
	$tab[] = getrepname($key);
}

$tab = array_unique($tab);

$qry = 'DELETE FROM project_'.htmlspecialchars($_SESSION['project']).'_reponse WHERE idperson = '.htmlspecialchars($_SESSION['id_client']).' AND iteration = '.htmlspecialchars($_SESSION['iteration']).';';
$bdd->exec($qry);

foreach ($tab as $name)
{
	if (!(isset($_POST[$name.'_str'])))
		$_POST[$name.'_str'] = "NA";
	if (!(isset($_POST[$name.'_time'])))
		$_POST[$name.'_time'] = 0;
	if (htmlspecialchars($_POST[$name.'_time']) > -1)
	{
		$qry = 'INSERT INTO project_'.htmlspecialchars($_SESSION['project']).'_reponse (idperson , idquestion, time, note, date_info, iteration, str) VALUE ('.htmlspecialchars($_SESSION['id_client']).' , "'.$name.'" , '.htmlspecialchars($_POST[$name.'_time']).', '.((isset($_POST[$name.'#note'])) ? htmlspecialchars($_POST[$name.'#note']) : '-1').' , NOW() , '.$_SESSION['iteration'].' , "'.htmlspecialchars($_POST[$name.'_str']).'" );';
		$bdd->exec($qry);
		//echo 'INSERT INTO project_'.$_SESSION['project'].'_reponse ('.$_SESSION['id_client'].', '.$_POST[$name."_time"].', '.$_POST[$name."_note"].', NOW());';
	}
}
if ($_SESSION['iteration'] == 0)
{
	$qry = 'UPDATE project_'.htmlspecialchars($_SESSION['project']).'_project SET refbool = 0 WHERE id = '.htmlspecialchars($_SESSION['id_client']).";";
	$bdd->exec($qry);
}

else if ($_SESSION['iteration'] == $_SESSION['max'])
{
	$qry = 'UPDATE project_'.htmlspecialchars($_SESSION['project']).'_project SET jour = jour + 1 WHERE id = '.htmlspecialchars($_SESSION['id_client']).";";
	$bdd->exec($qry);
}
?>

<head>
<link rel="stylesheet" href="style.css" />
<title>etude muranoconseil</title>
</head>
<body>
	<div class="topbar">
		<a href="index.php"><img src="logonew.png" alt="logo murano" class = logo></a>
		<h1 class = titre><?php echo str_replace("_", " ", htmlspecialchars($_SESSION['project'])); ?></h1>
	</div>


<p>Thank you for your participation!</p>

<p>Kind regards, </p>

<p>Anaïs and the MURAnO Team</p>


<p>If you have any question, you can still contact me:
<ul>
<li><a href="anais.deframond@muranoconseil.com">anais.deframond@muranoconseil.com</a></li>
<li>+33 770734938</li>
</ul></p>

