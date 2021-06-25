#include "Command.hpp"


// Constructor + Destructor
Command::Command(std::string str, Server &server, User &commander) : _server(server), _commander(commander)
{
	this->_params = new std::string[5];
	this->_erroneous = new std::string[5];
	if (!parseStr(str))
		return ;					// Parse error
//	execute();						// Should I?
	return;
}

Command::~Command(void)
{
	delete[] this->_params;
	delete[] this->_erroneous;
	return ;
}

// String/buff parser
int		Command::parseStr(std::string str)
{

	#ifdef DEBUG
		std::cout << "Buff = \"" << str << "\"" << std::endl;
	#endif
	if (str.empty())
		return (-1);						// Error, the string is empty.
	int pos1 = 0;
	int pos2 = str.find(" ");
	std::cout << pos2 << std::endl;
	std::cout << str.find("\r\n", pos1) << std::endl;
	this->_command = str.substr(pos1, pos2);
	#ifdef DEBUG
		std::cout << "Command = \"" << this->_command << "\"" << std::endl;
	#endif
	int i = 0;
	while (i < 5)				// While there are parameters, save them.
	{
		pos1 = pos2 + 1;
		pos2 = str.find(" ", pos1);
		if (pos2 == std::string::npos || str[pos1] == ':')
			pos2 = str.find("\r\n", pos1);
		if (pos2 <= pos1)
			break;
		this->_params[i++] = str.substr(pos1, pos2 - pos1);
		#ifdef DEBUG
			std::cout << i << " parameter = \"" << this->_params[i - 1] << "\"" << std::endl;
		#endif
	}
	#ifdef DEBUG
		std::cout << "Ended parser." << std::endl;
	#endif
	this->_paramsNum = i;
	return (0);
}

// Parameter parser
std::vector<std::string>	Command::parseParam(std::string param)
{
	int pos1;
	int pos2 = -1;
	std::vector<std::string> rst;
	while (1)
	{
		pos1 = pos2 + 1;
		pos2 = param.find(",", pos1);
		if (pos2 == std::string::npos)
			pos2 = param.length();
		if (pos2 <= pos1)
			break;
		rst.push_back(param.substr(pos1, pos2 - pos1));
	}
	#ifdef DEBUG
		std::cout << "End of sub parser" << std::endl;
	#endif
	return (rst);
}

// Execute
void		Command::execute(void)
{
	if (this->_command == "NICK")
		this->ftNICK();
	else if (this->_command == "USER")
		this->ftUSER();
	else if (this->_command == "OPER")
		this->ftOPER();
	else if (this->_command == "QUIT")
		this->ftQUIT();
	else if (this->_command == "JOIN")
		this->ftJOIN();
	else if (this->_command == "PART")
		this->ftPART();
	else if (this->_command == "TOPIC")
		this->ftTOPIC();
	else if (this->_command == "NAMES")
		this->ftNAMES();
	else if (this->_command == "LIST")
		this->ftLIST();
	else if (this->_command == "KICK")
		this->ftKICK();
	else if (this->_command == "PRIVMSG")
		this->ftPRIVMSG();
	else if (this->_command == "MODE")
		this->ftMODE();
	else
		this->numeric_reply(421);
	return ;
}

// Commands
void			Command::ftNICK()
{
	// Checking if a nickname has been provided.					(ERR_NONICKNAMEGIVEN)
	if (this->_paramsNum == 0)
	{
		this->numeric_reply(431);
		return ;
	}

	// Checking that the nickname isn't erroneous.					(ERR_ERRONEUSNICKNAME)
	this->_erroneous[0] = this->_params[0];
	int i = -1;
	while (this->_params[0][++i])
		if (!isalnum(this->_params[0][i]) || !isalpha(this->_params[0][0]))
		{
			this->numeric_reply(432);
			return ;
		}

	// Checking if the nickname isn't being used by another user.	(ERR_NICKNAMEINUSE)
	std::list<User *>::iterator it = this->_server.getUsers().begin();
	while (it != this->_server.getUsers().end())
	{
		if ((*it)->getNickname() == this->_params[0])
		{
			this->numeric_reply(433);
			return ;
		}
		it++;
	}

	// Not needed if we dont have server to server connection.		(ERR_NICKCOLLISION)
	//this->numeric_reply(436);

	// Changing the nickname
	this->_commander.setNickname(this->_params[0]);
	std::string ack = ": NICK " + _params[0] + "\r\n";
	send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
	return ;
}


