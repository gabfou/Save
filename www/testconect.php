<?php
	header( 'Content-type: text/html; charset=utf-8' );
	session_start();
	if (!(isset($_SESSION['project'])))
	{
		header("Location: login.php");
		echo "<html></html>";
		flush();
		ob_flush();
		exit;
	}
	if (!(isset($_SESSION['id_client'])))
	{
		header("Location: login.php");
		echo "<html></html>";
		flush();
		ob_flush();
		exit;
	}
?>