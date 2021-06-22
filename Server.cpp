#include "Server.hpp"

Server::Server(void)
{
}
Server::~Server(void)
{
	for (u_iterator it = _users.begin(); it != _users.end(); ++it)
		delete *it;
	_users.clear();
	for (c_iterator it2 = _channels.begin(); it2 != _channels.end(); ++it2)
		delete *it2;
	_channels.clear();
	#ifdef DEBUG
		std::cout << "Server conf destroyed" << std::endl;
	#endif
}

//Server::Server(const Server &other)
//{
//	*this = other;
//}
//
//Server & Server::operator=(const Server &rhs)
//{
//	this->_master = rhs._master;
//	this->_max = rhs._max;
//	this->_listener = rhs._listener;
//	this->_password = rhs._password;
//	return (*this);
//}

void	Server::start(const std::string &port_listen)
{
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
	#ifdef DEBUG
		std::cout << "Server conf finished" << std::endl;
	#endif
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
}
int						Server::getListener(void) const
{
	return (_listener);
}
std::list<User *>		Server::getUsers(void) const
{
	return (_users);
}
void					Server::addUser(void)
{
	struct sockaddr_storage remoteaddr;
	socklen_t addrlen = sizeof remoteaddr;
	int newfd = accept(_listener, (struct sockaddr *)&remoteaddr,
		&addrlen);
	if (newfd == -1)
		throw std::runtime_error(strerror(errno));
	if (fcntl(newfd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error(strerror(errno));
	User temp(newfd);
	_users.push_back(temp.clone());
	#ifdef DEBUG
		std::cout << "New User with socket " << temp.getSocket();
		std::cout << " added." << std::endl;
	#endif
	std::string buff = "Welcome to the Internet Relay Network!\r\n";
	send(newfd, buff.c_str(), strlen(buff.c_str()), 0);
	FD_SET(newfd, &_master);
	if (newfd > _max)
		_max = newfd;
}
User					*Server::getSocketUser(int socket)
{
	for (u_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if ((*it)->getSocket() == socket)
			return (*it);
	}
	return (nullptr);
}
void					Server::deleteUser(int fd)
{
	for (u_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if ((*it)->getSocket() == fd)
		{
			close(fd);
			FD_CLR(fd, &_master);
			delete *it;
			_users.erase(it);
			if (fd == _max)
			{
				int max = 0;
				for (u_iterator it = _users.begin(); it != _users.end(); ++it)
				{
					if ((*it)->getSocket() > max)
						max = (*it)->getSocket();
				}
				_max = max;
			}
			return ;
		}
	}
}
void					Server::deleteUser(const std::string &nick)
{
	for (u_iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if ((*it)->getNickname() == nick)
		{
			close((*it)->getSocket());
			FD_CLR((*it)->getSocket(), &_master);
			delete *it;
			_users.erase(it);
			if ((*it)->getSocket() == _max)
			{
				int max = 0;
				for (u_iterator it = _users.begin(); it != _users.end(); ++it)
				{
					if ((*it)->getSocket() > max)
						max = (*it)->getSocket();
				}
				_max = max;
			}
			return ;
		}
	}
}
void					Server::addChannel(Channel *chann)
{
	if (chann != nullptr)
		_channels.push_back(chann->clone());
}
Channel					*Server::getChannelName(const std::string &str)
{
	for (c_iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if ((*it)->getName() == str)
			return (*it);
	}
	return (nullptr);
}
std::list <Channel *>	Server::getChannels(void) const
{
	return (_channels);
}
void					Server::deleteChannel(const std::string &name)
{
	for (c_iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if ((*it)->getName() == name)
		{
			delete (*it);
			_channels.erase(it);
			return ;
		}
		
	}
}

bool		Server::are_in_same_channels(int sender, int receiver)
{
	User *u1;
	User *u2;
	if ((u1 = this->getSocketUser(sender)) == nullptr ||
		(u2 = this->getSocketUser(receiver)) == nullptr)
		return false;
	for (c_iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (u1->is_in_channel(*it) && u2->is_in_channel(*it))
			return true;
	}
	return false;
}
