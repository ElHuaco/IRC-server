/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:19:45 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/11 14:37:21 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netdb.h>
# include <vector>
# include "Client.hpp"
# include "Channel.hpp"
# define PORT 443

class Server
{
	private:
		fd_set					_master;
		int						_max;
		int						_listener;
		std::string				_password;
		std::vector<Client>		_clients;
		std::vector<Channel>	_channels;
		Server(void);
		Server(const Server & other);
		Server	&operator=(const Server &rhs);

	public:
		//Un constructor con un parametro a default, que es el host:pass:port.
		// host, port_network son del getaddrinfo(). port es del bind()????
		Server(const char *node = NULL, const char *service = PORT,
			const std::string &password_port = std::string(), port, password);
		//Crear cliente nuevo con accept()
		// Cliente tiene método de enviar, según canal o privado
		//Enviar numeric reply
}
