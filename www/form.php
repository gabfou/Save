<?php
	include("testconect.php");
	include("function.php");
	$req_pre = $bdd->prepare('SELECT questionbool, refbool, groupid FROM project_'.htmlspecialchars($_SESSION['project']).'_project WHERE id = '.htmlspecialchars($_SESSION['id_client']).";"); // changer user
	$req_pre->execute();
	($tab = $req_pre->fetch());
	if (($tab['questionbool'] == 0 && $_SESSION['iteration'] >= 1) || ($tab['refbool'] == 0 && $_SESSION['iteration'] == 0))
	{
		header("Location: index.php");
		echo "<html></html>";
		flush();
		ob_flush();
		exit;
	}
	$groupid = $tab['groupid'];
?>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
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
		$arrayjson2 = array();
		while ($groupid > -1)
		{
			$req_pre = $bdd->prepare('SELECT question, note, type, sujet, qgroupid, typef, ref_only, splitchar FROM project_'.htmlspecialchars($_SESSION['project']).'_question WHERE groupid = '.htmlspecialchars($groupid).";"); // changer user
			$req_pre->execute();
			($tabquestion = $req_pre->fetchall());
			foreach ($tabquestion as $key => $value)
			{
				if ($value['ref_only'] != 1 || $_SESSION['iteration'] == 0)
				{
					$echofinal = $echofinal.'<div id = "question'.$value['qgroupid'].'">';
					$echofinal = $echofinal.'<fieldset class="field"><legend>'.$value['question'].'</legend>';
					if ($value['typef'] == 0)
						$echofinal = $echofinal.'<label class="label" id="lab'.$value['question'].'" for "'.$value['question'].'#time"> '.$value['sujet'].' (en '.$value['type'].'): </label><input class = "reponse"  id="rep'.$value['question'].'" type="number" name="'.$value['question'].'#time" value="0" />';
					else if ($value['typef'] == 1)
						$echofinal = $echofinal.'<label class="label" id="lab'.$value['question'].'" for "'.$value['question'].'#time"> '.$value['sujet'].': </label><select class = "reponse" id="rep'.$value['question'].'" type="checkbox" name="'.$value['question'].'#time" ><option value = "1" name="'.$value['question'].'#time">oui</option><option value = "0" name="'.$value['question'].'#time">non</option></select>';
					else if ($value['typef'] == 2)
					{
						$echofinal = $echofinal.'<label class="label" id="lab'.$value['question'].'" for "'.$value['question'].'#str"> '.$value['sujet'].': </label><select class = "reponse" id="rep'.$value['question'].'" name="'.$value['question'].'#str" >';
						$select = explode(" ", $value['splitchar']);
						foreach ($select as $selectkey => $selectvalue)
						{
							$echofinal = $echofinal.'<option value = '.$selectvalue.' name="'.$value['question'].'#str">'.$selectvalue.'</option>';
						}
						$echofinal = $echofinal.'</select>';
					}
					if ($_SESSION['iteration'] == 0 && $value['note'])
					 	$echofinal = $echofinal.'<label for "'.$value['question'].'#note" >interet : </label><select name="'.$value['question'].'#note" /><option value = "1" name="'.$value['question'].'#note">faible</option><option value = "3" name="'.$value['question'].'#note">moyen</option><option value = "5" name="'.$value['question'].'#note">fort</option><br><br><br></select>';
					// else
					// 	continue ;
					$echofinal = $echofinal.'<label id="resum'.$value['question'].'" class = "reponse">NA</label><br>';
					$echofinal = $echofinal.'</fieldset>';
					$echofinal = $echofinal.'</div>';
					$arrayjson[] = $value['qgroupid'];
					$arrayjson2[] = $value['question'];
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
		$echofinal2 += "</div>";
		$arrayjson = array_unique($arrayjson);
		$arrayjson = array_values($arrayjson);
		$echofinal = $echofinal.'<div id = "intro"><p>Bonjour et merci de participer à cette étude</p><p>Veuillez cliquer sur le bouton suivant et repondre aux questions en fonction de votre journée.</p></div>';
		$introdesc = "";
		echo '<ul id="menupbar">';
		foreach ($arrayjson as $key => $value)
		{
			$req_pre = $bdd->prepare('SELECT groupname, description FROM project_'.htmlspecialchars($_SESSION['project']).'_groupe WHERE id= '.htmlspecialchars($value).";"); // changer user   
			$req_pre->execute();
			$str3 = $req_pre->fetch();
			if ($value == 0)
				$str3['groupname'] = "General";
			echo '<li class="etape" id = "pbar'.$value.'"><span>'.$str3['groupname'].'</span></li>';
			$introdesc = $introdesc.'<p id = gdesc'.$value.'>'.$str3['description'].'</p>';
		}
		echo '</ul>';
		echo '<div id="progressbar"><div id="indicator"></div><div id="progressnum">0%</div></div>';
		echo '<div class = "formulaire2">';
		echo '<h2 id = bilan>BILAN</h1>';
		echo $introdesc;
		echo '<form action="updatetimesheet.php" method="post" id="formulaireid">';
		echo $echofinal;
		echo '<input type="button" class = "from_inputleft" id = "go_back" value="Retour">';
		echo '<input type="button" class = "from_inputright" id = "target" value="Suivant">';
		echo '<input type="submit" class = "from_inputright" id = "next" value="Envoyer"></form>';
?>
		<script type="text/javascript" src="http://code.jquery.com/jquery-1.8.0.min.js"></script>
	<script type="text/javascript">
	$(document).ready(function () {
			(function() {
					<?php
					$js_array = json_encode($arrayjson);
					echo "var array = ". $js_array . ";\n";
					$js_array2 = json_encode($arrayjson2);
					echo "var question_array = ". $js_array2 . ";\n";
					?>
					var maxprogress = 100; // total à atteindre
					var actualprogress = 0; // valeur courante
					var itv = 0; // id pour setinterval
					function prog(nb)
					{
						// if(actualprogress >= maxprogress)
						// {
						// 	clearInterval(itv);
						// 	return ;
						// }
						var progressnum = document.getElementById("progressnum");
						var indicator = document.getElementById("indicator");
						actualprogress = ((maxprogress / array.length) * nb).toFixed(0);
						indicator.style.width=actualprogress + "%";
						progressnum.innerHTML = actualprogress + "%";
						progressnum.style.marginLeft=actualprogress + "%";
						//if(actualprogress == maxprogress)
						//	clearInterval(itv);
					}
					function bilanforeach(element, index, array)
					{
						// console.log("a[" + index + "] = " + element);
						var str3 = "[id=rep";
						str3.concat(element);
						str3.concat("]");
						var str4 = "[id=resum";
						str4.concat(element);
						str4.concat("]");
						var rep = document.getElementById("rep" + element);
						var resum = document.getElementById("resum" + element);
						if (resum && rep)
						{
							if (rep.tagName == "select" || rep.tagName == "SELECT")
							{
								var opt = rep.options;
								resum.innerHTML = opt[rep.selectedIndex].text;
							}
							else
								resum.innerHTML = rep.value;
						}
						// else
						// 	resum.innerHTML = "Vous n'avez pas repondu a cette question";
						$(str3).show();
						$(str4).show();
					}
					function bilan()
					{
						$("[id=next]").show();
						$("[id=target]").hide();
						$("[id^=resum]").show();
						$("[id^=gdesc]").hide();
						$("[id^=question]").show();
						$("[id^=rep]").hide();
						$("[id=bilan]").show();
						question_array.forEach(bilanforeach);
					}
					function etapemanageur(nb)
					{
						if (!(array[nb]))
						{
							bilan();
							prog(nb);
							//$("[id=go_back]").hide();
							return ;
						}
						$("[id^=rep]").show();
						$("[id=next]").hide();
						$("[id^=gdesc]").hide();
						$("[id=target]").show();
						$("[id^=question]").hide();
						$("[id^=resum]").hide();
						$("[id=intro]").hide();
						$("[id^=pbar]").css('background-color', '#6BF3FF');
						$("[id=bilan]").hide();
						var str = "[id=question";
						str = str.concat(array[nb]);
						var str2 = "[id=pbar";
						str2 = str2.concat(array[nb]);
						str = str.concat("]");
						str2 = str2.concat("]");
						var str4 = "[id=gdesc";
						str4 = str4.concat(array[nb]);
						str4 = str4.concat("]");
						$(str4).show();
						$(str).show();
						$(str2).css('background-color', '#449CA3');
						prog(nb);
					}
					var i = -1;
					$("[id^=question]").hide();
					$("[id^=gdesc]").hide();
					$("[id^=resum]").hide();
					//$("[id^=pbar]").css('background-color', '#6BF3FF');
					$("[id^=pbar]").hide();
					$("[id=next]").hide();
					$("[id=bilan]").hide();
					$( "#target" ).click(function()
					{
						etapemanageur(++i);
					});
					$( "#go_back" ).click(function()
					{
						if (i > 0)
							etapemanageur(--i);
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