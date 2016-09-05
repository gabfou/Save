<?php
try
{
	$bdd = new PDO('mysql:host=mysql1.paris1.alwaysdata.com;dbname=etudemurano_project;charset=utf8', '127008_johann', 't4x5akda');
	//$bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_WARNING);
}
catch(Exception $e)
{
	die('Erreur : '.$e->getMessage());
}

function mysql_escape_mimic($inp)
{
	if(is_array($inp))
		return array_map(__METHOD__, $inp);
	if(!empty($inp) && is_string($inp)) {
		return str_replace(array('\\', "\0", "\n", "\r", "'", '"', "\x1a"), array('\\\\', '\\0', '\\n', '\\r', "\\'", '\\"', '\\Z'), $inp);
	}
	return $inp;
}

class Securite
{
	public static function bdd($string)
	{
		if(ctype_digit($string))
		{
			$string = intval($string);
		}
		else
		{
			$string = mysql_real_escape_string($string);
			$string = addcslashes($string, '%_');
		}	
		return $string;
	}
	public static function html($string)
	{
		return htmlentities($string);
	}
}

function testconect()
{
	session_start();
	if (!(isset($_SESSION['project'])))
		header("Location: project.php");
	if (!(isset($_SESSION['id_client'])) && !(isset($_SESSION['email'])))
	{
		header("Location: project.php");
	}
}
?>