<?php
	header( 'Content-type: text/html; charset=iso-8859-1' );
	session_start();
	if (!(isset($_SESSION['project'])))
	{
	    header("Location: project.php");
		echo "<html></html>";
		flush();
		ob_flush();
		exit;
	}
	if (!(isset($_SESSION['id_client'])))
	{
	    header("Location: login.php?project__project=".$_SESSION['project']);
		echo "<html></html>";
		flush();
		ob_flush();
		exit;
	}
?>