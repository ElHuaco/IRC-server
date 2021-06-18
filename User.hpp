/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:40:36 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/18 12:49:07 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <list>
# include <string>
# include "Channel.hpp"

class Server;

class User
{
	public:
		typedef std::list<Channel *>::iterator	c_iterator;

	private:
		int						_socket;
		int						_hopcount;
		std::string				_nickname;
		std::string				_username;
		std::string				_realname;
		std::string				_password;
		std::string				_hostname;
		bool					_isOP;
		std::list<Channel*>		_joinedChannels;

		
	public:
		// Constructor + Destructor
		User(int fd);
		~User(void);
		User(void);
		User(const User & other);
		User	&operator=(const User &rhs);

		User					*clone(void) const;
		// Getters + Setters
		int						getSocket() const;
		int						getHopcount() const;
		std::string				getNickname() const;
		std::string				getUsername() const;
		std::string				getRealname() const;
		std::string				getHostname() const;
		bool					getIsOP() const;
//		std::list<Channel*>		getChannels() const;

		void					setHopcount(int hopcount);
		void					setNickname(std::string nickname);
		void					setIsOP(bool OP);
		void					setUsername(std::string username);
		void					setRealname(std::string realname);
		//TODO
		void					addChannel(Channel *chann);
		Channel					*getChannelName(const std::string &str);
		std::list <Channel *>	getChannels(void) const;
		void					deleteChannel(const std::string &name);
		
		//métodos de enviar a secas a otros sockets, comprobando channels
		void					message(Server serv, char *buff, int nbytes);
		//otros métodos de command
		bool					is_in_same_channels(int fd);
};
# include "Server.hpp"
