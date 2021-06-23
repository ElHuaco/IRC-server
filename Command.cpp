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

// Parser
int		Command::parseStr(std::string str)
{
	if (str.empty())
		return (-1);						// Error, the string is empty.
	int pos1 = 0;
	int pos2 = str.find(" ");
	this->_command = str.substr(pos1, pos2);
	int i = 0;
	while (i < 5)				// While there are parameters, save them.
	{
		pos1 = pos2 + 1;
		pos2 = str.find(" ", pos1);
		if (pos2 == std::string::npos)
			pos2 = str.find("\n", pos1) - 1;
		if (pos2 <= pos1)
			break;
		this->_params[i++] = str.substr(pos1, pos2 - pos1);
	}
	#ifdef DEBUG
		std::cout << "Ended parser." << std::endl;
	#endif
	this->_paramsNum = i;
	return (0);
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
}

// Commands
void			Command::ftNICK()
{
	// Checking if a nickname has been provided.					(ERR_NONICKNAMEGIVEN)
	if (this->_paramsNum == 0)
		this->numeric_reply(431);

	// Checking that the nickname isn't erroneous.					(ERR_ERRONEUSNICKNAME)
	int i = 0;
	if (!isalpha(this->_params[0][i]))
	{
		this->_erroneous[0] = this->_params[0];
		this->numeric_reply(432);
	}
	while (this->_params[0][++i])
		if (!isalnum(this->_params[0][i]))
		{
			this->_erroneous[0] = this->_params[0];
			this->numeric_reply(431);
		}

	// Checking if the nickname isn't being used by another user.	(ERR_NICKNAMEINUSE)
	std::list<User *>::iterator it;
	for (it = this->_server.getUsers().begin(); it != this->_server.getUsers().end(); ++it)
		if ((*it)->getNickname() == this->_params[0])
		{
			this->_erroneous[0] = this->_params[0];
			this->numeric_reply(433);
		}

	// Not needed if we dont have server to server connection.		(ERR_NICKCOLLISION)
	//this->numeric_reply(436);

	// Changing the nickname
	this->_commander.setNickname(this->_params[0]);
	std::string ack = ": NICK " + _params[0] + "\r\n";
	send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
}


void		Command::ftUSER()
{
	// Checking number of parameters.				(ERR_NEEDMOREPARAMS)
	if (this->_paramsNum < 4)
	{
		this->_erroneous[0] = this->_command;
		this->numeric_reply(461);
	}
		
	// Checking if the client is already registered.	(ERR_ALREADYRESGISTRED)
	if (!this->_commander.getUsername().empty())
		this->numeric_reply(462);
	
	// Registering, hostname and server parameters are ignored.
	this->_commander.setUsername(this->_params[0]);
	this->_commander.setRealname(this->_params[3]);
	std::string ack = ": USER " + _params[0] + " 0 * " + _params[3] + "\r\n";
	send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
	if (_commander.isWelcomed() == false)
	{
		ack = ":ft_irc 001 " + _commander.getNickname()
			+ " Welcome to the Internet Relay Network!\r\n";
		send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
		ack = ":ft_irc 002 " + _commander.getNickname()
			+ " Your host is ft_irc\r\n";
		send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
		ack = ":ft_irc 003 " + _commander.getNickname()
			+ " This server was created long ago\r\n";
		send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
		ack = ":ft_irc 004 " + _commander.getNickname()
			+ " RPL_MYINFO\r\n";
		send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
		ack = ":ft_irc 004 " + _commander.getNickname()
			+ " tokens are supported by this server\r\n";
		send(_commander.getSocket(), ack.c_str(), strlen(ack.c_str()), 0);
		_commander.setWelcomed(true);
	}
}


void		Command::ftOPER()
{
	// Checking number of parameters.					(ERR_NEEDMOREPARAMS)
	if (this->_paramsNum < 2)
	{
		this->_erroneous[0] = this->_command;
		this->numeric_reply(461);
	}

	// Not needed if we dont use other hosts.			(ERR_NOOPERHOST)
		//this->numeric_reply(491);

	// Checking if the password is valid.				(ERR_PASSWDMISMATCH)
	if (this->_server.getPassword() != this->_params[1])
		this->numeric_reply(464);

	// Searching the user/nick and OP.					(RPL_YOUREOPER)
	std::list<User *>::iterator it;
	for (it = this->_server.getUsers().begin(); it != this->_server.getUsers().end(); ++it)
		if ((*it)->getNickname() == this->_params[0] || (*it)->getUsername() == this->_params[0])
		{
			this->_commander.setIsOP(true);
			this->numeric_reply(381);
		}
	// If no user/nick, standar return?
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
	
	int i = -1;
	int j = 0;
	Channel *aux;
	while (++i < 5)
	{
		aux = this->_server.getChannelName(this->_params[i]);
		if (!aux)
		{
			aux = new Channel(_params[i]);
			this->_server.addChannel(aux);
			delete aux;
			this->_commander.addChannel(this->_server.getChannelName(_params[i]));
			//Mensaje JOIN, RPL_TOPIC, RPL_USERLIST
			std::string buff = ":" + _commander.getNickname() + "@"
				+ _commander.getUsername() + "!127.0.0.1 JOIN "
				+ _params[i] + "\r\n";
			send(_commander.getSocket(), buff.c_str(), strlen(buff.c_str()), 0);
			return ;
			//numeric_reply(332);
			//numeric_reply(353);
			// this->_erroneous[j++] = this->_params[i];
			// this->numeric_reply(403);
		}
		else
		{
			std::list<Channel *>::iterator it;
			for (it = this->_server.getChannels().begin(); it != this->_server.getChannels().end(); ++it)
				if ((*it)->getName() == this->_params[i])
				{
					this->_commander.addChannel(*it);
					// Imprimir topic
					// this->numeric_reply(381);
				}
		}
	}
}


