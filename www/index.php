<?php
include("function.php");
include("testconect.php");
$bdd = new PDO('mysql:host=mysql-johann.alwaysdata.net;dbname=johann_project;charset=utf8', 'johann', 't4x5akda');
//$bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_WARNING);
$req_pre = $bdd->prepare('SELECT questionbool, groupid FROM project_'.htmlspecialchars($_SESSION['project']).'_project WHERE id = '.htmlspecialchars($_SESSION['id_client']).";"); // changer user
$req_pre->execute();
($tab = $req_pre->fetch());
if ($tab['questionbool'] == 0)
	header("Location: error_no_question.php");
$groupid = $tab['groupid'];
?>

<head>
<link rel="stylesheet" href="style.css" />
<title>etude muranoconseil</title>
</head>
<body>
<div class="topbar">
	<img src="logo.jpeg" alt="logo murano" class = logo>
	<!-- <h1>MURANO</h1> -->
</div>
<p>Bonjour et merci de participer a cette étude</p>
<p>Veuillez remplir le formulaire suivant</p>

<?php
if (isset($_SESSION['project']) && isset($_SESSION['id_client']))
{

echo '<form action="updatetimesheet.php" method="post">';


// foreach ($_GET as $key => $value)
// {
	
// 	if ($key !== "project__project" && $key !== "person__person")
// 	{
while ($groupid > -1)
{
	$req_pre = $bdd->prepare('SELECT question, note, type, sujet FROM project_'.htmlspecialchars($_SESSION['project']).'_question WHERE groupid = '.htmlspecialchars($groupid).";"); // changer user		
	$req_pre->execute();
	($tabquestion = $req_pre->fetchall());
	foreach ($tabquestion as $key => $value)
	{
		echo '<fieldset><legend>'.$value['question'].'</legend>';
		echo '<label for "'.$value['question'].'#time"> '.$value['sujet'].' (en '.$value['type'].'): </label><input type="text" name="'.$value['question'].'#time" /><br>';
		if ($value['note'])
			echo '<label for "'.$value['question'].'#note" >interet (sur un bareme de 1 a 5) : </label><select name="'.$value['question'].'#note" /><option value = "1" name="'.$value['question'].'#note">1</option><option value = "2" name="'.$value['question'].'#note">2</option><option value = "3" name="'.$value['question'].'#note">3</option><option value = "4" name="'.$value['question'].'#note">4</option><option value = "5" name="'.$value['question'].'#note">5</option><br><br><br></select>';
		echo '</fieldset>';
	}
		$req_pre = $bdd->prepare('SELECT groupparent FROM project_'.htmlspecialchars($_SESSION['project']).'_groupe WHERE id = '.$groupid.";"); // changer user	   
		$req_pre->execute();
	($tab = $req_pre->fetch());
	if ($tab === false)
		$groupid = -1;
	else
		$groupid = $tab['groupparent'];
	unset ($tabquestion);
}
echo'<p><input type="submit" value="OK"></p></form>';

}

else
	echo("<p>cette page n'est pas disponible</p>");
?>

</body>