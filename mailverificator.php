<?php
	include("www/function.php");
	require 'phpMailer/PHPMailerAutoload.php';

function mailmieux($to, $subject, $body)
{

	try
	{
		$mail = new PHPMailer;
		$mail->SMTPDebug = 3;
		//$mail->isSMTP();
		$mail->Host = 'SSL0.OVH.NET';
		$mail->SMTPSecure = 'ssl';
		$mail->SMTPAuth = true;
		$mail->Username = 'etudes@muranoconseil.com';
		$mail->Password = 'etudes564';
		$mail->Port = 465;
		$mail->setFrom('etudes@muranoconseil.com', 'leadchangesurvey');
		$mail->addAddress($to/*, 'Joe User'*/);
		$mail->isHTML(true);
		$mail->CharSet = 'UTF-8';
		$mail->Subject = $subject;
		$mail->Body	= $body;
		$mail->AltBody = "hello, if you want to see corectly this message please use html compatible mailbox";

		if(!$mail->send())
		{
			echo 'Message could not be sent.';
			echo 'Mailer Error: '.$mail->ErrorInfo;
		}
		else
			echo 'Message has been sent';
	}
	catch (phpmailerException $e)
	{
		echo 'catch Mailer Error: '.$e->errorMessage(); //Pretty error messages from PHPMailer
	}
	catch (Exception $e)
	{
		echo 'Error: '.$e->getMessage(); //Boring error messages from anything else!
	}
}

function maildebase($to, $subject, $body)
{
	$headers   = array();
	$headers[] = "MIME-Version: 1.0";
	$headers[] = "Content-type: text/html; charset=utf-8";
	$headers[] = "From: leadchangesurvey <etudemurano@alwaysdata.net>";
	$headers[] = "Subject: {".$subject."}";
	$headers[] = "X-Mailer: PHP/".phpversion();


	if (!mail($to, $subject, $body, implode("\r\n", $headers)))
		echo "mail to ".$to;
}

		// $body = "<p>Bonjour,</p><Br/>";
		// $body .= "<p>Nous effectuons actuellement une mission pour le compte de votre société.</p>";
		// $body .= "<p>Dans ce cadre, le cabinet Murano vous donne la parole !</p>";
		// $body .= "<p>Merci de prendre quelques minutes de votre temps pour répondre à notre questionnaire :</p>";
		// $body .= '<a href="http://etudemurano.alwaysdata.net/directlogin.php';
		// $body .= '__%l__';
		// $body .= '"><u>ACCEDER AU QUESTIONNAIRE</u></a></p>';
		// $body .= "<p>Si vous avez des questions ou des difficultés avec le lien, n’hésitez pas à nous contacter.</p><Br/>";
		// $body .= "<p>Nous vous remercions de votre participation !</p>";
		// $body .= "<p>L’équipe MURAnO</p>";
		// $body .= "<Br/><p><b>MURAnO Conseil</b><Br/>";
		// $body .= "www.muranoconseil.com<Br/>";
		// $body .= "21, rue Vauthier<Br/>";
		// $body .= "92100 Boulogne-Billancourt<Br/>";
		// $body .= "<img src=\"http://etudemurano.alwaysdata.net/logomieux.jpg\" alt=\"logo murano\" style=\"width:64px; height:auto\" class = logo>";





