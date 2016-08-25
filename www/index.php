<?php
	include("testconect.php");
	include("function.php");
	$req_pre = $bdd->prepare('SELECT questionbool, groupid FROM project_'.htmlspecialchars($_SESSION['project']).'_project WHERE id = '.htmlspecialchars($_SESSION['id_client']).";"); // changer user
	$req_pre->execute();
	($tab = $req_pre->fetch());
	if ($tab['questionbool'] == 0)
	{
		header("Location: error_no_question.php");
		echo "<html></html>";
		flush();
		ob_flush();
		exit;
	}
	$groupid = $tab['groupid'];
?>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" /> 
	<head>
		<link rel="stylesheet" href="style.css" />
		<title>etude muranoconseil</title>
</head>
<body>
	<div class="topbar">
		<img src="logo.jpeg" alt="logo murano" class = logo>
		<!-- <h1>MURANO</h1> -->
	</div>
<?php
	$error = 1;
	if (isset($_SESSION['project']) && isset($_SESSION['id_client']))
	{
			$error = 0;
			$numberoffield = 0;


		$arrayjson = array();
		while ($groupid > -1)
		{
			$req_pre = $bdd->prepare('SELECT question, note, type, sujet, qgroupid, typef, ref_only  FROM project_'.htmlspecialchars($_SESSION['project']).'_question WHERE groupid = '.htmlspecialchars($groupid).";"); // changer user
			$req_pre->execute();
			($tabquestion = $req_pre->fetchall());
			foreach ($tabquestion as $key => $value)
			{
				if ($value['ref_only'] != 1)
				{
					$echofinal = $echofinal.'<div id = "question'.$value['qgroupid'].'">';
					$echofinal = $echofinal.'<fieldset class="field"><legend>'.$value['question'].'</legend>';
					if ($value['typef'] == 0)
						$echofinal = $echofinal.'<label for "'.$value['question'].'#time"> '.$value['sujet'].' (en '.$value['type'].'): </label><input class = "reponse" type="number" name="'.$value['question'].'#time" value="0" /><br>';
					else if ($value['typef'] == 1)
						$echofinal = $echofinal.'<label for "'.$value['question'].'#time"> '.$value['sujet'].': </label><label><input class = "reponse" type="checkbox" name="'.$value['question'].'#time" value="1" />oui</label><label><input class = "reponse" type="checkbox" name="'.$value['question'].'#time" value="0" />non</label><br>';
					if ($value['note'])
						$echofinal = $echofinal.'<label for "'.$value['question'].'#note" >interet : </label><select name="'.$value['question'].'#note" /><option value = "1" name="'.$value['question'].'#note">faible</option><option value = "3" name="'.$value['question'].'#note">moyen</option><option value = "5" name="'.$value['question'].'#note">fort</option><br><br><br></select>';
						$echofinal = $echofinal.'</fieldset>';
					$echofinal = $echofinal.'</div>';
					$arrayjson[] = $value['qgroupid'];
					$numberoffield++;
				}
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
		$arrayjson = array_unique($arrayjson);
		$arrayjson = array_values($arrayjson);
		$echofinal = $echofinal.'<div id = "intro"><p>Bonjour et merci de participer à cette étude</p><p>Veuillez cliquer sur le bouton suivant et repondre aux questions en fonction de votre journée.</p></div>';
		echo '<ul id="menupbar">';
		foreach ($arrayjson as $key => $value)
		{
			$req_pre = $bdd->prepare('SELECT groupname  FROM project_'.htmlspecialchars($_SESSION['project']).'_groupe WHERE id= '.htmlspecialchars($value).";"); // changer user   
			$req_pre->execute();
			$str3 = $req_pre->fetch();
			if ($value == 0)
				$str3['groupname'] = "General";
			echo '<li class="etape" id = "pbar'.$value.'"><span>'.$str3['groupname'].'</span></li>';
		}
		echo '</ul>';
		echo '<div id="progressbar"><div id="indicator"></div><div id="progressnum">0%</div></div>';
		echo '<div class = "formulaire2">';
		echo '<form action="updatetimesheet.php" method="post">';
		echo $echofinal;
		echo '<p><input type="button" class = "from_input" id = "target" value="Suivant"></p>';
		echo '<p><input type="submit" class = "from_input" id = "next" value="Envoyer"></p></form>';
?>
		<script type="text/javascript" src="http://code.jquery.com/jquery-1.8.0.min.js"></script>
	<script type="text/javascript">
	$(document).ready(function () {
			(function() {
					<?php
					$js_array = json_encode($arrayjson);
					echo "var array = ". $js_array . ";\n";
					?>
					var maxprogress = 100;   // total à atteindre
					var actualprogress = 0;  // valeur courante
					var itv = 0;  // id pour setinterval
					function prog()
					{
						if(actualprogress >= maxprogress) 
						{
							clearInterval(itv);   	
							return;
						}	
						var progressnum = document.getElementById("progressnum");
						var indicator = document.getElementById("indicator");
						actualprogress += 100 / array.length;	
						indicator.style.width=actualprogress + "%";
						progressnum.innerHTML = actualprogress + "%";
						progressnum.style.marginLeft=actualprogress + "%";
						if(actualprogress == maxprogress) clearInterval(itv);   
					}
					var i = 0;
					$("[id^=question]").hide();
					//$("[id^=pbar]").css('background-color', '#6BF3FF');
					$("[id^=pbar]").hide();
					$("[id=next]").hide();
					$( "#target" ).click(function()
					{
						$("[id^=question]").hide();
						$("[id=intro]").hide();
						$("[id^=pbar]").css('background-color', '#6BF3FF');
						var str = "[id=question";
						str = str.concat(array[i]);
						var str2 = "[id=pbar";
						str2 = str2.concat(array[i]);
						i++;
						str = str.concat("]");
						str2 = str2.concat("]");
						$(str).show();
						$(str2).css('background-color', '#449CA3');
						prog();
						if (!(array[i]))
						{
							$("[id=next]").show();
							$("[id=target]").hide();
						}
					});
				})();
			});
	</script>


	<?php
	}
	else
	{
			echo("<p>cette page n'est pas disponible</p>");
			die();
	}
	?>
</div>
	</body>