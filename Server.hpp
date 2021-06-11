/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:19:45 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/11 10:35:20 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


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
		//Dos constructores para red IRC o no.
		//Crear cliente nuevo con accept()
		//Cliente tiene método de enviar, según canal o privado
		//Enviar numeric reply
}
