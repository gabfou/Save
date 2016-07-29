<?php
if ($bdd = mysqli_connect('mysql-johann.alwaysdata.net', 'johann', 't4x5akda', 'johann_project'))
{
}
else
{
	$tag = "error";
}
include "function.php";
session_set_cookie_params(3600);
session_start();
if (isset($_SESSION['id_client']))
{
	header("Location: index.php");
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
		$req_pre = mysqli_prepare($bdd, 'SELECT id, email, FROM '.Securite::bdd($_GET[project__project]).' WHERE (email = ?) AND password = ?'); // changer user
		if ($req_pre === false)
			echo "mysql probleme"; // a virer
		mysqli_stmt_bind_param($req_pre, "sss", htmlspecialchars($login), $login, $hash);
		mysqli_stmt_execute($req_pre);
		mysqli_stmt_bind_result($req_pre, $tab['id'], $tab['email']);
		while (mysqli_stmt_fetch($req_pre))
		{
			$_SESSION['id_client'] = $tab['id'];
			$_SESSION['login'] = $tab['email'];
		}
		if (!$_SESSION['id_client'])
			$tag = "refused";
		else
			header("Location: index.php");

		mysqli_free_result($req);
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
				<form class = "formulaire" action="login.php" method="post">
					<input class = "field" name = "login" type = "text" placeholder = "e-mail">
					<input class = "field" name = "password" type = "password" placeholder = "mot de passe">
					<input class = "form_btn" name = "submit" type = "submit" value = "Je me connecte">
				</form>
				<input 
			</div>
		</body>
	</html>
<?php
}
?>