<?php
include("function.php");
include("testconect.php");
try{
	$req_pre = $bdd->prepare('SELECT refbool FROM project_'.htmlspecialchars($_SESSION['project']).'_project WHERE id = '.htmlspecialchars($_SESSION['id_client']).";"); // changer user		
	$req_pre->execute();
	}
catch (PDOException $e) {
	echo 'Error : '.$e->getMessage();
	exit;
}
header( 'Content-type: text/html; charset=utf-8' );
($tab = $req_pre->fetch());
if ($tab['refbool'] != 0)
{
	header("Location: index_ref.php");
	echo "<html></html>";
	flush();
	ob_flush();
	exit;
}
try{
	$req_pre2 = $bdd->prepare('SELECT questionbool FROM project_'.htmlspecialchars($_SESSION['project']).'_project WHERE id = '.htmlspecialchars($_SESSION['id_client']).";"); // changer user		
	$req_pre2->execute();
	}
catch (PDOException $e) {
	echo 'Error : '.$e->getMessage();
	exit;
}
($tab2 = $req_pre2->fetch());
if ($tab2['questionbool'] != 0)
{
	header("Location: index.php");
	echo "<html></html>";
	flush();
	ob_flush();
	exit;
}
header("Location: error_no_question.php");
echo "<html></html>";
flush();
ob_flush();
exit;
?>