void		Command::ftUSER()
{
	// Checking number of parameters.				(ERR_NEEDMOREPARAMS)
	if (this->_paramsNum < 4)
	{
		this->_erroneous[0] = this->_command;
		this->numeric_reply(461);
		return ;
	}
		
	// Checking if the client is already registered.	(ERR_ALREADYRESGISTRED)
	if (!this->_commander.getUsername().empty())
	{
		this->numeric_reply(462);
		return ;
	}
	
	// Registering, hostname and server parameters are ignored.
	this->_commander.setUsername(this->_params[0]);
	this->_commander.setRealname(this->_params[3]);
	std::string ack = ": USER " + _params[0] + " 0 * " + _params[3] + "\r\n";
	send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
	if (_commander.isWelcomed() == false)
	{
		//numeric_reply 001
		ack = ":ft_irc 001 " + _commander.getNickname()
			+ " Welcome to the Internet Relay Network!\r\n";
		send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
		//numeric_reply 002
		ack = ":ft_irc 002 " + _commander.getNickname()
			+ " Your host is ft_irc\r\n";
		send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
		//numeric_reply 003
		ack = ":ft_irc 003 " + _commander.getNickname()
			+ " This server was created long ago\r\n";
		send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
		//numeric_reply 004
		ack = ":ft_irc 004 " + _commander.getNickname()
			+ " RPL_MYINFO\r\n";
		send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
		//numeric_reply 005
		ack = ":ft_irc 005 " + _commander.getNickname()
			+ " tokens are not supported by this server\r\n";
		send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
		_commander.setWelcomed(true);
	}
	return ;
}


void		Command::ftOPER()
{
	// Checking number of parameters.					(ERR_NEEDMOREPARAMS)
	if (this->_paramsNum < 2)
	{
		this->_erroneous[0] = this->_command;
		this->numeric_reply(461);
		return ;
	}

	// Not needed if we dont use other hosts.			(ERR_NOOPERHOST)
		//this->numeric_reply(491);

	// Checking if the password is valid.				(ERR_PASSWDMISMATCH)
	if (this->_server.getPassword() != this->_params[1])
	{
		this->numeric_reply(464);
		return ;
	}

	// Searching the user/nick and OP.					(RPL_YOUREOPER)
	std::list<User *>::iterator it;
	for (it = this->_server.getUsers().begin(); it != this->_server.getUsers().end(); ++it)
		if ((*it)->getNickname() == this->_params[0])
		{
			this->_commander.setIsOP(true);
			this->numeric_reply(381);
		}
	return;
}


void		Command::ftQUIT()
{
	// Client only?
}


