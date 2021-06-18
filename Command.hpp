/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 11:00:28 by aleon-ca          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/18 09:50:43 by mmonroy-         ###   ########.fr       */
=======
/*   Updated: 2021/06/18 09:51:54 by aleon-ca         ###   ########.fr       */
>>>>>>> b1fca419964b87f8567844ce15659400779527d3
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <map>
# include <locale>
# include "Server.hpp"
# include "User.hpp"

typedef int ftcmd();

class Command
{
	private:
		//cadenas prefix, nombre, params
		//int _num_params
		Server					_server;
		User					_commander;
		std::string				_prefix;
		std::string				_command;
		std::string				*_params;
		std::string				*_erroneus;
		int						_paramsNum;
		std::map<std::string, ftcmd*>	_commandList;

		Command(void);
		Command(const Command &other);
	public:
		// Constructor + Destructor
		Command(std::string str, Server server, User commander); // Prefix, Command and Parameters parser.
		~Command(void);

		// Getters + Setters
		std::string		*getParams() const;
		std::string		*getErroneus() const;

		// Functions
		void			initCommands();
		int				parseStr(std::string str);
		int				execute();

		// Commands
		int				ftNICK();
		int				ftUSER();
		int				ftOPER();
		int				ftQUIT();
		int				ftJOIN();
		int				ftPART();
		int				ftTOPIC();
		int				ftNAMES();
		int				ftLIST();
		int				ftKICK();
};
