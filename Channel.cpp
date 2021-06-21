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

Channel		*Channel::clone(void) const
{
	return (new Channel(*this));
}

bool		Channel::belong_channel(int fd)
{
	for (iterator ituser = _users.begin(); ituser != _users.end(); ++ituser)
	{
		if ((*ituser)->getSocket() == fd)
				return (true);
	}
	return (false);
}

std::list <User *> Channel::getListUsers() const
{
	return (this->_users);
}

std::string	Channel::getTopic(void) const
{
	return (this->_topic);
}

void	Channel::setNewUser(User *newuser)
{
	this->_users.push_back(newuser->clone());
}

void	Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}
