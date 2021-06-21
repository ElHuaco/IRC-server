#include "Channel.hpp"

// Constructors  + Destructor + '=' operator

Channel::Channel(std::string &name): _name(name) {}

Channel::~Channel() {}

Channel::Channel(const Channel & other)
{
	*this = other;
}

Channel 				&Channel::operator=(const Channel &rhs)
{
	this->_name = rhs._name;
	return (*this);
}


// Functions

Channel					*Channel::clone(void) const
{
	return (new Channel(*this));
}

bool					Channel::belong_channel(int fd)
{
	for (iterator ituser = _users.begin(); ituser != _users.end(); ++ituser)
	{
		if ((*ituser)->getSocket() == fd)
				return (true);
	}
	return (false);
}

void					Channel::addUser(User *user)
{
	this->_users.push_back(user);
	return ;
}

void					Channel::getOutUser(User *user)
{
	this->_users.remove(user);
	return ;
}

void					Channel::addChanop(User *chanop)
{
	this->_chanops.push_back(chanop);
	return ;
}

void					Channel::getOutChanop(User *chanop)
{
	this->_chanops.remove(chanop);
	return ;
}


//	Getters

std::list <User *>		Channel::getListUsers() const
{
	return (this->_users);
}

std::list <User *>		Channel::getListChanops() const
{
	return (this->_chanops);
}

std::string				Channel::getTopic(void) const
{
	return (this->_topic);
}

std::string				Channel::getName(void) const
{
	return (this->_name);
}


//	Setters

void					Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}
