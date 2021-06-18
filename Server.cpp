/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 09:56:15 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/17 12:24:18 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(void)
{
}
Server::~Server(void)
{
	for (u_iterator it = _users.begin(); it != _users.end(); ++it)
		delete *it;
	_users.clear();
//	for (c_iterator it2 = _channels.begin(); it2 != _channels.end(); ++it2)
//		delete *it2;
//	_channels.clear();
	std::cout << "Server conf destroyed" << std::endl;
}

Server & Server::operator=(const Server &rhs)
{
	this->_master = rhs._master;
	this->_max = rhs._max;
	this->_listener = rhs._listener;
	this->_password = rhs._password;
	return (*this);
}

void	Server::start(const std::string &port_listen, const std::string &host,
		const std::string &port_network, const std::string &password_network)
{
	//TODO?: Código de enviar a host:port_network
	//Código de escuchar en port_listen
	struct addrinfo hints, *servinfo;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	const char *node = NULL;
	const char *port = port_listen.c_str();
	int status;
	if ((status = getaddrinfo(node, port, &hints, &servinfo)) != 0)
	{
		std::cout << "Server(): getaddrinfo() error: " << status << std::endl;
		throw std::runtime_error("Server(): getaddrinfo() error");
	}
	if ((_listener = socket(servinfo->ai_family, servinfo->ai_socktype,
		servinfo->ai_protocol)) == -1)
		throw std::runtime_error(strerror(errno));
	int yes = 1;
	if (setsockopt(_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1)
		throw std::runtime_error(strerror(errno));
	if (fcntl(_listener, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error(strerror(errno));
	if (bind(_listener, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
		throw std::runtime_error(strerror(errno));
	freeaddrinfo(servinfo);
	if (listen(_listener, 10) == -1)
		throw std::runtime_error(strerror(errno));
	FD_ZERO(&_master);
	FD_SET(_listener, &_master);
	_max = _listener;
	std::cout << "Server conf finished" << std::endl;
}

void					Server::setMax(int max)
{
	_max = max;
}
int						Server::getMax(void) const
{
	return (_max);
}
void					Server::setMaster(fd_set set)
{
	FD_COPY(&set, &_master);
}
fd_set					&Server::getMaster(void)
{
	return (_master);
}
void					Server::setPassword(const std::string &password)
{
	_password = password;
}
std::string				Server::getPassword(void) const
{
	return (_password);
}
int						Server::getListener(void) const
{
	return (_listener);
}
std::vector<User *>		Server::getUsers(void) const
{
	return (_users);
}
void					Server::addUser(void)
{
	struct sockaddr_storage remoteaddr;
	socklen_t addrlen = sizeof remoteaddr;
	int newfd = accept(_listener, (struct sockaddr *)&remoteaddr,
		&addrlen);
	if (newfd == -1)
		throw std::runtime_error(strerror(errno));
	if (fcntl(newfd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error(strerror(errno));
	_users.push_back(User(newfd).clone());
	//RPL_WELCOME
	//	buff = ":Welcome to the Internet Relay Network " + nick + "! "
	//		+ user + "@HOST";
	FD_SET(newfd, &_master);
	if (newfd > _max)
		_max = newfd;
}
User					*Server::getSocketUser(int socket)
{
	for (u_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if ((*it)->getSocket() == socket)
			return (*it);
	}
	return (nullptr);
}
void					Server::deleteUser(int fd)
{
	for (u_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if ((*it)->getSocket() == fd)
		{
			close(fd);
			FD_CLR(fd, &_master);
			delete *it;
			_users.erase(it);
			if (fd == _max)
			{
				int max = 0;
				for (u_iterator it = _users.begin(); it != _users.end(); ++it)
				{
					if ((*it)->getSocket() > max)
						max = (*it)->getSocket();
				}
				_max = max;
			}
			return ;
		}
	}
}
void					Server::deleteUser(const std::string &nick)
{
	for (u_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if ((*it)->getNickname() == nick)
		{
			close((*it)->getSocket());
			FD_CLR((*it)->getSocket(), &_master);
			delete *it;
			_users.erase(it);
			if ((*it)->getSocket() == _max)
			{
				int max = 0;
				for (u_iterator it = _users.begin(); it != _users.end(); ++it)
				{
					if ((*it)->getSocket() > max)
						max = (*it)->getSocket();
				}
				_max = max;
			}
			return ;
		}
	}
}
/*
std::vector<Channel *>	Server::getChannels(void) const
{
	return (_channels);
}
void					Server::addChannel(void)
{
}
void					Server::deleteChannel(void)
{
}
*/
void					Server::message(int fd, char *buff, int nbytes)
{
	this->getSocketUser(fd)->message(*this, buff, nbytes);
}
void					Server::error_reply(const std::string &cmd,
		const std::string &arg, int key)
{
	//arg vacío si no se detectó argumento erroneo.
	//REPLIES:
	// PASS: ERR_NEEDMOREPARAMS ERR_ALEADYREGISTERED
	// NICK: ERR_NONICKNAMEGIVEN ERR_NICKNAMEINUSE ERR_UNAVAILRESOURCE
	//  ERR_ERRONEUSNICKNAME ERR_NICKCOLLISION ERR_RESTRICTED
	// USER: no nuevos
	// OPER: RPL_YOUREOPER ERR_NOOPERHOST ERR_PASSWDMISMATCH
	// QUIT: no nuevos
	// JOIN: ERR_BANNEDFROMCHAN ERR_INVITEONLYCHAN ERR_BADCHANNELKEY
	//  ERR_CHANNELISFULL ERR_BADCHANMASK ERR_NOSUCHCHANNEL ERR_TOOMANYCHANNELS
	//  ERR_TOOMANYTARGETS RPL_TOPIC
	// PART: ERR_NOTONCHANNEL
	// TOPIC: ERR_NOTOPIC ERR_CHANOPRIVSNEEDED ERR_NOCHANMODES
	// NAMES: RPL_NAMEREPLY RPL_ENDOFNAMES
	// LIST: RPL_LIST RPL_LISTEND
	// KICK: ERR_USERNOTINCHANNEL
	// PRIVMSG: ERR_NORECIPIENT ERR_NOTEXTTOSEND ERR_CANNOTSENDTOCHAN
	//  ERR_NOTOPLEVEL ERR_WILDTOPLEVEL ERR_NOSUCHNICK RPL_AWAY
	std::string buff(arg);
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
		buff += ":No recipient given";
	else if (key == 412)
		buff += ":No text to send";
	else if (key == 413)
		buff += ":No toplevel domain specified";
	else if (key == 414)
		buff += ":Wildcard in toplevel domain";
	else if (key == 461)
		buff += cmd + ":Not enough parameters";
	else if (key == 462)
		buff += ":Unauthorized command (already registered)";
	else if (key == 431)
		buff += ":No nickname given";
	else if (key == 432)
		buff += ":Erroneous nickname";
	else if (key == 433)
		buff += ":Nickname is already in use";
	else if (key == 436)
		buff += ":Nickname collision KILL from " + user + "@HOST";
	else if (key == 437)
		buff += ":Nick/channel is temporarily unavailable";
	else if (key == 441)
		buff += ":They aren't on that channel";
	else if (key == 442)
		buff += ":You're not on a channel";
	else if (key == 464)
		buff += ":Password incorrect";
	else if (key == 471)
		buff += " :Cannot join channel (+l)";
	else if (key == 473)
		buff += " :Cannot join channel (+i)";
	else if (key == 474)
		buff += " :Cannot join channel (+b)";
	else if (key == 475)
		buff += " :Cannot join channel (+k)";
	else if (key == 476)
		buff += " :Bad Channel Mask";
	else if (key == 477)
		buff += " :Channel doesn't support modes";
	else if (key == 482)
		buff += " :You're not channel operator";
	else if (key == 484)
		buff += ":Your connection is restricted!";
	else if (key == 491)
		buff += ":No O-lines for your host";
	buff += "\r\n";
	nbytes = strlen(buff.c_str());
	if (send(client->getSocket(), buff.c_str(), nbytes, 0) == -1)
		throw std::runtime_error(strerror(errno));
}
