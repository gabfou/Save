<?php
include("function.php");
include("testconect.php");
try
{
    $bdd = new PDO('mysql:host=mysql-johann.alwaysdata.net;dbname=johann_project;charset=utf8', 'johann', 't4x5akda');
    //$bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_WARNING);
}
catch(Exception $e)
{
    die('Erreur : '.$e->getMessage());
}
try{
    $req_pre = $bdd->prepare('SELECT refbool FROM project_'.htmlspecialchars($_SESSION['project']).'_project WHERE id = '.htmlspecialchars($_SESSION['id_client']).";"); // changer user         
    $req_pre->execute();
    }
catch (PDOException $e) {
    echo 'Error : '.$e->getMessage();
    die();
}
($tab = $req_pre->fetch());
if ($tab['refbool'] == 0)
    header("Location: error_no_question.php");
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

<p> Merci de votre de participation. </p>
<p> Cordialement toute l'equipe de murano conseil </p>

<?php


function getrepname($arg_1)
{
    $i = -1;
    $ret = "";

    while ($arg_1[++$i] && $arg_1[$i] != '#')
        $ret .= $arg_1[$i];
    return ($ret);
}

 {$bdd->exec('CREATE TABLE IF NOT EXISTS project_'.htmlspecialchars($_SESSION['project']).'_reponse (id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT, idperson INTEGER, name VARCHAR(100), time INTEGER,  note INTEGER, date_info datetime, iteration INTEGER);');}
//echo 'Le jeu a bien été ajouté !';
$tab = array();
foreach ($_POST as $key => $value)
{
    $tab[] = getrepname($key);
}

$tab = array_unique($tab);

foreach ($tab as $name)
{
    //echo ($name);
    if (isset($_POST[$name.'#note']))
	    $qry = 'INSERT INTO project_'.htmlspecialchars($_SESSION['project']).'_reponse (idperson , name, time, note, date_info, iteration) VALUE ('.htmlspecialchars($_SESSION['id_client']).' , "'.$name.'" , '.htmlspecialchars($_POST[$name.'#time']).', '.htmlspecialchars($_POST[$name.'#note']).' , NOW() , 0 );';
	else
		$qry = 'INSERT INTO project_'.htmlspecialchars($_SESSION['project']).'_reponse (idperson , name, time, note, date_info, iteration) VALUE ('.htmlspecialchars($_SESSION['id_client']).' , "'.$name.'" , '.htmlspecialchars($_POST[$name.'#time']).', '.'-1'.' , NOW() , 0 );';
    $bdd->exec($qry);
    //echo 'INSERT INTO project_'.$_SESSION['project'].'_reponse ('.$_SESSION['id_client'].', '.$_POST[$name."_time"].', '.$_POST[$name."_note"].', NOW());';
}
$qry = 'UPDATE project_'.htmlspecialchars($_SESSION['project']).'_project SET refbool = "0" WHERE id = '.htmlspecialchars($_SESSION['id_client']).";";
    $bdd->exec($qry);
?>