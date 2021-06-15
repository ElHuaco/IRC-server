/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 09:56:15 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/15 11:19:56 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(void)
{
}
Server::~Server(void)
{
}

void	Server::start(const std::string &port_listen, const std::string &host,
		const std::string &port_network, const std::string &password_network)
{
	//TODO: Código de enviar a host:port_network
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
	// connect() si dan host???
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
}/*
std::vector <User>		Server::getUsers(void) const
{
	return (_users);
}
std::vector <Channel>	Server::getChannels(void) const
{
	return (_channels);
}*/
int						Server::getListener(void) const
{
	return (_listener);
}
