/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:19:45 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/18 10:09:01 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netdb.h>
# include <vector>
# include <string>
# include <iostream>
# include <exception>
# include <cstring>
# include <cerrno>
# include <unistd.h>
# include <fcntl.h>
# include "User.hpp"
# include "Channel.hpp"

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
		std::vector<User *>		_users;
		std::vector<Channel *>	_channels;
		

	public:
		//Coplien
		Server(void);
		~Server(void);
		Server	&operator=(const Server &rhs);
		Server(const Server & other);

		//Start configuration
		void					start(const std::string &port);

		//User and channel lists management
		void					addUser(void);
		User					*getSocketUser(int socket);
		std::vector<User *>		getUsers(void) const;
		void					deleteUser(const std::string &nick);
		void					deleteUser(int fd);
		void					addChannel(Channel *chann);
		Channel					*getChannelName(const std::string &str);
		std::vector <Channel *>	getChannels(void) const;
		void					deleteChannel(const std::string &name);

		//Bare messages and error replies
		void					message(int user_socket, char *buff, int bytes); 
		void					error_reply(const std::string &cmd,
				std::string *erroneous_arg, int key);

		//Get(set)ters
		void					setMax(int max);
		int						getMax(void) const;
		int						getListener(void) const;
		void					setMaster(fd_set set);
		fd_set					&getMaster(void);
		void					setPassword(const std::string &password);
		std::string				getPassword(void) const;
};
#endif
