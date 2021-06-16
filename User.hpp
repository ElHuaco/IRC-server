/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:40:36 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/16 11:18:29 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Server.hpp"
# include "Channel.hpp"
# include <list>

class User
{
	private:
		int						_socket;
		int						_hopcount;
		std::string				_nickname;
		std::string				_username;
		std::string				_realname;
		std::string				_hostname;
		bool					_isOP;
		std::list<Channel*>		_channels;

		User(void);
		User(const User & other);
		
	public:
		// Constructor + Destructor
		User(std::string username, std::string hostname, std::string realname);
		~User(void);

		// Getters + Setters
		int						getSocket() const;
		int						getHopcount() const;
		std::string				getNickname() const;
		std::string				getUsername() const;
		std::string				getRealname() const;
		std::string				getHostname() const;
		bool					getIsOP() const;
		std::list<Channel*>		getChannels() const;

		void					setHopcount(int hopcount);
		void					setNickname(std::string nickname);
		void					setIsOP(bool OP);
		void					setChannels(std::list<Channel*>);
		
		//métodos de enviar a secas a otros sockets
		//otros métodos de command
};
