/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 11:00:28 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/17 10:28:58 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "User.hpp"
# include <map>

class Server;

typedef int (*commandFt) ();
class Command
{
	private:
		//cadenas prefix, nombre, params
		//int _num_params
		Server					_server;
		User					_commander;
		std::string				_prefix;
		std::string				_command;
		std::string				_params[5];
		int						_paramsNum;
		std::map<std::string, commandFt>	_commandList;

		Command(void);
		Command(const Command &other);
	public:
		// Constructor + Destructor
		Command(std::string str, Server server, User commander); // Prefix, Command and Parameters parser.
		~Command(void);

		// Getters + Setters

		// Functions
		void			initCommands();
		int				parseStr(std::string str);
		int				execute();

		// Commands
		commandFt		ftNICK();
		commandFt		ftUSER();
		commandFt		ftOPER();
		commandFt		ftQUIT();
		commandFt		ftJOIN();
		commandFt		ftPART();
		commandFt		ftTOPIC();
		commandFt		ftNAMES();
		commandFt		ftLIST();
		commandFt		ftKICK();

};
# include "Server.hpp"
