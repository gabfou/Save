<?php
include("function.php");
include("testconect.php");

try
{
	$req_pre = $bdd->prepare('SELECT refbool FROM project_'.htmlspecialchars($_SESSION['project']).'_project WHERE id = '.htmlspecialchars($_SESSION['id_client']).";"); // changer user		
	$req_pre->execute();
}
catch (PDOException $e)
{
	echo 'Error : '.$e->getMessage();
	die();
}
($tab = $req_pre->fetch());
if ($tab['refbool'] != 0)
{
	$_SESSION['iteration'] = 0;
	header("Location: form.php");
	echo "<html></html>";
	flush();
	ob_flush();
	die();
}

try
{
	$req_pre2 = $bdd->prepare('SELECT questionbool, jour FROM project_'.htmlspecialchars($_SESSION['project']).'_project WHERE id = '.htmlspecialchars($_SESSION['id_client']).";");
	$req_pre2->execute();
}
catch (PDOException $e)
{
	echo 'Error : '.$e->getMessage();
	die();
}
($tab2 = $req_pre2->fetch());
if ($tab2['questionbool'] != 0)
{
	if ($tab2['jour'] < 1)
		$tab2['jour'] = 1;
	$_SESSION['iteration'] = $tab2['jour'];
	$req_pre2 = $bdd->prepare('UPDATE  project_'.htmlspecialchars($_SESSION['project']).'_project SET jour = '.htmlspecialchars($_SESSION['iteration'] + 1).";");
	$req_pre2->execute();
	header("Location: form.php");
	echo "<html></html>";
	flush();
	ob_flush();
	die();
}

header("Location: error_no_question.php");
echo "<html></html>";
flush();
ob_flush();
die();
?>