function prepperson($groupid, $project_name, $bdd, $ref, $body)
{
	if (!isset($body) && $ref == 1)
	{
		$body = "<html style=\"font-family: \"century gothic\", Arial;\"><p>Dear __%p__,</p>";
		$body .= "<p>We hope that you had the time to complete the -Estimation- part of the Survey. If not the link below is still valid.</p>";
		$body .= "<p>We are now moving to the daily timesheet phase (a daily record of the time you spend on each task). Some tasks (ie: project development) are slightly more detailed than others, don’t be surprised and be as much accurate as you can.</p>";
		$body .= "<p>Ideally, fill the form at the end of the day. Don’t wait too long to complete it, after 3 days it won’t be that fresh on your mind…</p>";
		$body .= '<a href="http://etudemurano.alwaysdata.net/directlogin.php';
		$body .= '__%l__';
		$body .= '"><u>PPD_DMI LEAD CHANGE_Online Survey</u></a></p>';
		$body .= "<p>If you encounter any difficulty or if you have any question, please contact me:<ul><li>anais.deframond@muranoconseil.com</li><li>+33 770734938</p></li>";
		$body .= "<p>Thank you,<Br />Best Regards,</p>";
		$body .= "<p>Anaïs for the MURANO Team</p>";
		// $body .= "<img src=\"http://etudemurano.alwaysdata.net/logomieux.jpg\" alt=\"logo murano\" style=\"width:64px; height:auto\" class = logo>";
		$body .= "www.muranoconseil.com<Br/>";
		$body .= "21, rue Vauthier<Br/>";
		$body .= "92100 Boulogne-Billancourt<Br/></html>";
	}
	else if (!isset($body))
	{
		$body = "<html><p>Dear __%p__,</p>";
		$body .= "<p>This is your daily DMI LEAD CHANGE Timesheet reminder!</p>";
		$body .= "<p>Thank you for taking a few minutes at the end of your day to complete the form:</p>";
		$body .= '<a href="http://etudemurano.alwaysdata.net/directlogin.php';
		$body .= '__%l__';
		$body .= '"><u>PPD_DMI LEAD CHANGE_Online Survey</u></a></p>';
		$body .= "<p>If you encounter any difficulty or if you have any question, please contact me:<ul><li>anais.deframond@muranoconseil.com</li><li>+33 770734938</li></ul></p>";
		$body .= "<p>Thank you,<Br />Best Regards,</p>";
		$body .= "<p>Anaïs for the MURANO Team</p>";
		$body .= "<Br/><p><b>MURANO Conseil</b><Br/>";
		$body .= "www.muranoconseil.com<Br/>";
		$body .= "21, rue Vauthier<Br/>";
		$body .= "92100 Boulogne-Billancourt<Br/></html>";
        // $body .= "<img src=\"http://etudemurano.alwaysdata.net/logomail.jpg\" alt=\"logo murano\" style=\"width:120px;height:auto;\"class = logo></p></html>\r\n";
	}		
	$req_pre = $bdd->prepare('SELECT id, email, questionbool, refbool, firstname, lastname FROM project_'.$project_name.'_project WHERE '.strallgroupfilsforsql($groupid, $bdd, $project_name).";");
	$req_pre->execute();
	$tabperson = $req_pre->fetchall();
	foreach ($tabperson as $keyp => $valuep)
	{
		echo $valuep['email']."\n";
		if ($ref)
			$req_pre = $bdd->prepare('UPDATE project_'.$project_name.'_project SET refbool = refbool + 1 WHERE id = '.$valuep['id'].';');
		else
			$req_pre = $bdd->prepare('UPDATE project_'.$project_name.'_project SET questionbool = questionbool + 1 WHERE id = '.$valuep['id'].';');
		$req_pre->execute();
		mailmieux($valuep['email'], "PPD_DMI LEAD CHANGE_Time Sheet Survey_part2_day".($valuep['questionbool'] + 1), str_replace("__%p__", $valuep['firstname'], (str_replace("__%l__", "?p=".$valuep['id']."&s=".$project_name, $body))));
	}
}

$bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_WARNING);
echo time()."\n";
$req_pre = $bdd->prepare('DELETE FROM all_etude WHERE begin < DATE_SUB(NOW(), INTERVAL 30 day);');
$req_pre->execute();
$req_pre = $bdd->prepare('SELECT id, begin, iteration, groupid, project_name, iteration_detail, ref, mail FROM all_etude WHERE begin < DATE_ADD(NOW(), INTERVAL 10 MINUTE) AND iteration > 0;');
$req_pre->execute();
$tabsondage = $req_pre->fetchall();
$req_pre = $bdd->prepare('UPDATE all_etude SET iteration = iteration - 1 WHERE begin < DATE_ADD(NOW(), INTERVAL 10 MINUTE) AND iteration > 0;');
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
