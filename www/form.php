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

	if (isset($_GET['it']) && $_GET['it'] <= $_SESSION['max'])
		$_SESSION['iteration'] = $_GET['it'];
	if (!isset($_SESSION['iteration']) || !isset($_SESSION['max']) || $_SESSION['iteration'] > $_SESSION['max'])
	{
		header("Location: index.php");
		echo "<html></html>";
		flush();
		ob_flush();
		exit;
	}

	$req_pre = $bdd->prepare('SELECT questionbool, refbool, groupid FROM project_'.htmlspecialchars($_SESSION['project']).'_project WHERE id = '.htmlspecialchars($_SESSION['id_client']).";"); // changer user
	$req_pre->execute();
	($tab = $req_pre->fetch());
	// if (($tab['questionbool'] == 0 && $_SESSION['iteration'] >= 1) || ($tab['refbool'] == 0 && $_SESSION['iteration'] == 0))
	// {
	// 	header("Location: index.php");
	// 	echo "<html></html>";
	// 	flush();
	// 	ob_flush();
	// 	exit;
	// }
	$questionbool = $tab['questionbool'];
	$refbool = $tab['refbool'];	
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
		$arrayjson3 = array();
		$arrayjson4 = array();
		$arraygrouparrent = array();
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

					$req_pre2 = $bdd->prepare('SELECT time, str FROM project_'.htmlspecialchars($_SESSION['project']).'_reponse WHERE idperson = '.htmlspecialchars($_SESSION['id_client']).' AND iteration = '.htmlspecialchars($_SESSION['iteration']).' AND idquestion = '.htmlspecialchars($value['id']).';'); // changer user
					$req_pre2->execute();
					$rep = $req_pre2->fetch();
					$repnbr = (isset($rep['time'])) ? $rep['time'] : "";
					$repstr = (isset($rep['str'])) ? $rep['str'] : "";

					if ($tabg['gquestion'] == 0)
					{
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<fieldset class="field"><legend>'.$value['question'].'</legend>';
					}
					if ($value['typef'] == 0)
					{
						$minmax = array_filter(explode("\n", $value['splitchar']));
						if (!isset($minmax[0]))
							$minmax[0] = '0';
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<label class="label lab'.$value['id'].'" for="'.$value['id'].'__time"> '.$value['sujet'].(($value['type'] == "") ? "" : (' (en '.$value['type'].')')).': </label><input class = "reponse required rep '.(($value['type'] == "") ? '' : ('type_'.$value['type'])).'" required '.$value['id'].'" type="number" min="'.$minmax[0].'" '.(isset($minmax[1]) ? 'max="'.$minmax[1].'"' : '').' name="'.$value['id'].'__time" id="'.$value['id'].'__time" value="'.$repnbr.'" />';
						$arrayjson4[] = $value['sujet'];
					}
					else if ($value['typef'] == 1)
					{
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<label class="label lab'.$value['id'].'" for="rep'.$value['id'].'"> '.$value['sujet'].': </label><select class = "reponse required rep" required '.$value['id'].'" type="checkbox" name="'.$value['id'].'__time" ><option value = "'.$repnbr.'" name="'.$value['id'].'__time"></option><option value = "0" name="'.$value['id'].'__time">non</option><option value = "1" name="'.$value['id'].'__time">oui</option></select>';
					}
					else if ($value['typef'] == 2)
					{
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<label class="label lab'.$value['id'].'" for "'.$value['id'].'__str"> '.$value['sujet'].': </label><select class = "reponse required rep" required '.$value['id'].'" name="'.$value['id'].'__str" >';
						$select = array_filter(explode("\n", $value['splitchar']));
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<option value = "'.$repstr.'" name="'.$value['id'].'__str"></option>';
						foreach ($select as $selectkey => $selectvalue)
						{
							$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<option value = '.$selectvalue.' name="'.$value['id'].'__str">'.$selectvalue.'</option>';
						}
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'</select>';
					}
					else if ($value['typef'] == 3)
					{
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<label class="label lab'.$value['id'].'" for "'.$value['id'].'__time"> '.$value['sujet'].': </label><select class = "reponse required rep" required '.$value['id'].'" name="'.$value['id'].'__time" >';
						$select = array_filter(explode("\n", $value['splitchar']));
						$i = 0;

						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<option value = "'.$repnbr.'" name="'.$value['id'].'__time"></option>';
						while ($select[$i])
						{
							$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<option value = '.$select[$i + 1].' name="'.$value['id'].'__time">'.$select[$i].'</option>';
							$i += 2;
						}
						$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'</select>';
					}
					if ($_SESSION['iteration'] == 0 && $value['note'])
					 	$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<label for "'.$value['id'].'#note" >interet : </label><select name="'.$value['id'].'#note" /><option value = "1" name="'.$value['id'].'#note">faible</option><option value = "3" name="'.$value['id'].'#note">moyen</option><option value = "5" name="'.$value['id'].'#note">fort</option><br><br><br></select>';
					// else
					// 	continue ;
					//$echopargroupe[$value['qgroupid']] = $echopargroupe[$value['qgroupid']].'<label id="resum'.$value['id'].'" class = "reponse">NA</label><br>';
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

		if (isset($_SESSION['etude']))
		{
			$req_pre = $bdd->prepare('SELECT intro FROM all_etude WHERE project_name = '.htmlspecialchars($_SESSION['project']).";");
			$req_pre->execute();
			($tab = $req_pre->fetch());
			$echofinal = $echofinal.$tab['intro'];
		}
		else
			$echofinal = $echofinal.'<div id = "intro"><h1>JOUR __%j__</h1></div>';
		$echofinal = str_replace("__%j__", $_SESSION['iteration'], $echofinal);
		$echofinal = str_replace("__%nb__", $questionbool + $refbool, $echofinal);
		$introdesc = "";
		echo '<ul id="menupbar">';
		$i = 0;
		$nop = 1;
