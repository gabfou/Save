<?php
include "function.php";
session_set_cookie_params(3600);
session_start();
if (isset($_SESSION['id_client']))
{
	header("Location: index.php");
	echo "<html></html>";
	flush();
	ob_flush();
	die();
}
else
{
	$tag = "start";
	if (isset($_POST['submit']))
	{
		$login = htmlspecialchars($_POST['login']);
		$mdp = htmlspecialchars($_POST['password']);
		$prefixe = "poke";
		$suffixe = "mon";
		$mdp = $prefixe.$mdp.$suffixe;
		$hash = hash("Sha384", $mdp);
		//include ("sql_connect.php");
		try
		{
			$req_pre = $bdd->prepare('SELECT idperson, email, name_table FROM project_all_user WHERE password ="'.htmlspecialchars($hash).'" AND email="'.htmlspecialchars($login).'";'); // changer user
			if ($req_pre === false)
				echo "mysql probleme";// a virer
			//$req_pre->bindValue(1, htmlspecialchars($login), PDO::PARAM_STR);
			//$req_pre->bindValue(2, htmlspecialchars($hash), PDO::PARAM_STR);
			$req_pre->execute();
			$tab = $req_pre->fetchall();
		}
		catch (PDOException $e)
		{
			echo 'Error : '.$e->getMessage();
			die();
		}
		foreach ($tab as $key => $value)
		{
			$_SESSION['id_client'] = $value['idperson'];
			$_SESSION['email'] = $value['email'];
			$_SESSION['project'] = $value['name_table'];
		}
		if (!$_SESSION['id_client'])
			$tag = "refused";
		else
		{
			header("Location: index.php");
			echo "<html></html>";
			flush();
			ob_flush();
			die();
		}
	}
	?>
	<!doctype html>
	<html>
	<head>
		<title>Etude murano - Login</title>
		<meta charset="utf-8">
		<link rel="stylesheet" href="style.css">
	</head>
		<body>
			<div class="topbar">
				<img src="logo.jpeg" alt="logo murano" class = logo>
				<!-- <h1>MURANO</h1> -->
			</div>
			<div class = "site_container">
				<?php //include 'header.php';
					if ($tag === "connected")
						echo '<div class = "message connected"><p>Vous êtes connectés</p></div>';
					else if ($tag === "refused")
						echo '<div class = "message notconnected"><p>Mauvais identifiant ou mot de passe</p></div>';
					else if ($tag === "error")
						echo '<div class = "message error"><p>Erreur de connexion a la base de données</p></div>';
				?>
				<h2 class = "text_form">Connexion</h2>
				<?php
					echo '<form class = "formulaire" action="login.php" method="post">'
				?>
					<input class = "field2" name = "login" type = "text" placeholder = "e-mail">
					<input class = "field2" name = "password" type = "password" placeholder = "mot de passe">
					<input class = "form_btn" name = "submit" type = "submit" value = "Je me connecte">
				</form>
			</div>
		</body>
	</html>
<?php
//echo "login = ".htmlspecialchars($_POST['login'])." pass = ".htmlspecialchars($_POST['password']). " hash = ".$hash;
}
?>