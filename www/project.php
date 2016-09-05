<?php if (isset($_SESSION)) session_destroy();?>
<head>
<link rel="stylesheet" href="style.css" />
<title>etude muranoconseil</title>
</head>
<body>
<form class = "formulaire" action="login.php" method="get">
	<input class = "field" name = "project__project" type = "text" placeholder = "noms de l'etablissement">
</form>
</body>