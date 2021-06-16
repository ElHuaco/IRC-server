/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 10:58:16 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/06/16 12:35:59 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

// Constructor + Destructor
Command::Command(std::string str, Server server, User commander) : _server(server), _commander(commander)
{
	if (!parseStr(str))
		return ;						// Parse error
	initCommands();
//	execute();						// Should I?
	return;
}

Command::~Command(void)
{
	return ;
}

// Init
void		Command::initCommands(void)
// {
// 	this->_commandList.insert("STATS", commmand_stats);
// 	// I wont do this now, so, etc...
// }

// Parser
int		Command::parseStr(std::string str)
{
	char *aux;
	if ((aux = strtok((char*)str.c_str(), " ")) == 0)
		return (-1);							// Error, the string is empty.
	if (str[0] == ':')					// If there is a prefix. Save prefix + command.
	{
		this->_prefix = aux;
		if ((aux = strtok(0, " ")) == 0)
			return (-1);						// Error, the string doesn't have a command.
		this->_command = aux;
	}
	else									// If there isn't a prefix. Save command.
	{
		this->_prefix = nullptr;
		this->_command = aux;
	}
	int i = 0;
	while (aux != 0 && i < 5)				// While there are parameters, save them.
	{
		aux = strtok(0, "0");
		this->_params[i++] = aux;
	}
	this->_paramsNum = i;
	return (0);
}

// Execute
int			Command::execute(void)
{
		std::map<std::string, commandFt>::iterator it;
	for (it = this->_commandList.begin(); it != this->_commandList.end(); ++it)
		if (it->first == this->_command)
			return (it->second(this->_server, this->_commander, this->_params, this->_paramsNum));
	if (it == this->_commandList.end())
		return (-1);						// Error, bad command.
}
