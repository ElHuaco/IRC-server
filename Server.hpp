#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netdb.h>
# include <list>
# include <string>
# include <iostream>
# include <exception>
# include <cstring>
# include <cerrno>
# include <unistd.h>
# include <fcntl.h>
# include "User.hpp"
# include "Channel.hpp"
#include "Command.hpp"

class Server
{
	public:
		typedef std::list<User *>::iterator		u_iterator;
		typedef std::list<Channel *>::iterator	c_iterator;

	private:
		fd_set					_master;
		int						_max;
		int						_listener;
		std::string				_password;
		std::list<User *>		_users;
		std::list<Channel *>	_channels;
		int						_numusers;
		Server	&operator=(const Server &rhs);
		Server(const Server & other);
		

	public:
		//Coplien
		Server(void);
		~Server(void);

		//Start configuration
		void					start(const std::string &port);

		//User and channel lists management
		void					addUser(void);
		User					*getSocketUser(int socket);
		std::list<User *>		&getUsers(void);
		void					deleteUser(const std::string &nick);
		void					deleteUser(int fd);
		void					addChannel(Channel *chann);
		Channel					*getChannelName(const std::string &str);
		std::list <Channel *>	&getChannels(void);
		void					deleteChannel(const std::string &name);

		//Get(set)ters
		void					setMax(int max);
		int						getMax(void) const;
		int						getListener(void) const;
		void					setMaster(fd_set set);
		fd_set					&getMaster(void);
		void					setPassword(const std::string &password);
		std::string				getPassword(void) const;
		int						getNumUsers(void) const;
		//Message
		bool					are_in_same_channels(int sender, int receiver);
};
#endif
