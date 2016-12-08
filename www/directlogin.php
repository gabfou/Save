<?php
if (isset($_GET['s']) && isset($_GET['p']))
{
	session_set_cookie_params(3600 * 5);
	session_start();
	$_SESSION['id_client'] = $_GET['p'];
	$_SESSION['project'] = $_GET['s'];
	if ($_SESSION['project'] == "DMI_LEAD_CHANGE")
	{
		$_SESSION['project'] = "DMI_LEAD_CHANGE_SURVEY";
	}
	header("Location: index.php");
	echo "<html></html>";
	flush();
	ob_flush();
	die();
}
?>