/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:19:45 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/16 13:03:33 by aleon-ca         ###   ########.fr       */
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
//# include "Channel.hpp"

class Server
{
	public:
		typedef std::vector<User *>::iterator		u_iterator;
//		typedef std::vector<Channel *>::iterator	c_iterator;

	private:
		fd_set					_master;
		int						_max;
		int						_listener;
		std::string				_password;
		std::vector<User *>		_users;
//		std::vector<Channel *>	_channels;
		

	public:
		Server(void);
		~Server(void);
		Server	&operator=(const Server &rhs);
		Server(const Server & other);
		void					start(const std::string &port,
			const std::string &host = std::string(),
			const std::string &port_network = std::string(),
			const std::string &password_network = std::string());
		void					addUser(void);
		User					*getSocketUser(int socket);
		std::vector<User *>		getUsers(void) const;
		void					deleteUser(const std::string &nick);
		void					deleteUser(int fd);
//		void					addChannel(void);
//		void					deleteChannel(const std::string &name);
		// User tiene método de enviar, según canal o privado
		//Enviar numeric reply
		void					setMax(int max);
		int						getMax(void) const;
		int						getListener(void) const;
		void					setMaster(fd_set set);
		fd_set					&getMaster(void);
		void					setPassword(const std::string &password);
		std::string				getPassword(void) const;
//		std::vector <Channel>	getChannels(void) const;
		void					numeric_reply(int key, User *client);
};
#endif
