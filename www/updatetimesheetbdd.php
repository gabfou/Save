<?php
if (isset($_POST['username']) && isset($_POST['passwd']) && $_POST['username'] == 'hj18972-ovh' && $_POST['passwd'] == 't4x5akda')
{
	try
	{
		$bdd = new PDO('mysql:host=mysql51-37.perso;dbname=muranocobdd;charset=utf8', 'muranocobdd', 'Gabriel63');
	}
	catch(Exception $e)
	{
		die('Erreur : '.$e->getMessage());
	}
	$bdd->exec("SELECT * FROM update_*");
	while ($data = $bdd->fetch())
	{
		echo $data['idperson']." ".$data['name']." ".$data['time']." ".$data['note']." ".$data['date']."\n";
	}
	//$bdd->exec("DROP IF EXIST update_*");
}
?>