//		while ($nop > 0)
		{
			$nop = 0;
			foreach ($arrayjson as $key => $value)
			{
				$req_pre = $bdd->prepare('SELECT groupname, description, groupparent, gquestion FROM project_'.htmlspecialchars($_SESSION['project']).'_groupe WHERE id= '.htmlspecialchars($value).";"); 
				$req_pre->execute();
				$str3 = $req_pre->fetch();
				if ($str3['gquestion'] != 0)
				{
					$nop++;
					$vqgroupid = $str3['groupparent'];
					$arrayjson[] = $str3['groupparent'];
					$arraygrouparrent[] = $str3['groupparent'];
					//echo "sup ". supfirstdiv($echopargroupe[$value])." add ".recupfirstdiv($echopargroupe[$value]);
					if ($str3['gquestion'] == 2)
					{
						$arrayjson3[] = $i; 
						$echopargroupe[$str3['groupparent']] = $echopargroupe[$str3['groupparent']].'<div class= "question'.$vqgroupid.'" style="display: hidden"><fieldset><legend>'.$str3['description'].'</legend><div class="md_debut'.$i.'">'.recupfirstdiv($echopargroupe[$value]).'</div><div id = "question'.$vqgroupid.'" class="md_fin'.$i.'" style="display: hidden"><div>'.supfirstdiv($echopargroupe[$value])."</div></fieldset></div>"; // j ai virer le duxieme div id (au cas ou sa bugerai)
					}
					else
						$echopargroupe[$str3['groupparent']] = $echopargroupe[$str3['groupparent']].'<div class = "question'.$vqgroupid.'" style="display: hidden"><fieldset><legend>'.$str3['description'].'</legend><div>'.$echopargroupe[$value]."</fieldset></div>";
					unset($arrayjson[$key]);
					$arrayjson[] = $str3['groupparent'];
				}
				$i++;
			}
			$arrayjson = array_unique($arrayjson);
			$arrayjson = array_values($arrayjson);
			$arraygrouparrent = array_unique($arraygrouparrent);
			$arraygrouparrent = array_values($arraygrouparrent);
		}
		foreach ($arrayjson as $key => $value)
		{
			$req_pre = $bdd->prepare('SELECT groupname, description, groupparent, gquestion FROM project_'.htmlspecialchars($_SESSION['project']).'_groupe WHERE id= '.htmlspecialchars($value).";"); 
			$req_pre->execute();
			$str3 = $req_pre->fetch();
			$vqgroupid = $value;
			if ($value == 0)
			{
				//$str3['groupname'] = "General";
				$echofinal = $echofinal.'<h3><p class = gdesc'.$vqgroupid.'>'.$str3['description'].'</p></h3>'.'<div class = "question'.$vqgroupid.'" style="display: hidden">'.$echopargroupe[$value]."</div>";
			}
			else
				$echofinal = $echofinal.'<h3><p class = gdesc'.$vqgroupid.'>'.$str3['description'].'</p></h3>'.'<div class = "question'.$vqgroupid.'" style="display: hidden">'.$echopargroupe[$value]."</div>";

		}
		$arrayjson = array_unique($arrayjson);
		$arrayjson = array_values($arrayjson);
		$arrayjson3 = array_unique($arrayjson3);
		$arrayjson3 = array_values($arrayjson3);
		$arrayjson4 = array_unique($arrayjson4);
		$arrayjson4 = array_values($arrayjson4);
		echo '</ul>';
		echo '<div id="progressbar"><div id="indicator"></div><div id="progressnum">0%</div></div>';
		echo '<div class = "formulaire2">';
		echo '<div class="rightbar"></div>';
		echo '<h1 id = bilan>BILAN</h1>';
		//echo $introdesc;
		echo '<form action="updatetimesheet.php" method="post" id="formulaireid">';
		echo $echofinal;
		echo '<input type="button" class = "from_inputleft btn-large waves-light" id = "go_back" value="Retour" name = "retour">';
		echo '<input type="button" class = "from_inputright btn-large waves-light" id = "target" value="Suivant" name = "suivant">';
		echo '<input type="submit" class = "from_inputright btn-large waves-light" id = "next" value="Envoyer" name = "submit"></form>';
