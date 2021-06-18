/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:57:49 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/18 12:11:17 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <map>

class Server;
class User;

class Channel
{
	private:
		//lista de int socket fds
		//un vector de chanops
		//atributos de commands: mensaje del día, etc.
		std::string	_name;
		User		_users;
		Server		_server;
		//std::map<std::string, ft_command>	_command_list; //Pasar el map de la lista de commands
		Channel();

	public:
		//get lista sockets
		Channel(std::string &name, User users, Server server);
		~Channel();
		Channel(const Channel & other);
		Channel	&operator=(const Channel &rhs);

		std::string &getname(void);
		Channel		*clone(void) const;
		bool		belong_channel(int fd);
};
# include "User.hpp"
# include "Server.hpp"
