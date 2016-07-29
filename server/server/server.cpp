// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "all.h"

string	replacespace(string name)
{
	int i = -1;

	while (name[++i])
	{
		if (name[i] == ' ')
			name[i] = '_';
	}
	return (name);
}

int		main()
{
	string comande;
	project project(PATH);

	cout << "running\n";
//	buildenv();
	project.projectshow();
//	srand(time(NULL));
	//cout << std::system("./send_mail.php");
	///send_mail();
	while (1)
	{
		std::getline(std::cin, comande);
		if (comande.compare("exit") == 0)
		{
			return(0);
			ft_exit();
		}
		if (comande.compare("send") == 0)
		{
			cout << "sending\n";
			project.send();
		}
		cout << comande << "\n";
	}
    return 0;
}