void		Command::ftPART()
{
}


void		Command::ftTOPIC()
{
}


void		Command::ftNAMES()//List all visible nicknames 
{
	std::list<User *> users = this->_server.getUsers();
	std::list<User *>::iterator u_iter = users.begin();

	for (; u_iter != users.end(); ++u_iter)
		std::cout << "Users on #Channel: " <<(*u_iter)->getNickname() << " ";
}


void		Command::ftLIST()//list channels & their topics
{
	// std::list<Channel *> channels = this->_server.getChannels();
	// std::list<Channel *>::iterator c_iter = channels.begin();

	std::string aux;
	aux.append(":127.0.0.1 322 ");
	aux.append("#");
	aux.append("Name channel ");
	aux.append("NunUsers ");
	aux.append("[topic]\n");

	for (int j = 0; j <= this->_server.getMax(); ++j)
	{
		if (FD_ISSET(j, &this->_server.getMaster()))
		{
			send(j, aux.c_str(), strlen(aux.c_str()), 0);//asi funciona pero hay que mejorar
		}
	}

	// for (; c_iter != channels.end(); ++c_iter)
	// {
	// 	std::cout << "#" << (*c_iter)->getName() << "\t" \
	// 		<< this->_server.getNumUsers() << "\t" \
	// 		<< (*c_iter)->getTopic() << std::endl;
	// }
}


void		Command::ftKICK()
{
}


void		Command::ftPRIVMSG()
{
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
	std::string buff = ":127.0.0.1 " + std::to_string(key) + " "
		+ _commander.getNickname() + " ";
	if (_erroneous != nullptr)
	{
		int i = -1;
		while (_erroneous[++i].empty() == false)
			buff += _erroneous[i];
	}
	if (key == 401)
		buff += ":No such nick/channel";
	else if (key == 403)
		buff += ":No such channel";
	else if (key == 404)
		buff += ":Cannot send to channel";
	else if (key == 405)
		buff += ":You have joined too many channels";
	else if (key == 407)
		buff += ":Too many recipients/targets";
	else if (key == 411)
		buff += ":No recipient given (" + _command + ")";
	else if (key == 412)
		buff += ":No text to send";
	else if (key == 413)
		buff += ":No toplevel domain specified";
	else if (key == 414)
		buff += ":Wildcard in toplevel domain";
	else if (key == 421)
		buff += _command + ":Unknown command";
	else if (key == 431)
		buff += ":No nickname given";
	else if (key == 432)
		buff += ":Erroneous nickname";
	else if (key == 433)
		buff += ":Nickname is already in use";
	else if (key == 436)
		buff += ":Nickname collision KILL from " + _commander.getNickname()
			+ "@HOST";
	else if (key == 437)
		buff += ":Nick/channel is temporarily unavailable";
	else if (key == 441)
		buff += ":They aren't on that channel";
	else if (key == 442)
		buff += ":You're not on a channel";
	else if (key == 461)
		buff += ":Not enough parameters";
	else if (key == 462)
		buff += ":Unauthorized command (already registered)";
	else if (key == 464)
		buff += ":Password incorrect";
	else if (key == 471)
		buff += ":Cannot join channel (+l)";
	else if (key == 473)
		buff += ":Cannot join channel (+i)";
	else if (key == 474)
		buff += ":Cannot join channel (+b)";
	else if (key == 475)
		buff += ":Cannot join channel (+k)";
	else if (key == 476)
		buff += ":Bad Channel Mask";
	else if (key == 477)
		buff += ":Channel doesn't support modes";
	else if (key == 482)
		buff += ":You're not channel operator";
	else if (key == 484)
		buff += ":Your connection is restricted!";
	else if (key == 491)
		buff += ":No O-lines for your host";
	buff += "\r\n";
	int nbytes = strlen(buff.c_str());
	if (send(_commander.getSocket(), buff.c_str(), nbytes, 0) == -1)
		throw std::runtime_error(strerror(errno));
}