?>
	<script type="text/javascript" src="http://code.jquery.com/jquery-1.8.0.min.js"></script>
	<script type="text/javascript" src="http://ajax.aspnetcdn.com/ajax/jquery.validate/1.9/jquery.validate.js"></script>
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
						$js_array4 = json_encode($arrayjson4);
						echo "var type_array = ".$js_array4.";\n";
					?>
					var nbtmp = 0;
					var maxprogress = 100; // total à atteindre
					var actualprogress = 0; // valeur courante
					var itv = 0; // id pour setinterval
					function prog(nb)
					{
						var progressnum = document.getElementById("progressnum");
						var indicator = document.getElementById("indicator");
						actualprogress = ((maxprogress / array.length) * nb).toFixed(0);
						indicator.style.width=actualprogress + "%";
						progressnum.innerHTML = actualprogress + "%";
						progressnum.style.marginLeft=actualprogress + "%";
					}
					function bilan()
					{
						$("[id=next]").show();
						$("[class^=question]").show();
						$("[id=target]").hide();
						$("[class^=gdesc]").show();
						$("[class^=rep]").show();
						$("[class^=lab]").show();
						$("[id=bilan]").show();
						//question_array.forEach(bilanforeach);
					}
					function mdcheck(element, index, array)
					{

						if ($( ".md_debut" + element).find("select").val() != 0 && $( ".md_debut" + element).find("select").val() != "")
							$( ".md_fin" + element).show();
						else
							$( "[class=md_fin" + element + "]").hide();
					}
					function typesummanager(element, index, array)
					{
						console.log("typesummanager" + nbtmp + element);
						var totalPoints = 0;
		 				$('.question' + nbtmp).each(function()
						{
							$(this).find("label:contains(\"" + element + "\")").each(function(i,n)
							{
								totalPoints += parseFloat($("#" + $(n).attr("for")).val(),20);
								console.log("#" + $(n).attr("for"));
								console.log(parseFloat($("#" + $(n).attr("for")).val(),20));
							});
					 	});	
						$('.rightbar').html($('.rightbar').html() + ("<h5>" + element + " = " + totalPoints + "</h5>"));
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
						nbtmp = array[nb];
						$('.rightbar').innerHTML = "";
						type_array.forEach(typesummanager);
						$("[class^=lab]").show();
						$("[class^=rep]").show();
						$("[id=next]").hide();
						$("[class^=gdesc]").hide();
						$("[id=target]").show();
						$("[class^=question]").hide();
						$("[id=intro]").hide();
						//$("[class^=pbar]").css('background-color', '#6BF3FF');
						$("[id=bilan]").hide();
						var str = "[class=question";
						str = str.concat(array[nb]);
						var str2 = "[class=pbar";
						str2 = str2.concat(array[nb]);
						str = str.concat("]");
						str2 = str2.concat("]");
						var str4 = "[class=gdesc";
						str4 = str4.concat(array[nb]);
						str4 = str4.concat("]");
						$(str4).show();
						$(str).show();
						$(str2).css('background-color', '#449CA3');
						md_array.forEach(mdcheck);
						prog(nb);
						if (array.length == 1)
						{
							$("[id=target]").hide();
							$("[id=next]").show();
							$("[class^=gdesc]").hide();
						}
					}
					function mdforeach(element, index, array)
					{
						$( ".md_debut" + element).find("select").on("change", function()
						{
							if (this.value != 0)
								$( ".md_fin" + element).show();
							else
								$( ".md_fin" + element).hide();
						});
					}
					var i = -1;
					$("[class^=question]").hide();
					$("[class^=gdesc]").hide();
					//$("[class^=pbar]").css('background-color', '#6BF3FF');
					//$("[class^=pbar]").hide();
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
					$( "#formulaireid" ).validate();
					jQuery.extend(jQuery.validator.messages,
					{
						required: "",
						remote: "Please fix this field.",
						email: "Please enter a valid email address.",
						url: "Please enter a valid URL.",
						date: "Please enter a valid date.",
						dateISO: "Please enter a valid date (ISO).",
						number: "Please enter a valid number.",
						digits: "Please enter only digits.",
						creditcard: "Please enter a valid credit card number.",
						equalTo: "Please enter the same value again.",
						accept: "Please enter a value with a valid extension.",
						maxlength: jQuery.validator.format("Please enter no more than {0} characters."),
						minlength: jQuery.validator.format("Please enter at least {0} characters."),
						rangelength: jQuery.validator.format("Please enter a value between {0} and {1} characters long."),
						range: jQuery.validator.format("Please enter a value between {0} and {1}."),
						max: jQuery.validator.format("Ce nombre doit être inférieur ou égal à {0}."),
						min: jQuery.validator.format("Ce nombre doit être supérieur ou égal à {0}.")
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
	?>
</div>
	</body>  