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
if (($tab['questionbool'] == 0 && $_SESSION['iteration'] >= 1) || ($tab['refbool'] == 0 && $_SESSION['iteration'] == 0))
{
	header("Location: error_no_question.php");
	echo "<html></html>";
	flush();
	ob_flush();
	die();
}
?>

<head>
<link rel="stylesheet" href="style.css" />
<title>etude muranoconseil</title>
</head>
<body>
<div class="topbar">
	<img src="logo.jpeg" alt="logo murano" class = logo>
</div>

<p> Merci de votre de participation. </p>
<p> Cordialement toute l'équipe de murano conseil </p>

<?php


function getrepname($arg_1)
{
	$i = -1;
	$ret = "";

	while (isset($arg_1[++$i]) && $arg_1[$i] != '#')
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

foreach ($tab as $name)
{
	if (!(isset($_POST[$name.'#str'])))
		$_POST[$name.'#str'] = "NA";
	if (!(isset($_POST[$name.'#time'])))
		$_POST[$name.'#time'] = 0;
	if (htmlspecialchars($_POST[$name.'#time']) > -1)
	{		$qry = 'INSERT INTO project_'.htmlspecialchars($_SESSION['project']).'_reponse (idperson , idquestion, time, note, date_info, iteration, str) VALUE ('.htmlspecialchars($_SESSION['id_client']).' , "'.$name.'" , '.htmlspecialchars($_POST[$name.'#time']).', '.((isset($_POST[$name.'#note'])) ? htmlspecialchars($_POST[$name.'#note']) : '-1').' , NOW() , '.$_SESSION['iteration'].' , "'.htmlspecialchars($_POST[$name.'#str']).'" );';
		$bdd->exec($qry);
		//echo 'INSERT INTO project_'.$_SESSION['project'].'_reponse ('.$_SESSION['id_client'].', '.$_POST[$name."_time"].', '.$_POST[$name."_note"].', NOW());';
	}
}
if ($_SESSION['iteration'] == 0)
{
	$qry = 'UPDATE project_'.htmlspecialchars($_SESSION['project']).'_project SET refbool = refbool - 1 WHERE id = '.htmlspecialchars($_SESSION['id_client']).";";
}
else
	$qry = 'UPDATE project_'.htmlspecialchars($_SESSION['project']).'_project SET questionbool = questionbool - 1 WHERE id = '.htmlspecialchars($_SESSION['id_client']).";";
$bdd->exec($qry);
?>