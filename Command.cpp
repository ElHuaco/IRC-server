/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 10:58:16 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/06/18 09:29:16 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"


// Constructor + Destructor
Command::Command(std::string str, Server server, User commander) : _server(server), _commander(commander)
{
	this->_params = new std::string[5];
	if (!parseStr(str))
		return ;					// Parse error
	initCommands();
//	execute();						// Should I?
	return;
}

Command::~Command(void)
{
	delete[] this->_params;
	return ;
}

// Init
void		Command::initCommands(void)
{
	this->_commandList["NICK"] = this->ftNICK;
	/*this->_commandList["USER"] = this->ftUSER;
 	this->_commandList.insert(std::pair<std::string, int (**)()>("NICK", this->ftNICK()));
 	this->_commandList.insert(std::pair<std::string, int>("USER", this->ftUSER()));
 	this->_commandList.insert(std::pair<std::string, int>("OPER", this->ftOPER()));
 	this->_commandList.insert(std::pair<std::string, int>("QUIT", this->ftQUIT()));
 	this->_commandList.insert(std::pair<std::string, int>("JOIN", this->ftJOIN()));
 	this->_commandList.insert(std::pair<std::string, int>("PART", this->ftPART()));
 	this->_commandList.insert(std::pair<std::string, int>("TOPIC", this->ftTOPIC()));
 	this->_commandList.insert(std::pair<std::string, int>("NAMES", this->ftNAMES()));
 	this->_commandList.insert(std::pair<std::string, int>("LIST", this->ftLIST()));
 	this->_commandList.insert(std::pair<std::string, int>("KICK", this->ftKICK()));*/
}

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
	//std::map<std::string, ftcmd>::iterator it;
	//ftcmd aux = this->_commandList[this->_command];
	/*for (it = this->_commandList.begin(); it != this->_commandList.end(); ++it)
		if (it->first == this->_command)
			return (it->second());*/
	//if (it == this->_commandList.end())
		//return (-1);						// Error, bad command.
}

// Commands
int			Command::ftNICK()
{
	// Checking if a nickname has been provided.					(ERR_NONICKNAMEGIVEN)
	if (this->_paramsNum == 0)
		return (431);

	// Checking that the nickname isn't erroneus.					(ERR_ERRONEUSNICKNAME)
	int i = 0;
	if (!isalpha(this->_params[0][i]))
		return (432);
	while (this->_params[0][++i])
		if (!isalnum(this->_params[0][i]))
			return (432);

	// Checking if the nickname isn't being used by another user.	(ERR_NICKNAMEINUSE)
	std::vector<User *>::iterator it;
	for (it = this->_server.getUsers().begin(); it != this->_server.getUsers().end(); ++it)
		if ((*it)->getNickname() == this->_params[0])
			return (433);

	// Not needed if we dont have server to server connection.		(ERR_NICKCOLLISION)
	//return (436);

	// Changing the nickname
	this->_commander.setNickname(this->_params[0]); 
	return (0);
}
int		Command::ftUSER()
{
	return (0);
}
int		Command::ftOPER()
{
	// Checking number of parameters.				(ERR_NEEDMOREPARAMS)
	if (this->_paramsNum < 2)
		return (461);
	

	// Not needed if we dont use other hosts.		(ERR_NOOPERHOST)
		//return (491);
	
	return (0);
}
int		Command::ftQUIT()
{
	// Client only?
	return (0);
}
int		Command::ftJOIN()
{
	return (0);
}
int		Command::ftPART()
{
	return (0);
}
int		Command::ftTOPIC()
{
	return (0);
}
int		Command::ftNAMES()
{
	return (0);
}
int		Command::ftLIST()
{
	return (0);
}
int		Command::ftKICK()
{
	return (0);
}

// Getters + Setters
std::string		*Command::getParams(void) const
{
	return (this->_params);
}
