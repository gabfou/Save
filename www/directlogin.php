<?php
if (isset($_GET['s']) && isset($_GET['p']))
{
	session_set_cookie_params(3600 * 2);
	session_start();
	$_SESSION['id_client'] = $_GET['p'];
	$_SESSION['project'] = $_GET['s'];
	header("Location: index.php");
	echo "<html></html>";
	flush();
	ob_flush();
	die();
}
?>