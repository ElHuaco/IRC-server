/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:19:45 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/14 12:23:01 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
//# include "User.hpp"
//# include "Channel.hpp"

class Server
{
	private:
		fd_set					_master;
		int						_max;
		int						_listener;
		std::string				_password;
//		std::vector<User>		_users;
//		std::vector<Channel>	_channels;
		Server(void);
		Server(const Server & other);
		Server	&operator=(const Server &rhs);

	public:
		//Un constructor con un parametro a default, que es el host:pass:port.
		// host, port_network son del getaddrinfo(). port es del bind()????
		explicit Server(const std::string &port, const std::string &password,
			const std::string &host = std::string(),
			const std::string &port_network = std::string(),
			const std::string &password_network = std::string());
		~Server(void);
		//Crear cliente nuevo con accept()
		// Usere tiene método de enviar, según canal o privado
		//Enviar numeric reply
		void					setMax(int max);
		int						getMax(void) const;
		int						getListener(void) const;
		void					setMaster(fd_set set);
		fd_set					&getMaster(void);
		void					setPassword(const std::string &password);
		std::string				getPassword(void) const;
//		std::vector <User>		getUsers(void) const;
//		std::vector <Channel>	getChannels(void) const;
};
