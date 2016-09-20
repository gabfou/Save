<?php
	include("testconect.php");
	include("function.php");

	function recupfirstdiv($str)
	{
		return (strstr($str, "</div>", true)."</div>");
	}

	function supfirstdiv($str)
	{
		return (substr(strstr($str, "</div>"), 6));
	}

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
		<!-- <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.97.7/css/materialize.min.css"> -->
</head>
<body>
	<div class="topbar">
		<img src="logo.jpeg" alt="logo murano" class = logo>
		<!-- <h1>MURANO</h1> -->
	</div>
<?php
	$error = 1;
	$echopargroupe = array();
	if (isset($_SESSION['project']) && isset($_SESSION['id_client']))
	{
		$error = 0;
		$numberoffield = 0;
		$arrayjson = array();
		$arrayjson2 = array();
		while ($groupid > -1)
		{
			$req_pre = $bdd->prepare('SELECT id, question, note, type, sujet, qgroupid, typef, ref_only, splitchar FROM project_'.htmlspecialchars($_SESSION['project']).'_question WHERE groupid = '.htmlspecialchars($groupid).";"); // changer user
			$req_pre->execute();
			($tabquestion = $req_pre->fetchall());
			foreach ($tabquestion as $key => $value)
			{
				if ($value['ref_only'] != 1 || $_SESSION['iteration'] == 0)
				{
					$req_pre2 = $bdd->prepare('SELECT gquestion FROM project_'.htmlspecialchars($_SESSION['project']).'_groupe WHERE id= '.$value['qgroupid'].";");
					$req_pre2->execute();
					$tabg = $req_pre2->fetch();
					$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<div>';
					if ($tabg['gquestion'] == 0)
					{
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<fieldset class="field"><legend>'.$value['id'].'</legend>';
					}
					if ($value['typef'] == 0)
					{
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<label class="label" id="lab'.$value['id'].'" for "'.$value['id'].'#time"> '.$value['sujet'].' (en '.$value['type'].'): </label><input class = "reponse"  id="rep'.$value['id'].'" type="number" name="'.$value['id'].'#time" value="0" />';
					}
					else if ($value['typef'] == 1)
					{
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<label class="label" id="lab'.$value['id'].'" for="rep'.$value['id'].'"> '.$value['sujet'].': </label><select class = "reponse" id="rep'.$value['id'].'" type="checkbox" name="'.$value['id'].'#time" ><option value = "0" name="'.$value['id'].'#time">non</option><option value = "1" name="'.$value['id'].'#time">oui</option></select>';
					}
					else if ($value['typef'] == 2)
					{
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<label class="label" id="lab'.$value['id'].'" for "'.$value['id'].'#str"> '.$value['sujet'].': </label><select class = "reponse" id="rep'.$value['id'].'" name="'.$value['id'].'#str" >';
						$select = explode(" ", $value['splitchar']);
						foreach ($select as $selectkey => $selectvalue)
						{
							$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<option value = '.$selectvalue.' name="'.$value['id'].'#str">'.$selectvalue.'</option>';
						}
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'</select>';
					}
					else if ($value['typef'] == 3)
					{
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<label class="label" id="lab'.$value['id'].'" for "'.$value['id'].'#str"> '.$value['sujet'].': </label><select class = "reponse" id="rep'.$value['id'].'" name="'.$value['id'].'#str" >';
						$select = explode(" ", $value['splitchar']);
						$i = 0;
						while ($select[$i])
						{
							$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<option value = '.$select[$i + 1].' name="'.$value['id'].'#str">'.$select[$i].'</option>';
							$i += 2;
						}
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'</select>';
					}
					if ($_SESSION['iteration'] == 0 && $value['note'])
					 	$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<label for "'.$value['id'].'#note" >interet : </label><select name="'.$value['id'].'#note" /><option value = "1" name="'.$value['id'].'#note">faible</option><option value = "3" name="'.$value['id'].'#note">moyen</option><option value = "5" name="'.$value['id'].'#note">fort</option><br><br><br></select>';
					// else
					// 	continue ;
					$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<label id="resum'.$value['id'].'" class = "reponse">NA</label><br>';
					if ($tabg['gquestion'] == 0)
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'</fieldset>';
					$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'</div>';
					$arrayjson[] = $value['qgroupid'];
					$arrayjson2[] = $value['id'];
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
		$i = 0;
		foreach ($arrayjson as $key => $value)
		{
			$req_pre = $bdd->prepare('SELECT groupname, description, groupparent, gquestion FROM project_'.htmlspecialchars($_SESSION['project']).'_groupe WHERE id= '.htmlspecialchars($value).";"); 
			$req_pre->execute();
			$str3 = $req_pre->fetch();
			if ($str3['gquestion'] != 0)
			{
				$vqgroupid = $str3['groupparent'];
				$arrayjson[] = $str3['groupparent'];
				$arraygrouparrent[] = $str3['groupparent'];
			}
			else
				$vqgroupid = $value;
			if ($value == 0)
				$str3['groupname'] = "General";
			// echo '<li class="etape" id = "pbar'.$value.'"><span>'.$str3['groupname'].'</span></li>';
			if ($str3['gquestion'])
			{
				//echo "sup ". supfirstdiv($echopargroupe[$value])." add ".recupfirstdiv($echopargroupe[$value]);
				if ($str3['gquestion'] == 2)
				{
					$arrayjson3[] = $i; 
					$echofinal = $echofinal.'<div id= "question'.$vqgroupid.'" class="md_debut'.$i.'">'.recupfirstdiv($echopargroupe[$value]).'</div><div id = "question'.$vqgroupid.'" class="md_fin'.$i.'"><fieldset><legend>'.$str3['description'].'</legend><div id = "question'.$vqgroupid.'">'.supfirstdiv($echopargroupe[$value])."</fieldset></div>";
				}
				else
					$echofinal = $echofinal.'<div id = "question'.$vqgroupid.'"><fieldset><legend>'.$str3['description'].'</legend><div id = "question'.$vqgroupid.'">'.$echopargroupe[$value]."</fieldset></div>";
			}
			else
				$echofinal = $echofinal.'<p id = gdesc'.$vqgroupid.'>'.$str3['description'].'</p>'.'<div id = "question'.$vqgroupid.'">'.$echopargroupe[$value]."</div>";
			if ($str3['gquestion'] != 0)
				unset($arrayjson[$key]);
			$i++;
		}
		$arraygrouparrent = array_unique($arraygrouparrent);
		$arraygrouparrent = array_values($arraygrouparrent);
		foreach ($arraygrouparrent as $key => $value)
		{
			$req_pre = $bdd->prepare('SELECT groupname, description, groupparent, gquestion FROM project_'.htmlspecialchars($_SESSION['project']).'_groupe WHERE id= '.htmlspecialchars($value).";");
			$req_pre->execute();
			$str3 = $req_pre->fetch();
			$echofinal = '<p id = gdesc'.$value.'><h3 id = gdesc'.$value.'>'.$str3['description'].'</h3></p>'.$echofinal;
		}
		$arrayjson = array_unique($arrayjson);
		$arrayjson = array_values($arrayjson);
		$arrayjson3 = array_unique($arrayjson3);
		$arrayjson3 = array_values($arrayjson3);
		echo '</ul>';
		echo '<div id="progressbar"><div id="indicator"></div><div id="progressnum">0%</div></div>';
		echo '<div class = "formulaire2">';
		echo '<h2 id = bilan>BILAN</h1>';
		//echo $introdesc;
		echo '<form action="updatetimesheet.php" method="post" id="formulaireid">';
		echo $echofinal;
		echo '<input type="button" class = "from_inputleft btn-large waves-light" id = "go_back" value="Retour">';
		echo '<input type="button" class = "from_inputright btn-large waves-light" id = "target" value="Suivant">';
		echo '<input type="submit" class = "from_inputright btn-large waves-light" id = "next" value="Envoyer"></form>';
?>
	<script type="text/javascript" src="http://code.jquery.com/jquery-1.8.0.min.js"></script>
	<!-- <script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.97.7/js/materialize.min.js"></script> -->
	<script type="text/javascript">
	$(document).ready(function () {
			(function() {
					<?php
						$js_array = json_encode($arrayjson);
						echo "var array = ".$js_array.";\n";
						$js_array2 = json_encode($arrayjson2);
						echo "var question_array = ".$js_array2.";\n";
						$js_array3 = json_encode($arrayjson3);
						echo "var md_array = ".$js_array3.";\n";
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
					$niark22 = 0;
					function mdforeach(element, index, array)
					{
						$( ".md_debut" + element).on('change', function()
						{
							var str = ".md_debut";
							str.concat(element);
							var str2 = ".md_fin";
							str2.concat(element);
							if ($niark22 % 2 == 0)
								$( ".md_fin" + element).show();
							else
								$( ".md_fin" + element).hide();
							$niark22++;
						});
					}
					var i = -1;
					$("[id^=question]").hide();
					$("[id^=gdesc]").hide();
					$("[id^=resum]").hide();
					//$("[id^=pbar]").css('background-color', '#6BF3FF');
					$("[id^=pbar]").hide();
					$("[id=next]").hide();
					$("[id=bilan]").hide();
					var j = -1;
					md_array.forEach(mdforeach);
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
	<!-- <script type="text/javascript">
	  $(document).ready(function() {
    $('select').material_select();
  });
	  </script> -->

	<?php
	}
	else
	{
			echo("<p>cette page n'est pas disponible</p>");
			die();
	}
	//print_r($arrayjson);
	?>
</div>
	</body>