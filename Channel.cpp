#include "Channel.hpp"

Channel::Channel(std::string &name, User users, Server server): _name(name), _users(users), _server(server) {}

Channel::~Channel() {}

Channel::Channel(const Channel & other)
{
	*this = other;
}

Channel & Channel::operator=(const Channel &rhs)
{
	this->_name = rhs._name;
	return (*this);
}

std::string & Channel::getname(void)
{
	return (this->_name);
}

bool Channel::belong_channel(int fd)
{
	std::vector<Channel *>::iterator itchannel = this->_server.getChannels().begin();
	std::vector<User *>::iterator ituser = this->_server.getUsers().begin();

	for (; itchannel != this->_server.getChannels().end(); ++itchannel)
	{
		for (; ituser != this->_server.getUsers().end(); ++ituser)
		{
			if (*ituser.getSocket() == fd)// NO es así pero es la idea
				return (true);
		}
	}
	return (false);
}
