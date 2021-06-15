/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 11:00:28 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/15 12:56:39 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Server.hpp"
# include "User.hpp"

typedef int (*commandFt) (Server server, User commander, std::string *params, int paramsNum);
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
		std::list<std::pair<std::string, commandFt>>	_commandList;

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

};