void		Command::ftJOIN()
{
	#ifdef DEBUG
		std::cout << "Entered JOIN..." << std::endl;
	#endif
	// Checking number of parameters.					(ERR_NEEDMOREPARAMS)
	if (this->_paramsNum == 0)
	{
		this->_erroneous[0] = this->_command;
		this->numeric_reply(461);
		return ;
	}
	// Limit of channels at one time?
	
	// Not needed if we don't have channel modes.		(ERR_INVITEONLYCHAN)	473
	//													(ERR_BANNEDFROMCHAN)	474
	//													(ERR_BADCHANNELKEY)		475
	//													(ERR_BADCHANMASK)		476

	// Not needed if we don't implement a limit.		(ERR_CHANNELISTFULL)	471
	//													(ERR_TOOMANYCHANNELS)	405

	// Checking if a channel exist and joining it.		(ERR_NOSUCHCHANNEL)
	//													(RPL_TOPIC)
	
	int j = 0;
	Channel *aux;
	std::vector<std::string> targets = this->parseParam(_params[0]);
	std::vector<std::string>::iterator it = targets.begin();
	for (; it != targets.end(); ++it)
	{
		if (it->empty() == true || (it->at(0) != '&' && it->at(0) != '#'
			&& it->at(0) != '+' && it->at(0) != '!'))
			continue ;
		aux = this->_server.getChannelName(*it);
		if (!aux)
		{
			aux = new Channel(*it);
			aux->getListChanops().push_back(&this->_commander);
			this->_server.addChannel(aux);
			delete aux;
			this->_commander.addChannel(this->_server.getChannelName(*it));
		}
		else
		{
			if (_commander.is_in_channel(aux) == true)
				continue ;
			this->_commander.addChannel(aux);
		}
		std::string buff = ":" + _commander.getNickname() + " JOIN "
			+ *it + "\r\n";
		send(_commander.getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
		//numeric_reply 332;
		if (aux->getTopic().empty() == false)
		{
			buff = ":127.0.0.1 332 " + _commander.getNickname() + " ";
			buff += aux->getName() + " " + aux->getTopic() + "\r\n";
			send(_commander.getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
		}
		//numeric_reply 353;
		buff = ":127.0.0.1 353 " + _commander.getNickname() + " = " + *it
			+ " :";
		for (std::list<User *>::iterator u_iter = _server.getUsers().begin();
			u_iter != _server.getUsers().end(); ++u_iter)
		{
			if ((*u_iter)->is_in_channel(aux) == true)
				buff += (*u_iter)->getNickname() + " ";
		}
		buff += "\r\n";
		send(_commander.getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
		//numeric_reply 366
		buff = ":127.0.0.1 366 " + _commander.getNickname() + " " + *it +
			" :End of /NAMES list\r\n";
		send(_commander.getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
		//server reply to other users on channel
		buff = ":" + _commander.getNickname() + " JOIN " + *it + "\r\n";
		for (std::list<User *>::iterator u_iter = _server.getUsers().begin();
			u_iter != _server.getUsers().end(); ++u_iter)
		{
			if ((*u_iter)->getNickname() != _commander.getNickname() &&
				(*u_iter)->is_in_channel(aux) == true)
				send((*u_iter)->getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
		}
	}
	return ;
}


void		Command::ftPART()
{
	// Check number of parameters.
	if (this->_paramsNum < 1)
	{
		this->numeric_reply(461);
		return;
	}

	// Loop for all the channels given.
	std::vector<std::string> targets = this->parseParam(_params[0]);
	for (std::vector<std::string>::iterator it = targets.begin(); it != targets.end(); ++it)
	{
		this->_erroneous[0] = (*it);
		if (it->empty() == true)
			continue ;

		// Check if channel exist.
		Channel *chan = _server.getChannelName(*it);
		if (chan == nullptr)
		{
			this->numeric_reply(403);
			continue ;
		}

		// Check if the commander/user is in the channel.
		if (_commander.is_in_channel(chan) == false)
		{
			this->numeric_reply(442);
			continue ;
		}

		// Warn all the users of the channel + commander leaves the channel.
		std::string buff = ":" + _commander.getNickname() + " PART "
			+ *it + " " + _params[1] + "\r\n";
		for (std::list<User *>::iterator it2 = _server.getUsers().begin();
			it2 != _server.getUsers().end(); ++it2)
			send((*it2)->getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
		_commander.deleteChannel(*it);
	}
	return;
}


void		Command::ftTOPIC()		// Prints topic of a channel.
{
	// Check number of parameters.
	if (this->_paramsNum < 1)
	{
		this->numeric_reply(461);
		return;
	}

	Channel *aux = this->_server.getChannelName(this->_params[0]);
	this->_erroneous[0] = this->_params[0];
	
	// Check if the channel exist.
	if (!aux)
		this->numeric_reply(403);

	// Check if the commander is on the channel.
	else if (!this->_commander.is_in_channel(aux))
		this->numeric_reply(442);

	// Check if the commander will change the Topic or just recive it.
	else if (this->_paramsNum == 1)		// Wants to know the topic.
	{
		if (aux->getTopic().empty())			// There is no topic.
			this->numeric_reply(331);
		else									// There is a topic.
		{
			this->_erroneous[5] = aux->getTopic();
			this->numeric_reply(332);
			this->_erroneous[1] = aux->getWhoTopicNick();
			this->_erroneous[2] = aux->getWhoTopicSetat();
			this->numeric_reply(333);
		}
	}
	else if (this->_paramsNum >= 2)		// Wants to change the topic.
	{
		if (aux->isChanop(&this->_commander))	// Commander is a channel operator.
		{
			aux->setTopic(this->_params[1]);		// Topic changed.
			aux->setWhoTopicNick(this->_commander.getNickname());
			std::stringstream time;
			time << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			aux->setWhoTopicSetat(time.str());
			this->_erroneous[5] = aux->getTopic();
			this->numeric_reply(332);
// -------- IMPORTANT -------- //
// Should reply with the new topic to every member of the channel.
		}
		else									// Commander is not a channel operator.
			this->numeric_reply(482);
	}
	return;
}


void		Command::ftNAMES()		// List all visible nicknames.
{
	// If there is no arguments an "end of the list" reply is returned.
	if (this->_paramsNum < 1)
	{
		this->_erroneous[0] = ("*");
		this->numeric_reply(366);
		return ;
	}
	std::list<User *> users = this->_server.getUsers();
	Channel *chan;

	// Loop for each channel.
	std::vector<std::string> targets = this->parseParam(_params[0]);
	for (std::vector<std::string>::iterator it = targets.begin(); it != targets.end(); ++it)
	{
		this->_erroneous[0] = "= " + (*it);
		if ((*it).empty() == true)
			continue ;
		
		// Check if the channel exists.
		if ((chan = _server.getChannelName(*it)) != nullptr)	// It exists.
		{
			// List all the users of the channel.
			for (std::list<User *>::iterator u_iter = users.begin(); u_iter != users.end(); ++u_iter)
				if ((*u_iter)->is_in_channel(chan) == true)
				{
					this->_erroneous[4] += (*u_iter)->getNickname() + " ";
				}
			this->numeric_reply(353);
			this->numeric_reply(366);
			this->_erroneous[4].clear();
		}
		else													// There isn't such channel.
			this->numeric_reply(401);
	}
	return ;
}

void		Command::ftMODE()
{
	//RPL_CHANNELMODEIS
	std::string buff = ":127.0.0.1 324 " + _commander.getNickname() + " "
		+ _params[0] + " b,k,l,imnpst\r\n";
	send(_commander.getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
}

void		Command::ftLIST()//list channels & their topics
{
	std::list<Channel *> channels = this->_server.getChannels();
	std::list<Channel *>::iterator c_iter = channels.begin();
	std::string buff;

	for (; c_iter != channels.end(); ++c_iter)
	{
		buff.append(":127.0.0.1 322 ");
		buff.append("#");
		buff.append((*c_iter)->getName());//si no pones esto no funciona
		buff.append(" ");
		buff.append((*c_iter)->getName());
		buff.append(" ");
		//buff.append(itoa(this->_server.getNumUsers()));//no funciona itoa <stdlib.h> ft_itoa??
		buff.append("2");//Numero de prueba
		buff.append(" ");
		buff.append((*c_iter)->getTopic());
		buff.append("\r\n");
		// buff = ":127.0.0.1 322 " + (*c_iter)->getName() + " 6 "
		//  		+ (*c_iter)->getTopic() + "\r\n";
		std::cout << "buff: " << buff << std::endl;
		send(_commander.getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
	}
}


void		Command::ftKICK()
{
	if (_paramsNum < 2)
	{
		this->numeric_reply(461);
		return ;
	}
	if (_commander.getIsOP() == false)
	{
		this->numeric_reply(482);
		return ;
	}
	std::vector<std::string> from = this->parseParam(_params[0]);
	std::vector<std::string> targets = this->parseParam(_params[1]);
	if (from.size() != 1) //No implementado parejas channel-user
		return ;
	Channel *aux = _server.getChannelName(from.at(0));
	if (aux == nullptr)
	{
		this->numeric_reply(403);
		return ;
	}
	if (_commander.is_in_channel(aux) == false)
	{
		this->numeric_reply(442);
		return ;
	}
	for (std::vector<std::string>::iterator it = targets.begin();
		it != targets.end(); ++it)
	{
		User *kicked = _server.getUserNick(*it);
		if (kicked->is_in_channel(aux) == false)
		{
			this->numeric_reply(441);
			continue ;
		}
		//Enviar PART al afectado y modificar sus atributos
		std::string buff = ":" + _commander.getNickname() + " KICK "
			+ from.at(0) + " " + *it + " " + _params[2] + "\r\n";
		kicked->deleteChannel(from.at(0));
		send(kicked->getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
		buff = ":" + kicked->getNickname() + " PART "
			+ from.at(0) + " :Kicked by an operator!\r\n";
		send(kicked->getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
		//Enviar al resto de users en el canal el KICK message
		buff = ":" + _commander.getNickname() + " KICK "
			+ from.at(0) + " " + *it + " " + _params[2] + "\r\n";
		for (std::list<User *>::iterator it2 = _server.getUsers().begin();
			it2 != _server.getUsers().end(); ++it2)
			if ((*it2)->is_in_channel(aux) == true)
				send((*it2)->getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
	}
}


void		Command::ftPRIVMSG()
{
	// Check number of params.
	if (this->_paramsNum == 0)
	{
		this->numeric_reply(411);
		return;
	}
	if (this->_paramsNum == 1)
	{
		this->numeric_reply(412);
		return;
	}

	// Parse first parameter.
	std::vector<std::string> targets = this->parseParam(this->_params[0]);

	//RFC message.
	std::string buff = ":" + _commander.getNickname() + " PRIVMSG";

	// Send message.
	std::vector<std::string>::iterator it;
	for (it = targets.begin(); it != targets.end(); ++it)
	{
		buff += " " + *it + " " + _params[1] + "\r\n";
		User *client;
		Channel *chan;

		// Send to a user.
		if ((*it)[0] != '#' && (client = _server.getUserNick(*it)) != nullptr)
			send(client->getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
		
		// Send to a server.
		else if ((*it)[0] == '#' && (chan = _server.getChannelName(*it)) != nullptr)
		{
			if (_commander.is_in_channel(chan) == false)
			{
				this->_erroneous[0] = (*it);
				this->numeric_reply(404);
				continue ;
			}
			for (std::list<User *>::iterator u_it = _server.getUsers().begin();
				u_it != _server.getUsers().end(); ++u_it)
			{
				if ((*u_it)->getNickname() != _commander.getNickname() &&
					(*u_it)->is_in_channel(chan))
					send((*u_it)->getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
			}
		}

		// There is not such server/user.
		else
		{
			this->_erroneous[0] = (*it);
			this->numeric_reply(401);
		}
	}
	return;
}

// Getters + Setters
std::string		Command::getCommand(void) const
{
	return (this->_command);
}
std::string		*Command::getParams(void) const
{
	return (this->_params);
}

std::string		*Command::getErroneous(void) const
{
	return (this->_erroneous);
}

void			Command::numeric_reply(int key)
{
	// Save in buff standar protocol for msg + <client>.
	std::string buff = ":127.0.0.1 " + std::to_string(key) + " "
		+ _commander.getNickname() + " ";
	// Save in buff <extra data> before the specific msg.
	if (_erroneous != nullptr)
	{
		int i = -1;
		while (_erroneous[++i].empty() == false)
			buff += _erroneous[i] + " ";
	}
	// Select correct msg reply.
	switch (key)		// This is my new favourite toy.
	{
		case 331:		// RPLY_NOTOPIC
			buff += ":No topic is set";
			break;
		case 332:		// RPLY_TOPIC
			buff += ":" + this->_erroneous[4];
			break;
		case 333:		// RPLY_TOPICWHOTIME
			break;
		case 353:		// RPLY_NAMREPLY
			buff += ":" + this->_erroneous[4];
			break;
		case 366:		// RPLY_ENDOFNAMES
			buff += ":End of /NAMES list";
			break;
		case 381:		// RPLY_YOUROPER
			buff += ":You are now an IRC operator";
			break;
		case 401:		// ERR_
			buff += ":No such nick/channel";
			break;
		case 403:		// ERR_
			buff += ":No such channel";
			break;
		case 404:		// ERR_
			buff += ":Cannot send to channel";
			break;
		case 405:		// ERR_
			buff += ":You have joined too many channels";
			break;
		case 407:		// ERR_
			buff += ":Too many recipients/targets";
			break;
		case 411:		// ERR_
			buff += ":No recipient given (" + _command + ")";
			break;
		case 412:		// ERR_
			buff += ":No text to send";
			break;
		case 413:		// ERR_
			buff += ":No toplevel domain specified";
			break;
		case 414:		// ERR_
			buff += ":Wildcard in toplevel domain";
			break;
		case 421:		// ERR_
			buff += this->_command + ":Unknown command";
			break;
		case 431:		// ERR_
			buff += ":No nickname given";
			break;
		case 432:		// ERR_
			buff += ":Erroneous nickname";
			break;
		case 433:		// ERR_
			buff += ":Nickname is already in use";
			break;
		case 436:		// ERR_
			buff += ":Nickname collision KILL from " + _commander.getNickname() + "@HOST";
			break;
		case 437:		// ERR_
			buff += ":Nick/channel is temporarily unavailable";
			break;
		case 441:		// ERR_
			buff += ":They aren't on that channel";
			break;
		case 442:		// ERR_
			buff += ":You're not on that channel";
			break;
		case 461:		// ERR_
			buff += this->_command + ":Not enough parameters";
			break;
		case 462:		// ERR_
			buff += ":Unauthorized command (already registered)";
			break;
		case 464:		// ERR_
			buff += ":Password incorrect";
			break;
		case 471:		// ERR_
			buff += ":Cannot join channel (+l)";
			break;
		case 473:		// ERR_
			buff += ":Cannot join channel (+i)";
			break;
		case 474:		// ERR_
			buff += ":Cannot join channel (+b)";
			break;
		case 475:		// ERR_
			buff += ":Cannot join channel (+k)";
			break;
		case 476:		// ERR_
			buff += ":Bad Channel Mask";
			break;
		case 477:		// ERR_
			buff += ":Channel doesn't support modes";
			break;
		case 482:		// ERR_
			buff += ":You're not channel operator";
			break;
		case 484:		// ERR_
			buff += ":Your connection is restricted!";
			break;
		case 491:		// ERR_
			buff += ":No O-lines for your host";
			break;
		default:
			break;
	}
	// End of msg.
	buff += "\r\n";
	// Send the msg.
	int nbytes = strlen(buff.c_str());
	if (send(_commander.getSocket(), buff.c_str(), nbytes, 0) == -1)
		throw std::runtime_error(strerror(errno));
}
