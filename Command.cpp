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
	if (this->_command == "NICK")
		return (this->ftNICK());
	else if (this->_command == "USER")
		return (this->ftUSER());
	else if (this->_command == "OPER")
		return (this->ftOPER());
	else if (this->_command == "QUIT")
		return (this->ftQUIT());
	else if (this->_command == "JOIN")
		return (this->ftJOIN());
	else if (this->_command == "PART")
		return (this->ftPART());
	else if (this->_command == "TOPIC")
		return (this->ftTOPIC());
	else if (this->_command == "NAMES")
		return (this->ftNAMES());
	else if (this->_command == "LIST")
		return (this->ftKICK());
	else if (this->_command == "KICK")
		return (this->ftKICK());
	return (-1);
}

// Commands
int			Command::ftNICK()
{
	// Checking if a nickname has been provided.					(ERR_NONICKNAMEGIVEN)
	if (this->_paramsNum == 0)
		return (431);

	// Checking that the nickname isn't erroneous.					(ERR_ERRONEUSNICKNAME)
	int i = 0;
	if (!isalpha(this->_params[0][i]))
	{
		this->_erroneous[0] = this->_params[0];
		return (432);
	}
	while (this->_params[0][++i])
		if (!isalnum(this->_params[0][i]))
		{
			this->_erroneous[0] = this->_params[0];
			return (431);
		}

	// Checking if the nickname isn't being used by another user.	(ERR_NICKNAMEINUSE)
	std::list<User *>::iterator it;
	for (it = this->_server.getUsers().begin(); it != this->_server.getUsers().end(); ++it)
		if ((*it)->getNickname() == this->_params[0])
		{
			this->_erroneous[0] = this->_params[0];
			return (433);
		}

	// Not needed if we dont have server to server connection.		(ERR_NICKCOLLISION)
	//return (436);

	// Changing the nickname
	this->_commander.setNickname(this->_params[0]); 
	return (0);
}


int		Command::ftUSER()
{
	// Checking number of parameters.				(ERR_NEEDMOREPARAMS)
	if (this->_paramsNum < 4)
	{
		this->_erroneous[0] = this->_command;
		return (461);
	}
		
	// Checking if the client is already registered.	(ERR_ALREADYRESGISTRED)
	if (!this->_commander.getUsername().empty())
		return (462);
	
	// Registering, hostname and server parameters are ignored.
	this->_commander.setUsername(this->_params[0]);
	this->_commander.setRealname(this->_params[3]);
	return (0);
}


int		Command::ftOPER()
{
	// Checking number of parameters.					(ERR_NEEDMOREPARAMS)
	if (this->_paramsNum < 2)
	{
		this->_erroneous[0] = this->_command;
		return (461);
	}

	// Not needed if we dont use other hosts.			(ERR_NOOPERHOST)
		//return (491);

	// Checking if the password is valid.				(ERR_PASSWDMISMATCH)
	if (this->_server.getPassword() != this->_params[1])
		return (464);

	// Searching the user/nick and OP.					(RPL_YOUREOPER)
	std::list<User *>::iterator it;
	for (it = this->_server.getUsers().begin(); it != this->_server.getUsers().end(); ++it)
		if ((*it)->getNickname() == this->_params[0] || (*it)->getUsername() == this->_params[0])
		{
			this->_commander.setIsOP(true);
			return (381);
		}
	// If no user/nick, standar return?
	return (0);
}


int		Command::ftQUIT()
{
	// Client only?
	return (0);
}


int		Command::ftJOIN()
{
	// Checking number of parameters.					(ERR_NEEDMOREPARAMS)
	if (this->_paramsNum == 0)
	{
		this->_erroneous[0] = this->_command;
		return (461);
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
			Channel *chan = new Channel(this->_params[i]);
			this->_server.addChannel(chan);
			this->_erroneous[j++] = this->_params[i];
			//return (403);
		}
		else
		{
			//getTopic.
			//Meter user en la lista.
		}
	}
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


int		Command::ftNAMES()//List all visible nicknames 
{
	std::list<User *> users = this->_server.getUsers();
	std::list<User *>::iterator u_iter = users.begin();

	for (; u_iter != users.end(); ++u_iter)
		std::cout << (*u_iter)->getNickname() << std::endl;//Habrá que imprimir con un mensaje formateado
	return (0);
}


int		Command::ftLIST()//list channels & their topics
{
	std::list<Channel *> channels = this->_server.getChannels();
	std::list<Channel *>::iterator c_iter = channels.begin();

	for (; c_iter != channels.end(); ++c_iter)
	{
		std::cout << (*c_iter)->getName() << std::endl;
		std::cout << (*c_iter)->getTopic() << std::endl;//Habrá que imprimir con un mensaje formateado
	}
	return (0);
}


int		Command::ftKICK()
{
	return (0);
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
