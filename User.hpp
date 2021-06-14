/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 10:40:36 by aleon-ca          #+#    #+#             */
/*   Updated: 2021/06/14 12:01:04 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class User
{
	private:
		int				_socket;
		std::string		_nickname;
		std::string		_username;
		std::string		_realname;
		std::string		_hostname;
		int				_hopcount;
		bool			_isOP;
		std::list<Channel*>	_channels;
	public:
		//métodos de enviar a secas a otros sockets
		//otros métodos de command
}
