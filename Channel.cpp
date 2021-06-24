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
void					Channel::chanMessage(Server &serv, const char *buff, int nbytes)
{
	std::list<User *>::iterator it1;
	for (it1 = serv.getUsers().begin(); it1 != serv.getUsers().end(); ++it1)
	{
		std::list<Channel *>::iterator it2;
		for (it2 = (*it1)->getListChannels().begin(); it2 != (*it1)->getListChannels().end(); ++it2)
			if ((*it2)->getName() == this->_name)
				(*it1)->message(serv, buff, nbytes);
	}
	return ;
}


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
