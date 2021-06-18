#include "Channel.hpp"

Channel::Channel(std::string &name): _name(name) {}

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

std::string Channel::getName(void) const
{
	return (this->_name);
}

bool Channel::belong_channel(int fd)
{
	for (iterator ituser = _users.begin(); ituser != _users.end(); ++ituser)
	{
		if ((*ituser)->getSocket() == fd)// NO es así pero es la idea
				return (true);
	}
	return (false);
}
