/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:57:49 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/18 15:31:11 by fjimenez         ###   ########.fr       */
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

		std::string			getName(void) const;
		std::list <User *>	getListUsers(void) const;
		std::string			getTopic(void) const;

		void				setNewUser(User *newuser);
		void				setTopic(std::string topic);

		Channel				*clone(void) const;
		bool				belong_channel(int fd);
};
# include "User.hpp"
