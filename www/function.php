<?php
	class Securite
	{
		public static function bdd($string)
		{
			if(ctype_digit($string))
			{
				$string = intval($string);
			}
			else
			{
				$string = mysql_real_escape_string($string);
				$string = addcslashes($string, '%_');
			}
				
			return $string;

		}
		public static function html($string)
		{
			return htmlentities($string);
		}
	}
?>