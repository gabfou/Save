<?php
	include("www/function.php");


function mailmieux($to, $subject, $body)
{
	require 'PHPMailerAutoload.php';

	$mail = new PHPMailer;

	//$mail->SMTPDebug = 3;

	$mail->isSMTP();
	$mail->Host = '"smtp-etudemurano.alwaysdata.net"';
	$mail->SMTPAuth = true;
	$mail->Username = 'etudemurano@alwaysdata.net';
	$mail->Password = 't4x5akda';
	$mail->SMTPSecure = 'tls';
	$mail->Port = 587;

	$mail->setFrom('etudemurano@alwaysdata.net', 'etudemurano');
	$mail->addAddress($to/*, 'Joe User'*/);

	$mail->isHTML(true);

	$mail->Subject = $subject;
	$mail->Body	= $body;
//	$mail->AltBody = 'body in plain text';

	if(!$mail->send())
	{
		echo 'Message could not be sent.';
		echo 'Mailer Error: ' . $mail->ErrorInfo;
	}
	else
		echo 'Message has been sent';
}

function maildebase($to, $subject, $body)
{
	$headers   = array();
	$headers[] = "MIME-Version: 1.0";
	$headers[] = "Content-type: text/html; charset=utf-8";
	$headers[] = "From: Etudesmuranoconseil <etudemurano@alwaysdata.net>";
	$headers[] = "Subject: {".$subject."}";
	$headers[] = "X-Mailer: PHP/".phpversion();

	if (!mail($to, $subject, $body, implode("\r\n", $headers)))
		echo "mail to ".$to;
}

function prepperson($groupid, $project_name, $bdd, $ref, $body)
{
	if (!isset($body))
	{
		$body = "<p>Bonjour,</p><Br/>";
		$body .= "<p>Nous effectuons actuellement une mission pour le compte de votre société.</p>";
		$body .= "<p>Dans ce cadre, le cabinet Murano vous donne la parole !</p>";
		$body .= "<p>Merci de prendre quelques minutes de votre temps pour répondre à notre questionnaire :</p>";
		$body .= '<a href="etudemurano.alwaysdata.net/directlogin.php';
		$body .= '__%l__';
		$body .= '"><u>ACCEDER AU QUESTIONNAIRE</u></a></p>';
		$body .= "<p>Si vous avez des questions ou des difficultés avec le lien, n’hésitez pas à nous contacter.</p><Br/>";
		$body .= "<p>Nous vous remercions de votre participation !</p>";
		$body .= "<p>L’équipe MURAnO</p>";
		$body .= "<Br/><p><b>MURAnO Conseil</b><Br/>";
		$body .= "www.muranoconseil.com<Br/>";
		$body .= "21, rue Vauthier<Br/>";
		$body .= "92100 Boulogne-Billancourt<Br/>";
		$body .= "<img src=\"http://etudemurano.alwaysdata.net/logomieux.jpg\" alt=\"logo murano\" class = logo></p>";
	}
	$req_pre = $bdd->prepare('SELECT id, email FROM project_'.$project_name.'_project WHERE '.strallgroupfilsforsql($groupid, $bdd, $project_name).";");
	$req_pre->execute();
	$tabperson = $req_pre->fetchall();
	print_r($tabperson);
	foreach ($tabperson as $keyp => $valuep)
	{
		echo $valuep['email']."\n";
		if ($ref)
			$req_pre = $bdd->prepare('UPDATE project_'.$project_name.'_project SET refbool = refbool + 1 WHERE id = '.$valuep['id'].';');
		else
			$req_pre = $bdd->prepare('UPDATE project_'.$project_name.'_project SET questionbool = questionbool + 1 WHERE id = '.$valuep['id'].';');
		$req_pre->execute();
		maildebase($valuep['email'], "etude muranoconseil", str_replace("__%l__", "?p=".$valuep['id']."&s=".$project_name, $body));
	}
}

$bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_WARNING);
echo time()."\n";
$req_pre = $bdd->prepare('DELETE FROM all_etude WHERE begin < DATE_SUB(NOW(), INTERVAL 30 day);');
$req_pre->execute();
$req_pre = $bdd->prepare('SELECT id, begin, iteration, groupid, project_name, iteration_detail, ref, mail FROM all_etude WHERE begin < DATE_ADD(NOW(), INTERVAL 30 MINUTE) AND iteration > 0;');
$req_pre->execute();
$tabsondage = $req_pre->fetchall();
$req_pre = $bdd->prepare('UPDATE all_etude SET iteration = iteration - 1 WHERE begin < DATE_ADD(NOW(), INTERVAL 30 MINUTE) AND iteration > 0;');
$req_pre->execute();
print_r($tabsondage);
foreach ($tabsondage as $key => $value)
{
	if ($value['ref'])
	{
		$req_pre = $bdd->prepare('UPDATE all_etude SET ref = 0 WHERE id = '.$value['id'].';');
		$req_pre->execute();
		prepperson($value['groupid'], $value['project_name'], $bdd, 1, $value['mail']);
		continue ;
	}
	prepperson($value['groupid'], $value['project_name'], $bdd, 0, $value['mail']);
}
echo "\n";
?>
