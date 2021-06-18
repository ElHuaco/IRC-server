/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 11:00:28 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/18 09:44:59 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <map>
# include <locale>

class Server;
class User;

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
# include "User.hpp"
# include "Server.hpp"
