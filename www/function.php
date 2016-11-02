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

function recupallgroupfils($groupid, $bdd, $project_name)
{
	$ret = array();
	$ret[] = $groupid;
	$req_pre = $bdd->prepare('SELECT id FROM project_'.$project_name.'_groupe WHERE groupparent = '.$groupid.";");
	$req_pre->execute();
	$fetch = $req_pre->fetchall();
	foreach ($fetch as $key => $value)
	{
		$ret = array_merge($ret, recupallgroupfils($value['id'], $bdd, $project_name));
	}
	return ($ret);
}

function strallgroupfilsforsql($groupid, $bdd, $project_name)
{
	$i = 0;
	$ret = "";
	$tabid = recupallgroupfils($groupid, $bdd, $project_name);
	print_r($tabid);
	foreach ($tabid as $key => $value)
	{
		if ($i === 0)
		{
			$ret .= "groupid = ".$value;			
			$i++;
		}
		else
			$ret .= " OR groupid = ".$value;
	}
	return ($ret);
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