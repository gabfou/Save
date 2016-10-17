

<?php
	include("www/function.php");

function maildebase($to, $subject, $body)
{
	$headers   = array();
	$headers[] = "MIME-Version: 1.0";
	$headers[] = "Content-type: text/plain; charset=utf-8";
	$headers[] = "From: Etudesmuranoconseil <etudemurano@alwaysdata.net>";
	//$headers[] = "Bcc: JJ Chong <bcc@domain2.com>";
	//$headers[] = "Reply-To: Recipient Name <receiver@domain3.com>";
	$headers[] = "Subject: {".$subject."}";
	$headers[] = "X-Mailer: PHP/".phpversion();

	mail($to, $subject, $body, implode("\r\n", $headers));
}

// maildebase("web-jbiqHB@mail-tester.com", "etude muranoconseil", "Bonjour dans le cadre de notre études veuillez repondre au formulaire à l'adresse suivante : http://etudemurano.alwaysdata.net/login.php"."\r\n\r\nMURAnO Conseil : Marketing / Retail / Supply Chain");

function prepperson($groupid, $project_name, $bdd, $ref)
{
	$req_pre = $bdd->prepare('SELECT id, email FROM project_'.$project_name.'_project WHERE groupid = '.$groupid.";");
	$req_pre->execute();
	$tabperson = $req_pre->fetchall();
	foreach ($tabperson as $keyp => $valuep)
	{
		if ($ref)
			$req_pre = $bdd->prepare('UPDATE project_'.$project_name.'_project SET refbool = 1 WHERE id = '.$valuep['id'].';');
		else
			$req_pre = $bdd->prepare('UPDATE project_'.$project_name.'_project SET questionbool = 1 WHERE id = '.$valuep['id'].';');
		$req_pre->execute();
		maildebase($valuep['email'], "etude muranoconseil", "Bonjour dans le cadre de notre études veuillez repondre au formulaire à l'adresse suivante : http://etudemurano.alwaysdata.net/directlogin.php?p=".$valuep['id']."&s=".$project_name."\r\n\r\nMURAnO Conseil : Marketing / Retail / Supply Chain");
	}
}

$req_pre = $bdd->prepare('DELETE FROM all_etude WHERE iteration < 1;');
$req_pre->execute();
$req_pre = $bdd->prepare('SELECT id, begin, iteration, groupid, project_name, iteration_detail, ref FROM all_etude WHERE 1;');
$req_pre->execute();
$tabsondage = $req_pre->fetchall();
foreach ($tabsondage as $key => $value)
{
	if ($value['ref'])
	{
		$req_pre = $bdd->prepare('UPDATE all_etude SET ref = 0 WHERE id = '.$value['id'].';');
		$req_pre->execute();
		prepperson($value['groupid'], $value['project_name'], $bdd, 1);
		continue ;
	}
	prepperson($value['groupid'], $value['project_name'], $bdd, 0);
}
$req_pre = $bdd->prepare('UPDATE all_etude SET iteration = iteration - 1 WHERE 1;');
$req_pre->execute();
?>
