/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 13:09:22 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/06/18 10:24:13 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

// Constructor + Destructor

User::User(int fd) : _socket(fd), _hostname(0), _username(0), _realname(0)
{
	return;
}

User::~User(void)
{
	return;
}

User					*User::clone(void) const
{
	return (new User(_socket));
}
// Getters

int						User::getSocket(void) const
{
	return (this->_socket);
}
int						User::getHopcount(void) const
{
	return (this->_hopcount);
}
std::string				User::getNickname(void) const
{
	return (this->_nickname);
}
std::string				User::getUsername(void) const
{
	return (this->_username);
}
std::string				User::getHostname(void) const
{
	return (this->_hostname);
}
std::string				User::getRealname(void) const
{
	return (this->_realname);
}
bool					User::getIsOP(void) const
{
	return (this->_isOP);
}
/*std::list<Channel*>		User::getChannels(void) const
{
	return (this->_channels);
}*/

// Setters

void					User::setHopcount(int hopcount)
{
	this->_hopcount = hopcount;
	return;
}
void					User::setNickname(std::string nickname)
{
	this->_nickname = nickname;
	return;
}
void					User::setIsOP(bool OP)
{
	this->_isOP = OP;
	return;
}
/*void					User::setChannels(std::list<Channel*> channels)
{
	this->_channels = channels;
	return;
}*/
void					User::message(Server server, char *buff, int nbytes)
{
	for (int j = 0; j <= server.getMax(); ++j)
	{
		if (FD_ISSET(j, &server.getMaster()) && j != server.getListener()
			&& j != _socket) //&& pertenece a su canal
			if (send(j, buff, nbytes, 0) == -1)
				throw std::runtime_error(strerror(errno));
	}
}
