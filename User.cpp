/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 13:09:22 by mmonroy-          #+#    #+#             */
/*   Updated: 2021/06/21 09:39:57 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

// Constructor + Destructor

User::User(int fd)
: _socket(fd), _isOP(false)
{
	return;
}

User::~User(void)
{
	for (iterator it = _joinedChannels.begin(); it != _joinedChannels.end(); ++it)
		delete *it;
	_joinedChannels.clear();
	return;
}

#include <iostream>
User					*User::clone(void) const
{
	std::cout << "Cloning user..." << std::endl;
	return (new User(_socket));
}

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
void					User::setUsername(std::string username)
{
	this->_username = username;
	return;
}
void					User::setRealname(std::string realname)
{
	this->_realname = realname;
	return;
}
void					User::setIsOP(bool OP)
{
	this->_isOP = OP;
	return;
}

void					User::addChannel(Channel *chann)
{
	_joinedChannels.push_back(chann->clone());
}
Channel					*User::getChannelName(const std::string &str)
{
	for (iterator it = _joinedChannels.begin(); it != _joinedChannels.end(); ++it)
	{
		if ((*it)->getName() == str)
			return (*it);
	}
	return (nullptr);
}
std::list <Channel *>	User::getChannels(void) const
{
	return (_joinedChannels);
}
void					User::deleteChannel(const std::string &name)
{
	for (iterator it = _joinedChannels.begin(); it != _joinedChannels.end(); ++it)
	{
		if ((*it)->getName() == name)
		{
			delete (*it);
			_joinedChannels.erase(it);
			return ;
		}
		
	}
}

bool					User::is_in_same_channels(int fd)
{
	for (iterator it = _joinedChannels.begin(); it != _joinedChannels.end(); ++it)
	{
		if ((*it)->belong_channel(fd) == true)
			return true;
	}
	return false;
}
void					User::message(Server &server, char *buff, int nbytes)
{
	for (int j = 0; j <= server.getMax(); ++j)
	{
		if (FD_ISSET(j, &server.getMaster()) && j != server.getListener()
			&& j != _socket) //&& this->is_in_same_joinedChannels(j)
			if (send(j, buff, nbytes, 0) == -1)
				throw std::runtime_error(strerror(errno));
	}
}
