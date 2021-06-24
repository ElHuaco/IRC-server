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

void					Channel::addChanop(User *chanop)
{
	if (chanop == nullptr)
		return ;
	for (iterator it = _chanops.begin(); it != _chanops.end(); ++it)
	{
		if ((*it)->getNickname() == chanop->getNickname())
			return ;
	}
	this->_chanops.push_back(chanop);
	return ;
}

void					Channel::deleteChanop(User *chanop)
{
	this->_chanops.remove(chanop);
	return ;
}
//void					Channel::chanMessage(Server &serv, const char *buff, int nbytes)
//{
//	std::list<User *>::iterator it;
//	for (it = serv.getUsers().begin(); it != serv.getUsers().end(); ++it)
//	{
//		if ((*it)->is_in_channel(this))
//			send((*it)->getSocket(), buff, nbytes, 0);
//	}
//	return ;
//}


//	Getters

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
