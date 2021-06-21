/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:57:49 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/21 11:08:04 by mmonroy-         ###   ########.fr       */
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
		std::list<User *>		_chanops;
		//un vector de chanops
		//atributos de commands: mensaje del día, etc.
		std::string	_name;
		std::string _topic;
		//std::map<std::string, ft_command>	_command_list; //Pasar el map de la lista de commands
		Channel();

	public:
	//	Constructors + Destructor
		Channel(std::string &name);
		~Channel();
		Channel(const Channel & other);
		Channel	&operator=(const Channel &rhs);

	//	Functions
		Channel				*clone(void) const;
		bool				belong_channel(int fd);
		void				addUser(User *user);
		void				getOutUser(User  *user);
		void				addChanop(User *chanop);
		void				getOutChanop(User  *chanop);

	//	Getters + Setters
		std::string			getName(void) const;
		std::list <User *>	getListUsers(void) const;
		std::list <User *>	getListChanops(void) const;
		std::string			getTopic(void) const;

		void				setTopic(std::string topic);

};
# include "User.hpp"
