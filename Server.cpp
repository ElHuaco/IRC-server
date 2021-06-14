/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 09:56:15 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/14 11:27:41 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const std::string &host = std::string(),
	const std::string &port_network = std::string(),
	const std::string &password_network = std::string(),
	const std::string &port_listen, const std::string &password) :
	_password(password)
{
	struct addrinfo hits, *servinfo, *p;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	const char *node = NULL;
//	if (host.empty() == false)
//		node = host.c_str();
	const char *port = "6667";
//	if (port_network.empty() == false)
//		port = port_network.c_str();
	int status;
	if ((status = getaddrinfo(node, port, &hints, &servinfo)) != 0)
	{
		std::cout << "Server(): getaddrinfo() error: " << status << std::endl;
		throw std::exception("Server(): getaddrinfo() error");
	}
	if ((_listener = socket(servinfo->ai_family, servinfo->ai_socktype,
		getprotobyname("tcp"))) == -1)
		throw std::exception(strerror(errno));
	// connect() si dan host???
	if (setsockopt(_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1)
		throw std::exception(strerror(errno));
	if (fcntl(_listener, F_SETFL, O_NONBLOCK) == -1)
		throw std::exception(strerror(errno));
	if (bind(_listener, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
		throw std::exception(strerror(errno));
	freeaddrinfo(servinfo);
	if (listen(_listener, 10) == -1)
		throw std::exception(strerror(errno));
	FD_ZERO(&_master);
	FD_SET(_listener, &_master);
	_max = _listener;
}
Server::~Server(void)
{
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
fd_set					Server::getMaster(void) const
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
std::vector <User>		Server::getUsers(void) const
{
	return (_users);
}
std::vector <Channel>	Server::getChannels(void) const
{
	return (_channels);
}
int						Server::getListener(void) const
{
	return (_listener);
}
