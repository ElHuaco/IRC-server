/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:57:49 by aleon-ca          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/18 12:50:18 by mmonroy-         ###   ########.fr       */
=======
/*   Updated: 2021/06/18 12:49:35 by aleon-ca         ###   ########.fr       */
>>>>>>> b0147e9610ed1f0db078e6d74360c45a1ccd2b80
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <map>
# include <list>
# include <string>

class User;

class Channel
{
	public:
		typedef std::list<User *>::iterator	iterator;

	private:
		//lista de usuarios en el canal
		std::list<User *>		_users;
		//un vector de chanops
		//atributos de commands: mensaje del día, etc.
		std::string	_name;
		std::string _topic;
		//std::map<std::string, ft_command>	_command_list; //Pasar el map de la lista de commands
		Channel();

	public:
		//get lista sockets
		Channel(std::string &name);
		~Channel();
		Channel(const Channel & other);
		Channel	&operator=(const Channel &rhs);

		std::string getName(void) const;

		Channel		*clone(void) const;
		bool		belong_channel(int fd);
};
# include "User.hpp"
