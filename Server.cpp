/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 09:56:15 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/16 12:10:28 by aleon-ca         ###   ########.fr       */
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
	_users.push_back(User(newfd).clone());
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
static int				max_element(void)
{
	int max = 0;
	for (u_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if ((*it)->getSocket() > max)
			max = (*it)->getSocket();
	}
	return (max);
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
				_max = max_element();
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
			if (fd == _max)
				_max = max_element();
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
